#include "x86.h"
#include "elf.h"

#define SECT_SIZE (512)
#define ELF_HEADER ((struct elf *) 0x10000)

void bootmain (void)
{
    struct Proghdr *ph, *eph;
    read_seg(0x10000, 4096, 0);
    if (    ->e_magic != ELF_MAGIC)
        goto bad;
    ph = ;
    eph = ;
    for (/*nop*/; ph < eph; ph++) {
        read_seg(ph->p_pa, ph->p_memsz, ph->p_offset);
    }
    ((void (*)(void)) (ELFHDR->e_entry))();
bad:
    outw(0x8A00, 0x8A00);
    outw(0x8A00, 0x8E00);
    while (true) {
        /*nop*/;
    }
}

static void waitdisk (void)
{
    while ((inb(0x1F7) & 0xC0) != 0x40)
        /*nop*/;
}

static void read_sect (void* dst, uint32_t offset)
{
    const int size = 512/4;
    waitdisk();
    outb(0x1F2, 1);     // count = 1
    outb(0x1F3, offset);
    outb(0x1F4, offset >> 8);
    outb(0x1F5, offset >> 16);
    outb(0x1F6, ((offset >> 24) | 0xE0));
    outb(0x1F7, 0x20);  // cmd 20 = read sectors
    waitdisk();
    insl(0x1F0, dst, size);
}
