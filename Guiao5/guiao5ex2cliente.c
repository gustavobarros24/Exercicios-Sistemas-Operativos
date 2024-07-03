#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    int fdin = open("fifoin", O_WRONLY, 0666);
    int n = atoi(argv[1]);
    if(strcmp(argv[1],"exit") == 0){
        n = 228;
    }
    printf("%d", n);
    write(fdin, &n, sizeof(int));
    close(fdin);
    if(n == 228){
        return 0;
    }
    int fdout = open("fifoout", O_RDONLY, 0666);
    int numeroocorr = 0;
    read(fdout,&numeroocorr,sizeof(int));
    close(fdout);
    printf("O número de occorências do número %d foi %d\n", n, numeroocorr);
    return 0;
}