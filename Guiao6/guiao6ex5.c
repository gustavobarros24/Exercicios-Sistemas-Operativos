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
    if(fork() == 0){
        dup2(pd[1], 1);
        close(pd[0]);
        close(pd[1]);
        execlp("ls", "ls", "/etc", NULL);
        perror("ls");
        return 1;
    }
    else{
        dup2(pd[0], 0);
        close(pd[0]);
        close(pd[1]);
        execlp("wc", "wc", "-l", NULL);
        perror("wc");
        return 1;
    }
}