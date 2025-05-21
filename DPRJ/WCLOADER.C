#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <i86.h>

int getfilesize(const char *fname)
{
    FILE *fp;
    unsigned char *temp;
    int size;

    temp = malloc(1024 * 20);
    if (!temp) {
        printf("\nMemory allocation failed");
        return -1;
    }

    fp = fopen(fname, "rb");
    if (!fp) {
        printf("\nCannot open file: %s", fname);
        free(temp);
        return -1;
    }

    size = fread(temp, 1, 1024 * 20, fp);
    printf("\nRead app file: %s (size %d)", fname, size);
    fclose(fp);
    free(temp);
    return size;
}

int readfile(const char *fname, unsigned segProcessAppAddr)
{
    FILE *fp;
    unsigned char *temp;
    int size;
    void far *entry_point; //the first instruction address of ".com" file

    fp = fopen(fname, "rb");
    if (!fp) {
        printf("\nCannot open file: %s", fname);
        return -1;
    }

    temp = malloc(1024 * 20);
    if (!temp) {
        fclose(fp);
        printf("\nMemory allocation failed");
        return -1;
    }

    size = fread(temp, 1, 1024 * 20, fp);
    printf("\nRead app file: %s (size %d)", fname, size);
    fclose(fp);

    entry_point = MK_FP(segProcessAppAddr, 0x100);
    _fmemcpy(entry_point, temp, size);
    free(temp);
    return 0;
}

int loadApp(const char *fname)
{
    unsigned segProcessAppAddr;
    int size;
    int num_para;
    void far *entry_point; //the first instruction address of ".com" file

    size = getfilesize(fname);
    if (size <= 0) {
        printf("\nCannot open file: %s", fname);
        return -1;
    }

    num_para = (size + 15 + 0x100) / 16;
    printf("\nAllocate memory for app: %d paragraphs (%d bytes)", num_para, size);

    if (_dos_allocmem(num_para, &segProcessAppAddr)) {
        printf("\nCannot allocate memory for app");
        return -1;
    }

    printf("\nLoad app into memory at segment: %04X\n", segProcessAppAddr);
    readfile(fname, segProcessAppAddr);

    //the first instruction address of ".com" file
    entry_point = MK_FP(segProcessAppAddr, 0x100);

    printf("\nTransferring control to loaded app...\n");

    _asm {
		lds  bx, dword ptr entry_point
        mov  ax, ds
        mov  es, ax
        mov  ss, ax
        mov  sp, 0xFFFE
        push ds                // push segProcessAppAddr
        push bx                // push 0x100
        retf                   // far return to new program
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *fname = "app2.com";

    if (argc > 1) {
        fname = argv[1];
    }

    printf("\nStart loading app: %s\n", fname);
    loadApp(fname);
    printf("\nLoader terminated\n");

    return 0;
}
