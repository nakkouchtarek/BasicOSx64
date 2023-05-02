PROGRAM_SPACE equ 0x8000 ;; constant for our disk address

ReadDisk:
    mov ah, 0x02 ;; call to read sectors
    mov bx, PROGRAM_SPACE ;; our disk 
    mov al, 35 ;; sector number
    mov dl, [BOOT_DISK] ;; where we boot from
    mov ch, 0x00 ;; cylinder 0
    mov dh, 0x00 ;; head 0
    mov cl, 0x02 ;; read from the 2nd sector
    int 0x13 ;; interrupt for low level disk service
    jc DiskErrorHandle ;; jump if disk read failed
    ret ;; return if success

BOOT_DISK: db 0 ;; one null byte to store our boot disk address
ErrorMsg: db "Disk read failed", 0 ;; our fail message

DiskErrorHandle:
    mov bx, ErrorMsg
    call printString
    jmp $