#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int sistema(const char* comando){
    pid_t pid;
    int status;
    if((pid = fork()) == 0){
        char** args = NULL, *ptr = strdup(comando) , *token = NULL;
        int i = 0;
        while((token = strsep(&ptr, " ")) != NULL){
            args = realloc(args, sizeof(char*) * (i+1));
            args[i] = strdup(token);
            i++;
        }
        args = realloc(args, sizeof(char*) * (i+1));
        args[i] = NULL;
        execvp(args[0], args);
        perror(args[0]);
        _exit(1);
    }
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status): 1;
}

int main(int argc, char* argv[]){
    sistema("ls");
    return 0;
}