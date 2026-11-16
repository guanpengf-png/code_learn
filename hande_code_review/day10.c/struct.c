#include <stdio.h>
struct stu
{
    int id;
    char*name;
    char gender;
    int age;
    int math_score;
};
// struct Person{
//     char*name;
//     char gender;
//     int age;

// };
struct Person{
    char*name;
    char gender;
    int age;

}p1;
struct Person p2;
struct Person p3={"xiao",'f',10};
struct Person p4={.age=10,.gender='m',.name="xiao"};
int main(int argc, char const *argv[])
{
    p1.age=101;
    p1.gender='m';
    p1.name="iverson";
    p2.age=101;
    p2.gender='m';
    p2.name="iverson";
    printf("p1 id%d gender %c p1 name?%s",p1.age,p1.gender,p1.name);
    printf("p1 id%d gender %c p1 name?%s",p2.age,p2.gender,p2.name);
    printf("p1 id%d gender %c p1 name?%s",p3.age,p3.gender,p3.name);
    printf("p1 id%d gender %c p1 name?%s",p4.age,p4.gender,p4.name);


    return 0;
}
