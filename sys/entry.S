

.text
.align 2


.global _start
_start = RELOC(entry)

.global entry
entry:
    movw    $0x1234, 0x472
    movl    $(RELOC(entry_pgdir)), %eax
    movl    %eax, %cr3

    # Trun no paging
    movl    %cr0, %eax
    orl     $0x80010001, %eax
    movl    %eax, %cr0

    mov     $relocated, %eax
    jmp     *%eax
relocated:
    movl    $0x0, %ebp
    movl    $(bootstacktop), %esp
    call    winix_init

.data
.p2align 12 # page alignment

.global bootstack
bootstack:
    .space 4096
.global bootstacktop
bootstacktop:
