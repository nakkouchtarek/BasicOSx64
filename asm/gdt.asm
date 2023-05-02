;; global descriptor table file

;; gdt null descriptor
gdt_nulldesc:
    dd 0 ;; 4 bytes
    dd 0 ;; 4 bytes

;; gdt code descriptor
gdt_codedesc:
    dw 0xFFFF ;; 2 bytes for the limit ( 16 bits for limit )
    dw 0x0000      ;; 2 bytes for base low ( 16 bits )
    db 0x00      ;; 1 bytes base medium ( 24 bits in total for base )
    db 10011010b ;; Flags ( Present + privilege + type + type flags )
    db 11001111b ;; Other Flags + upper limit last 4 bits
    db 0 ;; 0 for our base high
;; gdt data descriptor
gdt_datadesc:
    dw 0xFFFF ;; 2 bytes for the limit
    dw 0x0000      ;; 2 bytes for base low
    db 0x00      ;; 1 bytes base medium
    db 10010010b ;; Flags
    db 11001111b ;; Flags + upper limit last 4 bits
    db 0 ;; 0 for our base high
    
;; gdt descriptor
gdt_end:
gdt_descriptor:
    gdt_size: 
        dw gdt_end - gdt_nulldesc - 1
        dq gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc

[bits 32]

EditGDT:
    mov [gdt_codedesc + 6], byte 10101111b
    mov [gdt_datadesc + 6], byte 10101111b
    ret

[bits 16]