#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    pid = fork();
    switch (pid){
        case -1: //erro
            perror("fork()");
            _exit(1);
        case 0: //filho
            //sleep(1); //faz com que nunca imprima o pid do pai pois imprime o pid do processo inicial do linux
            printf("filho pid = %d\n, ppid = %d\n", getpid(), getppid());
            _exit(0);
        default: //pai
            printf("pai pid = %d\n, ppid = %d\n, filho = %d\n", getpid(), getppid(), pid);
    }
    return 0;
}