#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int status;
    pid_t pid;
    for(int i = 0; i < 10; i++){
        if(fork() == 0){
            printf("Pid do filho(no processo filho): %d\nPid do pai(no processo filho): %d\n", getpid(), getppid());
            _exit(0);
        }
        else{
            pid = wait(&status);
            if(WIFEXITED(status)){
                printf("Pid do pai(no processo pai): %d\nPid do filho(no processo pai): %d\nPid do pai do pai: %d\n", getpid(), pid, getppid());
            }
            else{
                printf("Filho morreu sem status.\n");
            }
        }
    }
    return 0;
}