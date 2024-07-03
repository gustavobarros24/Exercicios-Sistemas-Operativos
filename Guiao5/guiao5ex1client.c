#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int fd = open("fifo", O_WRONLY, 0666);
    if(fd == -1){
        perror("fd");
        return -1;
    }

    char buff[1024];
    int readbytes = 0;
    while((readbytes = read(STDIN_FILENO, &buff, sizeof(buff)))>0){
        write(fd, &buff, sizeof(buff));
    }
    close(fd);
    return 0;
}