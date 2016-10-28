.global _exit
    .syntax unified
    .arch armv6-m
    .align 2
_exit:
    bl   _exit 
    .end
