#define _GNU_SOURCE
char *gets(char *s);  // Explicit declaration of gets()
#include <stdio.h>
#include <time.h>
//#include <gnu/libc-version.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdint.h>

char* inputRead() {
    char vulnChar[32];
    printf("Where do you want to aim? (hex): ");
    gets(vulnChar);
    static char returner[4096];
    strcpy(returner, vulnChar);
    return returner;
}



void leftBorder() {
	return;
}


void the_green() {
    __asm__ __volatile__ (
        ".rept 8000 \n\t"  // 8 KB of NOPs
        "nop\n\t"
        ".endr\n\t"
    );
}

int main() {
    srand(time(NULL));
    int hole = rand() % 8000;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    void* handle = dlopen("libc.so.6", RTLD_NOW);
    if (!handle) {
        perror("dlopen");
        exit(1);
    }

    // Get base address of a known libc symbol
    Dl_info info;
    dladdr((void*)puts, &info);
    void* libc_base = (void*)((uintptr_t)info.dli_fbase & ~0xfff);

    void* target = libc_base + 0x026D60;

    // Print the address of a known libc function for easy testing
    //printf("Address of libc function printf: %p\n", (void *)printf);
    //printf("  malloc: %p\n", (void *)malloc);
    //printf("  free:   %p\n", (void *)free);
    printf("Welcome to golf. You just gotta get the ball into the hole :). To quit your session, use ctrl + c. \n \n");
    printf("Please stay within the borders: %p and %p\n", (void *)leftBorder, (void *)target);
    //printf("  main: %p\n", (void *)main);

//    printf("  strlen: %p\n", (void *)strlen);
    int playing = 1;
    while (playing) {
	//char input[32];
    	//printf("Where do you want to aim? (hex): ");
    	//gets(input);
	char* input = inputRead();
        char *endptr;
        void *addr = (void *)strtoull(input, &endptr, 16);

	if (addr == (void*)the_green+hole){
            printf("\nYou got the ball in the hole!!! But there's no flag here. ):\n");
            playing = 0;
        }else if (dladdr(addr, &info) && info.dli_sname) {
            printf("\nYour ball landed on %s\n", info.dli_sname);
            printf("This sections seems to start at %p\n", info.dli_saddr);
        } else if (addr == target) {
            printf("\nYour ball landed on rightBorder\n");
            printf("This sections seems to start at %p\n", addr);
        } else {
            printf("\nThere's nothing to land on at %p\n", addr);
        }
    }
    return 0;
}


