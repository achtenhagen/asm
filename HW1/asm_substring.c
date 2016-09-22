#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static inline char * sub_str(char * dest, char *src, int s_idx, int edix) {
    int length = edix - s_idx + 1;
    int i;
    for (i = 0; i < length; i++) {
        *(dest + i) = *(src + s_idx + i);
    }
    *(dest + length) = '\0';
    return dest;
}

static inline char * asm_sub_str(char * dest, char *src, int s_idx, int edix) {
    __asm__ __volatile__("cld\n\t"
                         "rep\n\t"
                         "movsb"
                         :
                         :"S"(src + s_idx), "D"(dest), "c"(edix - s_idx + 1)
                         );
    return dest;
}

int main(int argc, char **argv) {
    if (argc < 1) {
        return -1;
    }
        
    char* str = argv[1];
    int strsize = strlen(str);
    int startindex = atoi(argv[2]);
    int endindex = atoi(argv[3]);
    if (endindex > strsize) {
        return -1;
    }
    char cstr[strsize - endindex], asm_str[strsize - endindex];
    int sidx, eidx;
    sidx = startindex;
    eidx = endindex;
    char *d1 = sub_str(cstr, str, sidx, eidx);
    char *d2 = asm_sub_str(asm_str, str, sidx, eidx);
    printf("d1:%s\td2:%s\n", d1, d2);
    if (strcmp(d1, d2) == 0) {
        printf("The two strings are equal");
    } else {
        printf("The two strings are not equal");
    }
    return 0;
}