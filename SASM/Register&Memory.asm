%include "io64.inc"

section .text
global main
main:
    mov rbp, rsp ; for correct debugging
    
    mov eax, 0x1234
    mov rbx, 0x12345678
    mov cl, 0xff
    mov al, 0x00
    
    ;Memory <-> Register
    ;mov rax, a --> a의 변수 주소값을 rax에 저장함.
    ;mov rax, [a] --> a의 변수에 선언된 값을 rax에 저장함.
    mov al, [a] ; rax = 1211, al = 1byte, 1byte 영역에만 영향을 줌.
    
    mov [a], byte 0x55      ;0x55, 0x22, 0x22, 0x33, 입력할 상수 앞에 해당 상수 사이즈를 명시해주어야함.
    mov [a], word 0x6666    ;0x55, 0x55, 0x22, 0x33, 해당 변수보다 큰 사이즈의 상수를 입력하면 그 다음 주소에 저장됨.
    mov [a], cl     ;cl = 1byte, 0xff, 0x55, 0x22, 0x33

    
    xor rax, rax
    ret

section .data
;초기화된 데이터
;[변수 이름] [크기] [초기값]
;크기 db = 1byte, dw = 2byte, dd = 4byte, dq = 8byte
    a db 0x11               ;1byte
    b dw 0x2222             ;2byte
    c dd 0x33333333         ;4byte
    d dq 0x4444444444444444 ;8byte

section .bss
;초기화 되지 않은 데이터
;[변수이름] [크기] [개수]
;크기 resb = 1byte, resw = 2byte, resd = 4byte, resq = 8byte
    e resb 10