P1_0 = 0x90
P1_1 = 0x91
P1_2 = 0x92
P1_3 = 0x93
P1_4 = 0x94

.area CSEG    (CODE)
_blink_p1_0::
    
top:
    mov r0,#255
    mov r1,#255
loop:
    djnz r0,loop
    mov r0,#255
    djnz r1,loop
    cpl P1_0
    ret

_debug1_on::
    setb P1_1
    ret

_debug1_off::
    clr P1_1
    ret
    
