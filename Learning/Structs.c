#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight){
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who){
    assert(who != NULL);
    free(who->name);
    free(who);
}

void Person_print(struct Person *who){
    printf("+-----------------------+\n");
    printf("|Name: %s\t|\n", who->name);
    printf("|\tAge: %d\t\t|\n", who->age);
    printf("|\tHeight: %d\t|\n",who->height);
    printf("|\tWeight: %d\t|\n",who->weight);
    printf("+-----------------------+\n");
}

int main(int argc, char *argv[]){
    struct Person *Alex = Person_create("Alexander",26,65,70);
    printf("Alex's memory is at: %p\n", &Alex);

    struct Person Jonas = {"Jonas",20,55,22};
    
    Alex->age += 20;
    Alex->height += 0;
    Alex->weight += 10;

    Person_print(Alex);
    Person_print(&Jonas);

    Person_destroy(Alex);
    printf("\n");

    return 0;
}
