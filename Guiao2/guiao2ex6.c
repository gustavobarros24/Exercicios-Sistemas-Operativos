#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define M 10000000

void incializa_palheiro(int palheiro[N][M]){
    //inicialiar a ero e semear a "agulha"
    memset(palheiro, 0, sizeof(int)*N*M);
    palheiro[2][100000] = palheiro[3][20000] = 7;
    //alternativamente, inicializar o palheiro aleatoriamente
}

int palheiro[N][M];

int main(int argc, char* argv[]){
    int agulha = atoi(argv[1]);
    int i, j;
    pid_t filho[N];

    incializa_palheiro(palheiro);
    for(i = 0; i != N; i++){
        filho[i] = fork(); //array para armazenar os pids dos processos que encontram o numero para depois retornar em que linha estava
        if(filho[i] == 0){
            for(j; j != M && palheiro[i][j] != agulha; j++){
                return j != M; // 1 se encontrou agulha, e substitui o _exit(0) ou _exit(1)
            }
        }
    }
    for(i = 0; i != N; i++){
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)){
            for(j = 0; j != N && filho[j] != pid; j++)
            if(WEXITSTATUS(status)){
                for(j = 0; j != N && filho[j] != pid; j++){
                    printf("agulha na linha %d do palheiro \n", j);
                    //return 0;
                }
                //printf("filho encontrou a agulha na sua linha do palheiro");
                //return 0; //o pai termina antes de esperar pelos filhos todos, mas os outros filhos ficam a executar, no caso seria utiliado os sinais para esses filhos acabarem
            }
        }
    }
    return 0;
}