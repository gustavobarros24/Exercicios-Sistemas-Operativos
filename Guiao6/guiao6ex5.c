#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int pd[2];
    pipe(pd);

    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        close(pd[0]);
        dup2(pd[1], STDOUT_FILENO);
        close(pd[1]);
        execlp("ls","ls","/etc",NULL);
        perror("execlp");
        _exit(-1);
    }
    else{
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            close(pd[1]);
            dup2(pd[0],STDIN_FILENO);
            close(pd[0]);
            execlp("wc", "wc", "-l", NULL);
            perror("execlp");
            return -1;
        }
    }
    return 0;
}