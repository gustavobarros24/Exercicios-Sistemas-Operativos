#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, const char *argv[]){
    srand(time(NULL));
	int matrix[10][10];
	printf("Generating random matrix...\n");
	for(size_t i = 0; i < 10; i++) {
		for(size_t j = 0; j < 10; j++) {
			matrix[i][j] = rand() % 10;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Random matrix generated.\n");
    int value = 8;
    int v[100];
    int pd[2];
    pipe(pd);
    for(int i = 0; i<10; i++){
        pid_t pid = fork();
        if(pid == -1){
            perror("pid");
            _exit(-1);
        }
        if(pid == 0){
            close(pd[0]);
            for(int j = 0; j<10; j++){
                if(matrix[i][j] == value){
                    write(pd[1], &matrix[i][j], sizeof(int));
                }
            }
            close(pd[1]);
            _exit(0);
        }
    }
    close(pd[1]);
    int bytesread = 0;
    int recebido;
    int i = 0;
    while((bytesread = read(pd[0], &recebido, sizeof(int)))>0){
        v[i] = recebido;
        i++;
    }
    close(pd[0]);
    for (int i = 0; i < 10; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}