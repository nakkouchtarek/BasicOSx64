[org 0x7c00] ;; our base address for this file 

mov [BOOT_DISK], dl ;; specifying where we booted from

mov bp, 0x7c00 ;; base of stack
mov sp, bp ;; stack pointer

call ReadDisk ;; read the disk

jmp PROGRAM_SPACE ;; jump to our other program address

%include "print.asm"
%include "readdisk.asm"

times 510-($-$$) db 0 ;; $ is current address, $$ is start of current address; $-$$ means size of current address
dw 0xaa55 ;; last two bytes to define the boot sector