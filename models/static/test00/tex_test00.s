.include "macros.inc"

.section .data
    
glabel grass_road_rgba16
.incbin "models/static/test00/road.rgba16.bin"
.balign 16

glabel grass_race_rgba16
.incbin "models/static/test00/race.rgba16.bin"
.balign 16

glabel grass_fence_rgba16
.incbin "models/static/test00/fence.rgba16.bin"
.balign 16

glabel sky_sky_rgba16
.incbin "models/static/test00/sky.rgba16.bin"
.balign 16
