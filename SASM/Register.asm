%include "io64.inc"

section .text
global main
main:
    mov rbp, rsp ; for correct debugging
    
    mov eax, 0x1234
    ;rax = 0x1234
    mov rbx, 0x12345678
    ;rbx = 0x12345678
    mov cl, 0xff
    ;cl은 8bit 임으로 0xfffff같은 용량오버가 되면 빌드가 되지 않는다.
    ;rcx = 0xff
    
    mov al, 0x00
    ;rax = 1200, al은 8bit임으로 8bit 영역에만 영향을 줌.
    ;eax 0x1234 = 0001 0010 0011 0100
    ;al  0x00 = 0001 0010 0000 0000 = 0x1200
    mov rax, rdx
    ;rax = rdx
    
    xor rax, rax
    ret