#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int sistema(const char *comando){
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        char** args = NULL, *aux = strdup(comando), *token = NULL;
        int i = 0;
        while((token = strsep(&aux, " ")) != NULL){
            args = realloc(args, sizeof(char*) * (i+1));
            args[i] = strdup(token);
            i++;
        }
        args = realloc(args, sizeof(char*) * (i+1));
        args[i] = NULL;
        execvp(args[0], args);
        perror("execvp");
        _exit(-1);
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WIFEXITED(status): -1;
    }
}


int main(int argc, char *argv[]){
    sistema("ls");
    return 0;
}