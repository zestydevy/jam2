.include "macros.inc"

.section .data

glabel _miditableSegmentRomStart
.incbin "sound/N64ST1.PTR"
.balign 16
glabel _miditableSegmentRomEnd

glabel _midibankSegmentRomStart
.incbin "sound/N64ST1.WBK"
.balign 16
glabel _midibankSegmentRomEnd

glabel _seqSegmentRomStart
.incbin "sound/N64ST1.BIN"
.balign 16
glabel _seqSegmentRomEnd

glabel _sfxSegmentRomStart
.incbin "sound/N64ST1.BFX"
.balign 16
glabel _sfxSegmentRomEnd
