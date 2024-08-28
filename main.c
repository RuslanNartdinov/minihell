#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("\033[32m" " minishell> ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
         for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    return 0;
}