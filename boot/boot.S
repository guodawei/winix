
.global start
start:
.code16
    cli
    cld

    xorw    %ax, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %ss

seta20.1:
    inb     $0x64, %al          # Wait for not busy
    testb   $0x02, %al
    jnz     seta20.1

    movb    $0xD1, %al          # 0xD1 -> port 0x64
    outb    %al, $0x64
seta20.2:
    inb     $0x64, %al          # Wait for not busy
    testb   $0x02, %al
    jnz     $seta20.2

    movb    $0xDF, %al          # 0xDF -> port 0x60
    outb    %al, $0x60


    lgdt    gdtdesc
    movl    %cr0, %eax
    orl     $0x1, %eax
    movl    %eax, %cr0

    ljmp    $0x8, $protcseg

.code32
protcseg:
    movw    $0x10, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %fs
    movw    %ax, %gs
    movw    %ax, %ss        # -> SS: Stack Segment

    # Setup the stack pointer and call into C
    movl    $start, %esp
    call    bootmain

spin:
    jmp spin

.p2align 2
gdt:
    SEG_NULL
    SEG(STA_X|STA_R, 0x0, 0xFFFFFFFF)   # code seg
    SEG(STA_W, 0x0, 0xFFFFFFFF)         # data seg

gdtdesc:
    .word 0x17                          # sizeof(gdt) - 1
    .long gdt                           # address gdt
