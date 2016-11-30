.area CSEG    (CODE)
_wait_5us::
    nop
    nop
    nop
    nop
    ret

_wait_71ms::
    mov r0,#255
    mov r1,#255
loop:
    djnz r0,loop
    mov r0,#255
    djnz r1,loop
    ret

_wait_35ms::
    mov r0,#255
    mov r1,#127
loop3:
    djnz r0,loop3
    mov r0,#255
    djnz r1,loop3
    ret

_wait_250us::
    mov r0,#231
loop2:
    djnz r0,loop2
    ret

_wait_1s::
    mov r0,#255
    mov r1,#255
    mov r2,#14
loop1:
    djnz r0,loop1
    mov r0,#255
    djnz r1,loop1
    mov r1,#255
    djnz r2,loop1
    ret

_wait_212ms::
    mov r0,#255
    mov r1,#255
    mov r2,#3
loop4:
    djnz r0,loop4
    mov r0,#255
    djnz r1,loop4
    mov r1,#255
    djnz r2,loop4
    ret
    

