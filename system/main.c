/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

void    printchar(char c)
{
    int i;
    for (i=0; i<30; i++)
        kprintf("%c\n", c);
}

int main(uint32 argc, uint32 *argv)
{
    //priority of process is input as the 3rd argument of create()
    ready(create((void*) printchar, INITSTK, 15, "P1", 1, 'A'), FALSE);
    ready(create((void*) printchar, INITSTK, 20, "P2", 1, 'B'), FALSE);
    ready(create((void*) printchar, INITSTK, 10, "P3", 1, 'C'), FALSE);
    ready(create((void*) printchar, INITSTK, 5, "P4", 1, 'D'), FALSE);

    return 0;
}
