/* 案例：结构体传值。函数改的是副本，原来的学生不变。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

static void change(struct Student s)
{
    s.id = 9;
    s.name[0] = 'Z';
}

int main(void)
{
    struct Student stu = {1, "ann"};

    change(stu);
    printf("id = %d，name = %s\n", stu.id, stu.name);
    return 0;
}
