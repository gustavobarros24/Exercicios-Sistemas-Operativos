#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int v[28] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8};
    int pipein = mkfifo("fifoin", 0666);
    if(pipein == -1){
        perror("pipein");
        return -1;
    }
    int pipeout = mkfifo("fifoout", 0666);
    if(pipeout == -1){
        perror("pipeout");
        return -1;
    }
    int alert = 0;
    while(alert == 0){
        int fdin = open("fifoin", O_RDONLY, 0666);
        int n;
        read(fdin, &n, sizeof(int));
        if(n == 228){
            break;
        }
        printf("%d foi lido", n);
        close(fdin);
        /*pid_t pid = fork();
        if(pid == -1){
            perror("pid");
            _exit(-1);
        }
        if(pid == 0){
            int count = 0;
            for(int i = 0; i < 28; i++){
                if(v[i] == n){
                    count++;
                }
            }
            int fdout = open("fifoout", O_WRONLY, 0666);
            write(fdout, &count, sizeof(int));
            close(fdout);
            _exit(0);
        }
        else{
            int status;
            pid = wait(&status);
            if(WIFEXITED(status)){
                printf("Processo filho %d terminou com sucesso.", pid);
            }
        }
        */
        int count = 0;
        for(int i = 0; i < 28; i++){
            if(v[i] == n){
                count++;
            }
        }
        int fdout = open("fifoout", O_WRONLY, 0666);
        write(fdout, &count, sizeof(int));
        close(fdout);
    }
    int fifounin = unlink("fifoin");
    int fifounout = unlink("fifoout");
    return 0;
}