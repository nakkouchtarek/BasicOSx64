[org 0x7e00]

jmp EnterProtectedMode

%include "gdt.asm"
%include "print.asm"

EnterProtectedMode:
    call EnableA20
    cli ;; disable interrupts
    lgdt [gdt_descriptor] ;; load gdt into our gdt descriptor
    mov eax, cr0 ;; cpu knows its in protected mode
    or eax, 1
    mov cr0, eax
    jmp codeseg:StartProtectedMode ;; far jump into code segment

[bits 32]

%include "cpuid.asm"
%include "paging.asm"

StartProtectedMode:
    ;; point our segment registers to data segment
    mov ax, dataseg
    mov ds , ax
    mov ss , ax
    mov es , ax
    mov fs , ax
    mov gs , ax

    ;; give more space to ur stack
    mov ebp, 0x90000
    mov esp, ebp

    ;; print to video memory
    ;; start of video memory is 0xb8000
    ;; mov [0xb8000], byte 'H' ;; current byte is character and next byte is color
    ;; mov [0xb8002], byte 'A' ;; 
    call DetectCpuId
    call DetectLongMode
    call SetupIdentityPaging
    call EditGDT
    jmp codeseg:Start64Bit

EnableA20:  ;; enable A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 64]

Start64Bit:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20 ;; 1f = color | 20 is a space
    mov ecx, 500
    rep stosq
    mov [0xb8000], byte 'H'
    jmp $

times 2048-($-$$) db 0