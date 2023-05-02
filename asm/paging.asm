PageTableEntry equ 0x1000

SetupIdentityPaging:
    ;; fill our tables

    mov edi, PageTableEntry
    mov cr3, edi
    
    mov dword [edi], 0x2003
    add edi, 0x1000

    mov dword [edi], 0x3003
    add edi, 0x1000

    mov dword [edi], 0x4003
    add edi, 0x1000
    
    ;; loop for 512 times
    mov ebx, 0x00000003
    mov ecx, 512

    ;; add 512 entries
    .SetEntry:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop .SetEntry

    ;; enable PAE

    mov edx, cr4
    or  edx, (1 << 5)
    mov cr4, edx
    
    ;; set long mode enable

    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

    ;; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0 ,eax

    ret