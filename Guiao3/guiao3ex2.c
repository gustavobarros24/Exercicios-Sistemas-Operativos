#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    pid_t pid = fork();

    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        _exit(-1);
    }
    else{
        int status;
        wait(&status);
        printf("Terminou processo %d: %d\n", pid, WEXITSTATUS(status));
    }
}