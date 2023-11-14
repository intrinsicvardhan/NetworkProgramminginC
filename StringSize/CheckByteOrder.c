#include <stdio.h>

int main() {
    union {
        short s; 
        char c[sizeof(short)]
    } un; 
    un.s = 0x0102; 
    if(sizeof(short)==2) {
        if(un.c[0]==2&&un.c[1]==1) 
            printf("Little endian");
        else if(un.c[1]==2&&un.c[0]==1)
            printf("Big endian"); 
        else
            printf("Unknown");
    }
    else {
        printf("Size of short is: %d", sizeof(short));
    }
    return 0;
}  
