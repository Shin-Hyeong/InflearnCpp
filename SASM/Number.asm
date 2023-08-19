%include "io64.inc"

section .text
global main
main:
    ;write your code here
    
    ; -> 주석 기능
    ; 10진수(0 1 2 3 4 5 6 7 8 9)
    ;10 11 12 13 14 ... 19 20
    
    ;2진수(0 1)
    ; 0 1 10 11
    ; 0b0 0b1 0b10 0b11 0b100
    
    ;16진수(0 1 2 3 4 5 6 7 8 9 A B C D E F)
    ;0 1 2 3 4 5 6 7 8 9 A B C D E F 10
    
    ;0b10010101 = 0b 1001 0101 = 0x95
    
    xor rax, rax
    ret