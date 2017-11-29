#include <stdio.h>
#include <console.h>

void winix_init (void)
{
    // clear the BSS
    extern char edata[], end[];
    memset(edata, 0, end - edata);

    // Init the console
    cons_init();
    kprintf("winix starting...\n");

    while (true) {
        monitor(NULL);
    }
}
