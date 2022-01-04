#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int pid, status, fd;
    
    if (argc < 3) {
        printf("koristenje: %s <datotek> <naredba> [argument1] ...\n", argv[0]);
        return 0;
    }
    
    if ((pid=fork()) < 0) { // ERROR
        perror("fork");
    } else if (pid==0) {    // CHILD
        fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd < 0) {
            perror("open");
            return 100;
        }
        dup2(fd, STDOUT_FILENO);
        if (fd != STDOUT_FILENO)
            close(fd);
        execvp(argv[2], &argv[2]);
        perror("execvp");
        return 200;
    } else {		    // PARRENT
        wait(&status);
        if (WIFEXITED(status)) 
            printf("STATUS: %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("SIGNAL: %d\n", WTERMSIG(status));
        else 
            printf("UNKNOWN\n");
    }
    
    return 0;
}
