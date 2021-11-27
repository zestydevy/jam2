PNG2N64
===============================

This is a PNG file converter to **RGBA32** or **RGBA16** binary format for the Nintendo 64.

Dependencies
------------

    sudo apt install cmake libpng-dev

Build
-----

    cmake .
    make

Usage
-----

    png2n64 source.png [--format=FORMAT]

Supported formats:

- `rgba32` (R8G8B8A8)
- `rgba16` (R5G5B5A1)

This will produce a result.bin file.

For the future
--------------

- Handle output IA16 format
- Handle output IA8 format
- Handle output IA4 format
- Handle output I8 format
- Handle output I4 format
- Handle output CI8 format
- Handle output CI4 format

Contributors
------------

- Thomas Noury - [Github](https://github.com/is06), [Gitlab](https://gitlab.com/is06)

License
-------

See [LICENSE](LICENSE) file for more info.