DetectCpuId:
    ;; set a bit in the flags register, copy it back
    ;; if it stays flipped, cpuid is supported

    pushfd ;; push eflags
    pop eax ;; pop the value into eax
 
    mov ecx, eax ;; move value of eax to ecx

    xor eax, 1 << 21 ;; flip bit in the register

    push eax ;; push onto the stack
    popfd ;; put it back onto the eflags

    pushfd ;; push the eflags
    pop eax ;; pop it into eax

    push ecx ;; push ecx to the stack
    popfd ;; pop the flags

    xor eax, ecx ;; compare eax to ecx
    jz nocpuid ;; ifs its no equal jump to cpu id
    ret

DetectLongMode:
    mov eax, 0x80000001 ;; we test with this large value
    cpuid ;; call cpuid
    test edx, 1 << 29 ;; see if the bit is flipped
    jz nolongmode ;; if its not flipped, no long mode support
    ret

nolongmode:
    hlt ;; no long mode support

nocpuid:
    hlt ;; no cpu id support
