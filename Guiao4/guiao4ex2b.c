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
    int n[5] = {1, 2, 3, 4, 5};
    pipe(pd);
    pid_t pid = fork();
    if(pid == -1){
        perror("pid");
        _exit(-1);
    }
    if(pid == 0){
        close(pd[0]);

        for(int i = 0; i < 5; i++){
            write(pd[1], &n[i], sizeof(int));
            sleep(2);
        }
        close(pd[1]);
        _exit(0);
    }
    else{
        close(pd[1]);
        int recebido;
        int bytesread = 0;
        while((bytesread = read(pd[0], &recebido, sizeof(int)))>0){
            printf("Sou o pai e recebi: %d\n", recebido);
        }
        close(pd[0]);
    }
    return 0;
}