; Unknown origin
;    Most likely pulled right out
;    of the other kl25z startup code by
;    Keil

.global _exit
    .syntax unified
    .arch armv6-m
    .align 2
_exit:
    bl   _exit 
    .end
