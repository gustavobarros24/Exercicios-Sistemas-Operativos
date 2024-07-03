#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int mycp(const char *arg1, const char *arg2){
    char buff[1024];
    int fdi = open(arg1, O_RDONLY,0666);
    if(fdi == -1){
        perror("fdi");
        return -1;
    }
    int fdo = open(arg2, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fdo == -1){
        perror("fdi");
        return -1;
    }
    int in;
    while((in = read(fdi,buff,sizeof(buff))) > 0){
        write(fdo,buff,in);
    }
    close(fdi);
    close(fdo);
    return 0;
}


int main(int argc, const char *argv[]){
    const char *filei = argv[1];
    const char *fileo = argv[2];
    mycp(filei,fileo);
    return 0;
}