



int kprintf (const char *fmt, ...)
{
    for (const char *p = fmt; *p != '\0'; p++) {
        cga_putc(*p);
        //cons_putc(*p);
    }
    return 0;
}
#if 0
static void putchar (int ch, int *cnt)
{
    cput_char(ch);
    *cnt++;
}

int kprintf (const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int cnt = vkprintf(fmt, ap);
    va_end(ap);

    return cnt;
}
int vkprintf (const char *fmt, va_list ap)
{
    int cnt = 0;
    vprintfmt((void*)putchar, &cnt, fmt, ap);
    return cnt;
}
#endif
