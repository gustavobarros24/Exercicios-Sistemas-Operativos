#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


typedef struct Req{
    pid_t pid;
    char *prompt;
} Req;


int servidor(){
    int pipe = mkfifo("fifo_server",0666);
    if(pipe == -1){
        perror("pipe");
        _exit(-1);
    }
    while(1){
        Req r;
        int fd = open("fifo_serrver", O_RDONLY, 0666);
        int id;
        int bytesread;
        pid_t pid;
        while((bytesread = read(fd, &r, sizeof(struct Req)))>0){
            pid = fork();
            if(pid == -1){
                perror("pid");
                _exit(-1);
            }
            if(pid == 0){
                execlp("sogpt","sogpt",r.prompt,NULL);
                perror("execlp");
                _exit(-1);
            }
            else{
                int status;
                pid = wait(&status);
                if(WIFEXITED(status)){
                    int fd2 = open("fifoc_name",O_WRONLY,0666);
                    write(fd2, &(id), sizeof(int));
                    id++;
                    close(fd2);
                }
            }
        }
        close(fd);
    }
    unlink("fifo_server");
    return 0;
}


int main(int argc, const char *argv[]){
    servidor();
    return 0;
}