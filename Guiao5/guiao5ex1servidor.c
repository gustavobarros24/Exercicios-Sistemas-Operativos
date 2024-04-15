#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int fd = open("fifo", O_RDONLY, 0666);
    if(fd == -1){
        perror("Não conectou com o fifo");
        return -1;
    }
    char buffer[1024];
    int readbuffer = 0;
    while((readbuffer = read(fd, &buffer, sizeof(buffer)))>0){
        printf("%s\n",buffer);
    }
    close(fd);
    int pipe = unlink("fifo");
    if(pipe == -1){
        perror("fifo nao foi fechado");
        return -1;
    }
    return 0;
}