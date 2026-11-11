#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_LEN 32
#define DATA_FILE "student.txt"
typedef struct Student{
    int i;
    char name[NAME_LEN];
    float chinese;
    float math;
    float english;
}Student;

int main(){
    Student* head=NULL;
    int choice;
    int n=list_load(&head,DATA_FILE);
    if (n>0)
    {
        printf("%sload student,%d",DATA_FILE,n);
    }else{
        printf("no %s student",DATA_FILE);
    }

    

    return 0;
}