#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILENAME "filepessoas"


typedef struct Person{
    char name[100];
    unsigned short age;
} Person;


int addperson (const char * name, unsigned short age){
    int fd = open(FILENAME, O_WRONLY, 0666);
    if(fd == -1){
        perror("fd");
        close(fd);
        return -1;
    }
    Person person;
    person.age = age;
    strcpy(person.name,name);

    write(fd, &person, sizeof(struct Person));

    close(fd);

    return 0;
}


int listpeople (unsigned short N){
    int fd = open(FILENAME, O_RDONLY, 0666);
    if(fd == -1){
        perror("fd");
        close(fd);
        return -1;
    }

    Person person;

    for(int i = 0; i < N; i++){
        ssize_t bytesread = read(fd, &person, sizeof(struct Person));
        if(bytesread == -1){
            perror("bytesread");
            close(fd);
            return -1;
        }
        char buffer[1024];
        
        int length = sprintf(buffer, "Person %d: %s, %d\n", i+1, person.name, person.age);
        write(STDOUT_FILENO, buffer, length);
    }
    close(fd);
    return 0;
}

int atualizaidade(const char * name, unsigned short age){
    int fd = open(FILENAME, O_RDWR, 0666);
    if(fd == -1){
        perror("fd");
        close(fd);
        return -1;
    }
    Person person;
    ssize_t bytesread = 0;
    while((bytesread = read(fd, &person, sizeof(struct Person))) > 0){
        if(strcmp(name, person.name) == 0){
            person.age = age;
            lseek(fd, -(sizeof(struct Person)), SEEK_CUR);
            write(fd, &person, sizeof(struct Person));
        }
    }
    close(fd);
    return 0;
}


int main(int argc, const char *argv[]){
    if(argc < 3){
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return -1;
    }

    if ( strcmp(argv[1],"-i") == 0 ){
        short age = atoi(argv[3]);
        addperson(argv[2], age);
    }

    if ( strcmp(argv[1],"-l") == 0 ){
        short n = atoi(argv[2]);
        listpeople(n);
    }

    if ( strcmp(argv[1],"-u") == 0 ){
        short age = atoi(argv[3]);
        atualizaidade(argv[2], age);
    }

    if ( strcmp(argv[1],"-o") == 0 ){
        //Meter um contador no add person, e mudar a função do -u
    }

    return 0;
}