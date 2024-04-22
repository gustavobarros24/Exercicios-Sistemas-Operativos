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

    int pid = fork();
    if (pid == 0){
        close(pd[1]);
        dup2(pd[0], 0);
        execlp("wc", "wc", NULL);
        close(pd[0]);
        _exit(1);
    }
    else{
        close(pd[0]);
        char buffer[1024];
        int readbytes = 0;
        while((readbytes = read(0, &buffer, 1024))>0){
            write(pd[1], &buffer, readbytes);
        }
        close(pd[1]);
        wait(NULL);
    }
    return 0;
}