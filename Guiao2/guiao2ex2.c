#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        printf("Pid do filho(no processo filho): %d\nPid do pai(no processo filho): %d\n", getpid(), getppid());
        _exit(0);
    }
    else{
        printf("Pid do pai(no processo pai): %d\nPid do filho(no processo pai): %d\nPid do pai do pai: %d\n", getpid(), pid, getppid());
    }
    return 0;
}