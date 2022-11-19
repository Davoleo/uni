#include <stdio.h>

int main(int argc, char* argv[])
{
    int i, val = 0x01020304;
    char* ptr;

    printf("Using value %08X\n", val);
    ptr = (char*) &val;

    printf("Host order: \n");
    for (i = 0; i < sizeof(int); i++) 
		printf("val[%d]=%02hhX\n", i, ptr[i]);

    return 0;
}


