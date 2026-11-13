/* 案例：结构体传地址。s->id 改的是原来的学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

static void change(struct Student *s)
{
    s->id = 9;
    s->name[0] = 'Z';
}

int main(void)
{
    struct Student stu = {1, "ann"};

    change(&stu);
    printf("id = %d，name = %s\n", stu.id, stu.name);
    return 0;
}
