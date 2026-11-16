#include<stdio.h>
typedef char*String;
typedef int Int;
typedef struct 
{
    Int id;
    String name;
    Int age;
   
}Person;

int main(int argc, char const *argv[])
{
    Person p;
    p.age=10;
    p.name="xiao";
    p.id=1;
    printf("%d %s %d ",p.age,p.name,p.id);
   
    return 0;
}
