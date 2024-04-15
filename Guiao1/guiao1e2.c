#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]){
    char buffer[BUFSIZE];
    int n;
    int fdi = open(argv[1], O_RDONLY);
    if(fdi == -1){ //erro ao abrir o ficheiro de entrada
        perror(argv[1]);
        return 1;

    }
    int fdo = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fdo == -1){ //erro ao abrir o ficheiro de saída
        perror(argv[2]);
        close(fdi);
        return 1;
    }
    while((n = read(fdi, buffer, sizeof(buffer))) > 0){
        write(fdo, buffer, n);
    }
    close(fdi);
    close(fdo);
    return 0;
}