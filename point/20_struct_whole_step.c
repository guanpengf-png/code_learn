/* 案例：指向结构体数组的指针 +1，跨过这一整组学生。
   room 有 2 组，每组 3 个学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

int main(void)
{
    struct Student room[2][3] = {
        {
            {1, "ann"},
            {2, "bob"},
            {3, "cy"}
        },
        {
            {4, "dee"},
            {5, "ed"},
            {6, "fay"}
        }
    };
    struct Student (*all)[3] = room;
    int i;

    printf("一个学生 %zu 字节，all 一步 %zu 字节\n",
           sizeof room[0][0], sizeof *all);

    printf("1. (*all)[0].name\n");
    printf("  %s\n", (*all)[0].name);
    printf("2. (*(all + 1))[0].name\n");
    printf("  %s\n", (*(all + 1))[0].name);
    printf("3. all[1][2].name\n");
    printf("  %s\n", all[1][2].name);
    printf("4. (*all + 2)->name\n");
    printf("  %s\n", (*all + 2)->name);
    printf("5. (all[1] + 1)->name\n");
    printf("  %s\n", (all[1] + 1)->name);

    printf("6. 第一组\n");
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%s ", (*all)[i].name);
    printf("\n");
    printf("7. 第二组\n");
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%s ", (*(all + 1))[i].name);
    printf("\n");

    all = all + 1;
    printf("8. all = all + 1 之后 (*all)[0].name\n");
    printf("  %s\n", (*all)[0].name);
    return 0;
}
