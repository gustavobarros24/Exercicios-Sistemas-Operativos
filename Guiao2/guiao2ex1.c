#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    printf("Pid do processo: %d\nPid do pai: %d\n", getpid(), getppid());
    return 0;
}