#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_TOKENS 64
#define DELIMITER " \t\n"

void tokenize(char *line, char **tokens);

int execute(char **args);

int sh_cd(char **args);
int sh_exit(char **args);

int main() {
    int status = 1;

    while (status) {
        printf("> ");
        fflush(stdout);

        char line[1024];
        fgets(line, sizeof(line), stdin);

        char *args[MAX_TOKENS + 1];
        tokenize(line, args);
        
        if (args[0] == NULL) {
            continue;
        }

        status = execute(args);
    }

    return 0;
}

void tokenize(char *line, char **tokens) {
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

int sh_cd(char **args) {
    if (args[1] == NULL) {
        perror("expected argument to cd");
    } else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }

    return 1;
}

int sh_exit(char **args) {
    return 0;
}

int execute(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        return sh_cd(args);
    }

    if (strcmp(args[0], "exit") == 0) {
        return sh_exit(args);
    }
    
    int status;
    pid_t wpid;
    pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        _exit(1);
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
