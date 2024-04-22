#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int fd = open("ls.txt", O_CREAT|O_APPEND|O_WRONLY, 0666);
    if(fd == -1){
        perror("ls.txt");
        return 1;
    }   
    dup2(fd,2);
    close(fd);
    execlp("ls","ls",NULL);
    perror("ls");
    return 1;
}