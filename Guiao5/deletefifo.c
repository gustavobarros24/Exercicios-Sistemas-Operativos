#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    unlink("fifoin");
    unlink("fifoout");
    return 0;
}