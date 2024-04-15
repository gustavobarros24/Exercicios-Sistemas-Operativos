#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define LINHAS 10
#define COLUMNS 100000


int main(int argc, char* argv[]){
    int pid;
    int status;
    int matrix[LINHAS][COLUMNS];
    for(size_t i = 0; i < LINHAS; i++){
        for(size_t j = 0; j < COLUMNS; j++){
            matrix[i][j] = 0;
            if(i == 8 && j == 24000){
                matrix[i][j] = 24;
            }
        }
    }
    printf("Preencheu a matriz com números\n");
    for(size_t i = 0; i < LINHAS; i++){
        int res = fork();
        if(res == 0){
            for(size_t j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == 24){
                    _exit(i+1);
                }
            }
            _exit(0);
        }
    }

    while((pid = wait(&status)) != -1){
        if(WIFEXITED(status)){
            printf("pai %d: filho %d devolveu %d\n", getpid(), pid, WEXITSTATUS(status));
        }
        else{
            printf("Erro\n");
        }
    }
    return 0;
}