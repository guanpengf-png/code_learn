/* 案例：指向结构体数组的指针 +1，跨过这一整组学生。
   all 的类型是 struct Student (*)[3]，一步是 3 个学生，这里是 36 字节。
   room 有 2 组：ann bob cy，以及 dee ed fay。 */
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
    struct Student (*all)[3] = room; /* 指向第 0 组 */
    int i;

    /* 一个学生 12 字节，all 一步跨过一整组 36 字节。 */
    printf("一个学生 %zu 字节，all 一步 %zu 字节\n",
           sizeof room[0][0], sizeof *all);

    /* (*all) 是第 0 组，[0] 是 ann。all 自己没动。 */
    printf("1. (*all)[0].name\n");
    printf("  %s\n", (*all)[0].name);
    /* all + 1 先跨过一整组，再取那组的第 0 个，是 dee。 */
    printf("2. (*(all + 1))[0].name\n");
    printf("  %s\n", (*(all + 1))[0].name);
    /* all[1] 就是 *(all + 1)。第 1 组第 2 个是 fay。 */
    printf("3. all[1][2].name\n");
    printf("  %s\n", all[1][2].name);
    /* *all 退化成 struct Student *，再 + 2 是第 0 组的 cy。
       all[1] + 1 是第 1 组的 ed。 */
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

    /* 这一次 all 自己跨过 36 字节，站到第 1 组。(*all)[0] 变成 dee。 */
    all = all + 1;
    printf("8. all = all + 1 之后 (*all)[0].name\n");
    printf("  %s\n", (*all)[0].name);
    return 0;
}
