#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int fd = open("fifo", O_RDONLY, 0666);
    if(fd == -1){
        perror("fd");
        return -1;
    }
    char buff[1024];
    int bytesread = 0;
    while((bytesread = read(fd, &buff, sizeof(buff)))>0){
        printf("%s\n",buff);
    }
    close(fd);
    int pipe = unlink("fifo");
    if(pipe == -1){
        perror("pipe");
        return -1;
    }
    return 0;
}