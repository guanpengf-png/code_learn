#include <stdio.h>
#include <string.h>
struct Person
{
    char namep[10];
    int age;
    int price;
};
struct Person p;
void pay_mooney(struct Person*p){
     p->price=p->age>18?20:0;
}



int main(int argc, char const *argv[])
{
    struct Person p;
    while (1)
    {
        scanf("%d %s",&p.age,p.namep);
        if (!strcmp(p.namep,"xiao"))
        {
        break;
        }
    }
    
    pay_mooney(&p);
    printf("price%d name%s: age%d",p.price,p.namep,p.age);

    

    
    return 0;
}

