#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    for(int i = 0; i < 10; i++){
        int res = fork();
        if(res == 0){
            printf("[FILHO] PID: %d; PID-pai: %d\n", getpid(), getppid());
            sleep(1);
            _exit(i+1);
        }
    }
    int status;
    
    while(wait(&status) != -1){
        if(WIFEXITED(status)){
            printf("[PAI] Filho devolveu: %d\n", WEXITSTATUS(status));
        }
        else{
            printf("Erro.\n");
        }
    }
    return 0;
}