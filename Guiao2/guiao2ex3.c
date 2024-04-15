#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    int i, status;
    pid_t pid;
    for(i=0; i!=10; i++){
        if(fork()==0){//filho
            printf("filho %d: pid = %d, ppid %d\n", i+1, getpid(), getppid());
            return i+1;
        }
        //pai
        pid = wait(&status);
        if(WIFEXITED(status)){
            printf("pai %d: filho %d, %d\n",getpid(), pid, WEXITSTATUS(status));
        }
        else {
            printf("pai %d: filho morreu sem status no wifexited(status)");
        }
    }
    return 0;
}