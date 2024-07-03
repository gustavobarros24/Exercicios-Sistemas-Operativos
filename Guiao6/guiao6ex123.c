#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int fdinput = open("testeguiao6ex1.txt", O_RDONLY, 0666);
    if (fdinput == -1){
        perror("open");
        return -1;
    }

    int fderrors = open("errors.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fderrors == -1){
        perror("open");
        return -1;
    }

    int fdoutput = open("output.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fdoutput == -1){
        perror("open");
        return -1;
    }

    int stdin;
    if((stdin = dup2(fdinput, STDIN_FILENO))==-1){
        perror("dup2");
        return -1;
    }
    close(fdinput);

    int stderror;
    if((stderror = dup2(fderrors, STDERR_FILENO))==-1){
        perror("dup2");
        return -1;
    }
    close(fderrors);

    int stdout;
    if((stdout = dup2(fdoutput, STDOUT_FILENO))==-1){
        perror("dup2");
        return -1;
    }
    close(fdoutput);

    char msg[] = "Terminei.\n";

    write(stdout, &msg, sizeof(msg));
    int pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        execlp("wc", "wc", NULL);
        char error[] = "Erro.\n";
        write(stdout,&error,sizeof(error));
        _exit(-1);
    }
    else{
        int status;
        pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Processo filho %d terminou.",pid);
        }
    }
    return 0;
}