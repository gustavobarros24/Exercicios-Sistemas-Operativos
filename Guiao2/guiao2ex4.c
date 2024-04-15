#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    int res = fork();
    if (res == 0) {
        // FILHO
        printf("Sou o filho e o meu pid é %d | Parent id: %d\n", getpid(), getppid());
        sleep(1);
        _exit(32); // numero entre 0 e 255 (1000 => devolve depois 232 devido a overflow)
    } else {
        // PAI
        int status;
        // wait(&status);
        waitpid(res, &status, 0);
        if (WIFEXITED(status)) {
            printf("-----------\n");
            printf("Sou o pai (%d) e o filho (%d) devolveu %d.\n", getpid(), res, WEXITSTATUS(status));
        } else {
            printf("Erro.\n");
        }

    }
    for (int i = 0; i < 10; i++) {
        int res = fork();
        if (res == 0) {
            printf("[FILHO] PID: %d; PID-pai: %d\n", getpid(), getppid());
            sleep(1);
            _exit(i);
        }
    }

    int status;
    while (wait(&status) != -1) {
        if (WIFEXITED(status)) {
            printf("[PAI] Filho devolveu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Erro.\n");
        }
    }
    return 0;
}