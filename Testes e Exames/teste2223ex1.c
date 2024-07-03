#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int defeitos(char *imagens[], int N, int max){
    int processoscurr = 0;
    for(int i = 0; i<N; i++){
        while(processoscurr >= max){
            int status;
            wait(&status);
            processoscurr--;
        }
        pid_t pid = fork();
        if(pid == -1){
            perror("pid");
            _exit(-1);
        }
        if(pid == 0){
            execlp("./detectAnom","detectAnom",imagens[i],NULL);
            perror("execlp");
            _exit(-1);
        }
        else{
            processoscurr++;
        }
    }
    while(processoscurr>0){
        int status;
        wait(&status);
        processoscurr--;
    }
}


int main(int argc, const char *argv[]){
    
    return 0;
}