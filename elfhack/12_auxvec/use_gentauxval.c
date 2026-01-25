#include <stdio.h>
#include <sys/auxv.h>
int main(void) { printf("AT_RANDOM=0x%p\n",(void *) getauxval(AT_RANDOM));}
