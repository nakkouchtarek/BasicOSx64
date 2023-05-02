jmp EnterProtectedMode

%include "gdt.asm"
%include "print.asm"

EnterProtectedMode:
    call EnableA20 ;; enabling a20 line to access more memory
    cli ;; disable interrupts
    lgdt [gdt_descriptor] ;; load gdt into our gdt descriptor
    mov eax, cr0 ;; cpu knows its in protected mode
    or eax, 1 ;; swap last bit to 1
    mov cr0, eax ;; move the value back to cr0
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
    jmp codeseg:Start64Bit ;; after editing the gdt we have new code segment address, lets far jump to it

EnableA20:  ;; enable A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 64]

[extern _start]

%include "idt.asm"

Start64Bit:
    call _start ;; call our kernel start function
    jmp $ ;; infinite loop

times 2048-($-$$) db 0 ;; 2048 - current disk size bytes for disk