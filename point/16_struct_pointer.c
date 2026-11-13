/* 案例：结构体指针。sp->id 就是 (*sp).id。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

int main(void)
{
    struct Student stu = {1, "ann"};
    struct Student *sp = &stu;

    printf("sp->id = %d，sp->name = %s\n", sp->id, sp->name);
    sp->id = 9;
    printf("改完之后 stu.id = %d\n", stu.id);
    return 0;
}
