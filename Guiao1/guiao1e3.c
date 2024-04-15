#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "filepessoas"

typedef struct Person{
    char name[100];
    unsigned short age;
} Person;

int addperson (const char * name, unsigned short age){
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1){
        perror("error opening file");
        close(fd);
        return -1;
    }

    Person person;
    person.age = age;
    strcpy(person.name, name);

    write(fd, &person, sizeof(struct Person));

    return 0;
}

int listpeople (unsigned short N){
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1){
        perror("error opening file");
        close(fd);
        return -1;
    }

    Person person;
    for(int i = 0; i<N; i++){
        ssize_t bytesread = read(fd, &person, sizeof(struct Person));
        if (bytesread == 0){
            perror("end of file");
            close(fd);
            break;
        }
        else if(bytesread == -1){
            perror("Read error");
            close(fd);
            return -1;
        }
        char buffer[1024];
        int len = sprintf(buffer, "Person %d: %s, %d\n", i + 1, person.name, person.age);

        write(STDOUT_FILENO, buffer, len);
    }

    close(fd);

    return 0;
}

int main(int argc, char* argv[]){

    if ( argc < 3 ){
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if ( strcmp(argv[1],"-i") == 0 ){
        addperson(argv[2], argv[3]);
    }

    if ( strcmp(argv[1],"-l") == 0 ){
        listpeople(argv[2]);
    }

    if ( strcmp(argv[1],"-u") == 0 ){
        // TO DO
    }

    if ( strcmp(argv[1],"-o") == 0 ){
        // TO DO
    }

    return 0;
}