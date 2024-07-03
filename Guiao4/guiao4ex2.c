#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int pd[2];
    int m = 8;
    pipe(pd);
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        close(pd[0]);
        write(pd[1], &m, sizeof(m));
        printf("O filho enviou o inteiro para o pipe\n");
        close(pd[1]);
        _exit(0);
    }
    else{
        int recebido = 0;
        close(pd[1]);
        //sleep(8);
        read(pd[0], &recebido, sizeof(recebido));
        printf("O pai recebeu %d do filho %d\n", recebido, pid);
        close(pd[0]);
    }
    return 0;
}