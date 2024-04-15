#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

//gcc -Wall guiao3ex1.c -o guiao3ex1
int main(int argc, char* argv[]){
    execlp("ls", "ls", "-l", NULL);
    perror("Erro ao executar o comando ls.");
    return 1;
}