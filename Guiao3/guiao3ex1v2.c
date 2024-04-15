#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    char* args[] = { "ls", "-l", NULL};
    execvp("ls", args);
    perror("ls");
    return 1;
}