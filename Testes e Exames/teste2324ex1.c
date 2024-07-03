#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int sogpt(const char *prompt){
    int pd[2];
    pipe(pd);
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid==0){
        close(pd[0]);
        dup2(pd[1],STDOUT_FILENO);
        close(pd[1]);
        execlp("filter","filter",prompt,NULL);
        perror("execlp");
        _exit(-1);
    }
    close(pd[1]);
    int pd2[2];
    pipe(pd2);
    pid_t pid2 = fork();
    if(pid2 == -1){
        perror("pid2");
        _exit(-1);
    }
    //for (int i = 0; i < N; ++i){
    if(pid2 == 0){
        close(pd2[0]);
        dup2(pd[0],STDIN_FILENO);
        close(pd[0]);
        dup2(pd2[1],STDOUT_FILENO);
        close(pd[1]);
        execlp("execute","execute",prompt,NULL);
        perror("execlp");
        _exit(-1);
    }
    //}
    close(pd[0]);
    close(pd2[1]);

    pid_t pid3 = fork();
    if(pid3 == -1){
        perror("pid3");
        _exit(-1);
    }
    if(pid3 == 0){
        close(pd[1]);
        dup2(pd2[0], STDIN_FILENO);
        close(pd2[0]);
        execlp("merge","merge", prompt, NULL);
        perror("execlp");
        _exit(-1);
    }
    close(pd2[0]);
    int status;
    for(int i = 0; i < 3/*+N*/;i++){
        wait(&status);
        if(WIFEXITED(status)){
            printf("Processo filho %d terminou.",pid);
        }
    }
    return 0;
}


int main(int argc, const char *argv[]){
    char *prompt;
    strcpy(prompt, argv[1]);
    sogpt(prompt);
    return 0;
}