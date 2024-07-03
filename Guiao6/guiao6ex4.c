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
    if (pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        close(pd[1]);
        dup2(pd[0],STDIN_FILENO);
        execlp("wc","wc",NULL);
        close(pd[0]);
        _exit(-1);
    }
    else{
        close(pd[0]);
        char buffer[1024];
        int readbytes = 0;
        while((readbytes=read(STDIN_FILENO,buffer,sizeof(buffer)))>0){
            write(pd[1],buffer,sizeof(buffer));
        }
        close(pd[1]);
        int status;
        pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Processo filho %d terminou.\n",pid);
        }
    }
    return 0;
}