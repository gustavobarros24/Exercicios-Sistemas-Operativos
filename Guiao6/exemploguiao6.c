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
        return -1;
    }
    //dup2(fd,STDERR_FILENO); Os erros passam a ir para o ficheiro.
    //dup2(fd,STDIN_FILENO); O input passa a vir do ficheiro.
    //dup2(fd,STDOUT_FILENO); O output passa a ir para o ficheiro.
    close(fd);
    execlp("ls","ls",NULL);
    perror("ls");
    return -1;
}