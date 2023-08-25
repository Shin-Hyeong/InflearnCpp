%include "io64.inc"

section .text
global main
main:
    mov rbp, rsp ; for correct debugging
    
    
    xor rax, rax
    ret
    
section .data
    a dd 0x12345678 
    
    ;메모리에 저장되는 방식
    ;0x78, 0x56, 0x34, 0x12 -> Little Endian
    ;캐스팅에 유리하다. -> 큰 데이터에서 일부를 가져와서 사용하는 것.
    
    ;0x12, 0x34, 0x56, 0x78 -> Big Endian
    ;숫자 비교에 유리하다.
    