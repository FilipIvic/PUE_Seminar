#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
    
int main() {
    char *buf;
    char *ptr;
    char *args[20];
    int n, pid;
    
    while((buf=readline(">> ")) != NULL) {
        if (strlen(buf) > 0) {
            add_history(buf);
            args[0] = strtok(buf, " ");
            n = 1;
            while((ptr=strtok(NULL, " ")) != NULL)
                args[n++] = ptr;
            args[n] = NULL;
        }        
        
        pid = fork();
        if (pid < 0) 
            perror("fork");
        else if (pid == 0) {   // CHILD
            execvp(args[0], args);
            perror("execvp");
        } else {
            wait(NULL);
        }
        
        free(buf);
    }

    printf("\n");
    return 0;
}
