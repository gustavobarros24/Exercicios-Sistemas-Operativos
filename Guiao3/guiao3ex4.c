#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define MAXPROCS 10


int main(int argc, char* argv[]) {
    pid_t pids[MAXPROCS], pid;
    int nexecs[MAXPROCS], pexec = 0, status, i;
    for(i = 0; i != argc-1;i++,pexec++){
        if((pids[i] = fork()) == 0){
            execlp(argv[i+1], argv[i+1], NULL);
            perror(argv[i+1]);
            _exit(1);
        }
        nexecs[i] = 1;
    }
    while(pexec > 0){
        pid = wait(&status);
        for(i = 0; i != argc-1 && pids[i] != pid; i++);
        if(WIFEXITED(status) && WEXITSTATUS(status == 0)){
            pexec--;
            pids[i] = 0;
        }
        else{
            if((pids[i] = fork()) == 0){
                execlp(argv[i+1], argv[i+1], NULL);
                perror(argv[i+1]);
            }
            nexecs[i]++;
        }
    }
    for(i = 0; i < argc-1; i++){
        printf("(%d) %s: %d\n", pids[i], argv[i], nexecs[i]);
    }
    return 0;
}