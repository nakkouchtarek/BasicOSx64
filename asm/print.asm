printString:
    mov al, [bx]
    cmp al, 0
    je exit
    mov ah, 0x0e
    int 0x10
    inc bx
    jmp printString
    exit:
        ret
