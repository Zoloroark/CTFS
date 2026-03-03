#define _GNU_SOURCE
char *gets(char *s);
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

int is_valid_format(char *input) {
    regex_t regex;
    // matches %p or %<digits>$p, rejects everything else with %
    regcomp(&regex, "%([0-9]+\\$)?p", REG_EXTENDED);
    char *ptr = input;
    while (*ptr) {
        if (*ptr == '%') {
            regmatch_t match;
            if (regexec(&regex, ptr, 1, &match, 0) != 0 || match.rm_so != 0) {
                regfree(&regex);
                return 0;  // invalid
            }
            ptr += match.rm_eo;
        } else {
            ptr++;
        }
    }
    regfree(&regex);
    return 1;  // valid
}



char* inputRead() {
    char vulnChar[40];
    printf("Where do you want to mine out? (hex): ");
    gets(vulnChar);

    static char returner[4096];
    strcpy(returner, vulnChar);
    return returner;
}

void mineStart() {
    return;
}

void the_cage() {
    __asm__ __volatile__ (
        ".rept 24000 \n\t"
        "nop\n\t"
        ".endr\n\t"
    );
}

int main() {
    srand(time(NULL));
    int birdie = rand() % 24000;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    void* handle = dlopen("libc.so.6", RTLD_NOW);
    if (!handle) {
        perror("dlopen");
        exit(1);
    }

    Dl_info info;
    dladdr((void*)puts, &info);
    void* libc_base = (void*)((uintptr_t)info.dli_fbase & ~0xfff);
    void* target = libc_base + 0x026D60;

    printf("Welcome to the mines. Just a whole lot of coal and a cage somewhere. To quit your session, use ctrl + c. \n \n");
    printf("Please name your mine: ");
//    int c;
//    while ((c = getchar()) != '\n' && c != EOF);
    char buffer [256];
    char* input = fgets(buffer, sizeof(buffer), stdin);
    input[strcspn(input, "\n")] = 0;
    if (!is_valid_format(input)) {
        printf("No is a nice name!\n");
    } else {
        printf(input);
        printf(" is a nice name!\n");
    }
    printf("The mine extends from %p to %p\n", (void *)mineStart, (void *)target);

    int playing = 1;
    while (playing) {
        char* input = inputRead();
        char *endptr;
        void *addr = (void *)strtoull(input, &endptr, 16);
        if (addr == (void*)the_cage+birdie){
            printf("\ntweet tweet\n");
//            printf("\n0x%lx\n", stack_canary);
        } else if (dladdr(addr, &info) && info.dli_sname) {
            printf("\nYou have found %s\n", info.dli_sname);
            printf("This seems to start at %p\n", info.dli_saddr);
        } else if (addr == target) {
            printf("\nYou have found mineEnd\n");
            printf("This seems to start at %p\n", addr);
        } else {
            printf("\nDarkness\n");
        }
    }
    return 0;
}
