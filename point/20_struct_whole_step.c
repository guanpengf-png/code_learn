/* 案例：指向结构体数组的指针 +1，跨过这一整组学生。 */
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
    struct Student (*all)[3] = &cls;

    printf("组里第一个是 %s\n", (*all)[0].name);
    printf("all + 1 跨过 %zu 字节\n", sizeof(*all));
    return 0;
}
