/* 案例：指向结构体的指针 +1，跨过一个学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

int main(void)
{
    struct Student cls[3] = {
        {1, "ann"},
        {2, "bob"},
        {3, "cy"}
    };
    struct Student *p = cls;

    printf("现在是 %s\n", p->name);
    p = p + 1;
    printf("走一步之后是 %s\n", p->name);
    return 0;
}
