/* 案例：指向结构体的指针 +1，跨过一个学生。
   cls 是 ann、bob、cy。 */
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
    struct Student *saved;
    struct Student *walk;
    struct Student *end = cls + 3;
    int i;

    printf("一个学生 %zu 字节，p + 1 跨过这么多\n", sizeof *p);

    printf("1. p->name\n");
    printf("  %s\n", p->name);
    printf("2. (p + 1)->name\n");
    printf("  %s\n", (p + 1)->name);
    printf("3. p[1].name\n");
    printf("  %s\n", p[1].name);
    printf("4. (*(p + 1)).name\n");
    printf("  %s\n", (*(p + 1)).name);
    printf("5. (p + 1)->id\n");
    printf("  %d\n", (p + 1)->id);

    printf("6. p 不动，p[i].name\n");
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%s ", p[i].name);
    printf("\n");

    saved = p;
    p = p + 1;
    printf("7. p = p + 1 之后 p->name，saved 仍是开头\n");
    printf("  %s %s\n", p->name, saved->name);

    printf("8. walk++ 从前往后\n");
    printf("  ");
    walk = cls;
    while (walk < end) {
        printf("%s ", walk->name);
        walk++;
    }
    printf("\n");
    printf("9. end - cls\n");
    printf("  %ld\n", (long)(end - cls));

    printf("10. 从最后一个往回走\n");
    printf("  ");
    walk = end;
    while (walk > cls) {
        walk--;
        printf("%s ", walk->name);
    }
    printf("\n");
    return 0;
}
