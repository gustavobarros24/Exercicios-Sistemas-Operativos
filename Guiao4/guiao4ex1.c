#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    int pd[2], m = 24;
    pipe(pd);
    if(fork() == 0){  //FILHO
        int v;
        close(pd[1]);
        read(pd[0], &v, sizeof(v));
        close(pd[0]);
        printf("filho: %d\n", v);
        _exit(0);
    }
    else{  //PAI
        close(pd[0]);
        sleep(5);
        write(pd[1], &m, sizeof(m));
        close(pd[1]);
    }
    return 0;
}