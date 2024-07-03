#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int pipe = mkfifo("fifo", 0666);
    if(pipe == -1){
        perror("pipe");
        return -1;
    }
    return 0;
}