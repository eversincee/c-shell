#include <stdio.h>

int main() {
    printf("> ");
    fflush(stdout);
    char line[1024];
    fgets(line, sizeof(line), stdin);
    return 0;
}
