#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int pd[2], m = 8;
    pipe(pd);
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        close(pd[1]);
        int v;
        printf("Leitura do pipe vai ser iniciada\n");
        read(pd[0], &v, sizeof(v));
        close(pd[0]);
        printf("Filho recebeu: %d\n", v);
        _exit(0);
    }
    else{
        close(pd[0]);
        sleep(8);
        write(pd[1], &m, sizeof(m));
        printf("Pai enviou: %d\n",m);
        close(pd[1]);
    }
    return 0;
}