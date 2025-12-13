#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 64
#define DELIMITER " "
void **tokenize(char *line, char **tokens) {
    int i = 0;
    char *token;
    
    token = strtok(line, DELIMITER);

    while (token != NULL && i < MAX_TOKENS) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, DELIMITER);
    }
    
    tokens[i] = NULL;
}

int main() {
    printf("> ");
    fflush(stdout);

    char line[1024];
    fgets(line, sizeof(line), stdin);
    
    char *args[MAX_TOKENS + 1];
    tokenize(line, args);

    return 0;
}
