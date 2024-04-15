#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(){
    int fd = open("fifo", O_WRONLY, 0666);
    if(fd == -1){
        perror("Não ligou ao fifo");
        return -1;
    }

    char buffer[1024];
    int readbytes = 0;
    while((readbytes = read(0, &buffer, sizeof(buffer)))>0){
        write(fd, &buffer, sizeof(buffer));
    }
    close(fd);
    return 0;
}