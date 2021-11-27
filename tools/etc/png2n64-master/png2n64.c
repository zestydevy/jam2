#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png2n64.h"

int main(int argc, char* argv[])
{
    if (check_arguments(argc) != 0) {
        return 1;
    }

    FILE* png_file = fopen(argv[1], "rb");
    if (png_file == NULL) {
        printf("Unable to open the file %s\n", argv[1]);
        return 1;
    }

    png_byte header[8];
    unsigned long header_size = sizeof(header);
    if (fread(header, 1, header_size, png_file) != header_size) {
        printf("Error reading the file %s\n", argv[1]);
        return 1;
    }

    if (png_sig_cmp(header, 0, header_size)) {
        printf("File %s is not a valid PNG file\n", argv[1]);
        return 1;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        printf("Unable to initialize PNG reading\n");
        return 1;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        printf("Unable to initialize PNG info\n");
        return 1;
    }

    png_init_io(png_ptr, png_file);
    png_set_sig_bytes(png_ptr, header_size);

    png_read_info(png_ptr, info_ptr);

    int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    int color_type = png_get_color_type(png_ptr, info_ptr);

    if (bit_depth != 8) {
        printf("PNG format not supported for conversion.\n");
        return 1;
    }

    // Allocate the binary image (RGBA32 or GA16)
    bin_image_t* binary_image = (bin_image_t*)malloc(sizeof(bin_image_t));

    // Read PNG width and height
    png_get_IHDR(
        png_ptr,
        info_ptr,
        (png_uint_32*)(&binary_image->width),
        (png_uint_32*)(&binary_image->height),
        &bit_depth,
        &color_type,
        NULL,
        NULL,
        NULL
    );

    // Format from parameter (default: rgba16)
    binary_image->output_format = BINARY_IMAGE_FORMAT_RGBA16;
    if (argc == 3) {
        binary_image->output_format = get_format_from_parameter(argv[2]);
    }

    int binary_pixel_size = RGBA32_PIXEL_SIZE;

    switch (color_type) {
        case PNG_COLOR_TYPE_RGB_ALPHA:
            if (binary_image->output_format != BINARY_IMAGE_FORMAT_RGBA32
            && binary_image->output_format != BINARY_IMAGE_FORMAT_RGBA16) {
                printf("Input PNG format is RGBA, please provide rgba32 or rgba16 output format.\n");
                return 1;
            }
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            if (binary_image->output_format != BINARY_IMAGE_FORMAT_IA16
            && binary_image->output_format != BINARY_IMAGE_FORMAT_IA8) {
                printf("Input PNG format is IA, please provide ia16 or ia8 output format.\n");
                return 1;
            }
            binary_pixel_size = IA16_PIXEL_SIZE;
            break;
        default:
            printf("PNG format not supported for conversion.\n");
            return 1;
    }

    // Allocate bytes in source binary image
    binary_image->bytes = (unsigned char*)malloc(sizeof(unsigned char) * binary_image->width * binary_image->height * binary_pixel_size);

    // Row pointers for PNG read
    png_bytep* row_pointers;
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * binary_image->height);
    for (int i = 0; i < binary_image->height; ++i) {
        row_pointers[i] = (png_bytep)(binary_image->bytes + (i * binary_image->width * binary_pixel_size));
    }
    png_read_image(png_ptr, row_pointers);
    free(row_pointers);

    // Close PNG file
    png_read_end(png_ptr, NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(png_file);

    int output_pixel_size = BINARY_IMAGE_FORMAT_RGBA16;
    convert_image(binary_image, &output_pixel_size);

    write_file(*binary_image, output_pixel_size);

    // Free memory of binary image
    free(binary_image->bytes);
    free(binary_image);

    return 0;
}

void convert_image(bin_image_t* image, int* output_pixel_size)
{
    // Convert the binary image before writing to file
    switch (image->output_format) {
        case BINARY_IMAGE_FORMAT_RGBA32:
            printf("Converting using RGBA32 format...\n");
            *output_pixel_size = RGBA32_PIXEL_SIZE;
            break;
        case BINARY_IMAGE_FORMAT_RGBA16:
            printf("Converting using RGBA16 format...\n");
            convert_image_to_rgba16(image);
            *output_pixel_size = RGBA16_PIXEL_SIZE;
            break;
        case BINARY_IMAGE_FORMAT_IA16:
            *output_pixel_size = IA16_PIXEL_SIZE;
            printf("Converting using IA16 format...\n");
            break;
        case BINARY_IMAGE_FORMAT_IA8:
            printf("Converting using IA8 format...\n");
            convert_image_to_ia8(image);
            *output_pixel_size = IA8_PIXEL_SIZE;
            break;
    }
}

void write_file(bin_image_t image, int output_pixel_size)
{
    FILE* bin_file = fopen("result.bin", "wb");

    const int binary_image_size = image.width * image.height;

    printf("Done.\n");
    printf("Output binary image size: %i\n", binary_image_size * output_pixel_size);

    fwrite(image.bytes, output_pixel_size, binary_image_size, bin_file);
    
    fclose(bin_file);
}

int check_arguments(int argc)
{
    if (argc < 2 || argc > 3) {
        printf("Usage: png2n64 file [format]\n");
        printf("format: can be 'rgba32' or 'rgba16'\n");
        return 1;
    }

    return 0;
}

int get_format_from_parameter(char* parameter)
{
    if (strcmp(parameter, "--format=rgba32") == 0) {
        return BINARY_IMAGE_FORMAT_RGBA32;
    }
    if (strcmp(parameter, "--format=rgba16") == 0) {
        return BINARY_IMAGE_FORMAT_RGBA16;
    }
    if (strcmp(parameter, "--format=ia16") == 0) {
        return BINARY_IMAGE_FORMAT_IA16;
    }
    if (strcmp(parameter, "--format=ia8") == 0) {
        return BINARY_IMAGE_FORMAT_IA8;
    }

    return -1;
}

unsigned char get_ia8_color_from_ia16(unsigned short ia16)
{
    unsigned short intensity = (ia16 & 0xff00) >> 8;
    unsigned short alpha = ia16 & 0xff;

    intensity = intensity / 16;
    alpha = alpha / 16;

    return (intensity << 4) | alpha;
}

void convert_image_to_ia8(bin_image_t* image)
{
    int source_image_length = image->width * image->height * IA16_PIXEL_SIZE;
    int destination_image_length = image->width * image->height * IA8_PIXEL_SIZE;

    unsigned char* source_bytes = image->bytes;
    unsigned char* destination_bytes = (unsigned char*)malloc(sizeof(unsigned char) * destination_image_length);

    int offset = 0;
    for (int i = 0; i < source_image_length; i += IA16_PIXEL_SIZE) {
        unsigned char intensity = image->bytes[i];
        unsigned char alpha = image->bytes[i+1];

        unsigned short ia16_color = intensity << 8 | alpha;
        unsigned char ia8_color = get_ia8_color_from_ia16(ia16_color);

        destination_bytes[offset] = (ia8_color & 0xf0) >> 4;
        destination_bytes[offset+1] = ia8_color & 0xf;

        offset += IA8_PIXEL_SIZE;
    }

    image->bytes = destination_bytes;
    free(source_bytes);
}

unsigned short get_rgba16_color_from_rgba32(unsigned int rgba32)
{
    unsigned char red = (rgba32 & 0xff000000) >> 24;
    unsigned char green = (rgba32 & 0xff0000) >> 16;
    unsigned char blue = (rgba32 & 0xff00) >> 8;
    unsigned char alpha = rgba32 & 0xff;

    red = red / 8;
    green = green / 8;
    blue = blue / 8;
    alpha = alpha == 0 ? 0 : 1;

    return (red << 11) | (green << 6) | (blue << 1) | alpha;
}

void convert_image_to_rgba16(bin_image_t* image)
{
    int source_image_length = image->width * image->height * RGBA32_PIXEL_SIZE;
    int destination_image_length = image->width * image->height * RGBA16_PIXEL_SIZE;

    unsigned char* source_bytes = image->bytes;
    unsigned char* destination_bytes = (unsigned char*)malloc(sizeof(unsigned char) * destination_image_length);

    int offset = 0;
    for (int i = 0; i < source_image_length; i += RGBA32_PIXEL_SIZE) {
        unsigned char red = image->bytes[i];
        unsigned char green = image->bytes[i+1];
        unsigned char blue = image->bytes[i+2];
        unsigned char alpha = image->bytes[i+3];

        unsigned int rgba32_color = red << 24 | green << 16 | blue << 8 | alpha;
        unsigned short rgba16_color = get_rgba16_color_from_rgba32(rgba32_color);

        destination_bytes[offset] = (rgba16_color & 0xff00) >> 8;
        destination_bytes[offset+1] = rgba16_color & 0xff;

        offset += RGBA16_PIXEL_SIZE;
    }

    image->bytes = destination_bytes;
    free(source_bytes);
}
