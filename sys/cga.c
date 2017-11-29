


/* Text-mode CGA display output */
static uint16_t crt_buf[];
static unsigned crt_addr;
static uint16_t crt_pos;

static void cga_putc (int c)
{
    if (!(c & ~0xFF)) {
        c |= 0x0700;
    }
    // crt_buf
    switch (c & 0xFF) {
    default:
        crt_buf[crt_pos++] = c;
        break;
    }
    // crt_buf
    if (crt_pos >= CRT_SIZE) {
        memmove(crt_buf, crt_buf+CRT_COLS, (CRT_SIZE-CRT_COLS)*sizeof(uint16_t));
        for (int i = CRT_SIZE-CRT_COLS; i < CRT_SIZE; i++) {
            crt_buf[i] = (0x0700 | ' ');
        }
        crt_pos -= CRT_COLS;
    }
    /* move that little blinky thing */
    outb(addr_6845, 14);
    outb(addr_6845+1, crt_pos >> 8);
    outb(addr_6845, 15);
    outb(addr_6845+1, crt_pos);
}

static void cga_init (void)
{
    volatile uint16_t *cp;
    uint16_t was;
    unsigned pos;

    cp = (uint16_t *)(KERNBASE + CGA_BUF);
    was = *cp;
    *cp = (uint16_t)0xA55A;
    if (*cp != 0xA55A) {
        cp = (uint16_t *)(KERNBASE + MONO_BUF);
        addr_6845 = MONO_BASE;
    } else {
        *cp = was;
        addr_6845 = CGA_BASE;
    }

    /* Extract cursor location */
    outb(addr_6845, 14);
    pos = inb(addr_6845+1) << 8;
    outb(addr_6845, 15);
    pos |= inb(addr_6845+1);

    crt_buf = (uint16_t *)cp;
    crt_pos = pos;
}
