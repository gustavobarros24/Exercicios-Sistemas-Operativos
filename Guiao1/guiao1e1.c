#include <unistd.h>
#include <fcntl.h>

//1
int mycat(){
    int n;
    char buf[1024];
    while((n = read(0, buf, sizeof(buf))) > 0){
        write(1, buf, n);
    }
    return 0;
}
int main(int argc, char const *argv[]){
        mycat();
}