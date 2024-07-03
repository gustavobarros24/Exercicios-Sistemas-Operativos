#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int mycat(){
    char buff[1024];
    int in = read(STDIN_FILENO, buff, sizeof(buff));
    if(in == -1){
        perror("in");
        return -1;
    }
    while(in>0){
        write(STDOUT_FILENO, buff, in);
        in = read(STDIN_FILENO, buff, sizeof(buff));
    }
    close(in);
    return 0;
}


int main(int argc, char const *argv[]){
    mycat();
    return 0;
}