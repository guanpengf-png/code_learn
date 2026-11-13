/* 案例：指向结构体的指针 +1，跨过一个学生。
   p 的类型是 struct Student *，一步是 sizeof *p，这里是 12 字节。
   p + 1 算出下一个学生的地址，并不自动改 p。
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
    struct Student *p = cls;     /* 指向 ann */
    struct Student *saved;
    struct Student *walk;
    struct Student *end = cls + 3; /* 最后一个学生的后面，不要 *end */
    int i;

    /* 一个学生 12 字节。p + 1 跨过这么多，落到 bob。 */
    printf("一个学生 %zu 字节，p + 1 跨过这么多\n", sizeof *p);

    /* p 指着 ann，这次读取没有改 p。 */
    printf("1. p->name\n");
    printf("  %s\n", p->name);
    /* (p + 1)->name、p[1].name、(*(p + 1)).name 都是 bob，id 是 2。p 仍指着 ann。 */
    printf("2. (p + 1)->name\n");
    printf("  %s\n", (p + 1)->name);
    printf("3. p[1].name\n");
    printf("  %s\n", p[1].name);
    printf("4. (*(p + 1)).name\n");
    printf("  %s\n", (*(p + 1)).name);
    printf("5. (p + 1)->id\n");
    printf("  %d\n", (p + 1)->id);

    /* 循环只改 i，p 一直指着开头。 */
    printf("6. p 不动，p[i].name\n");
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%s ", p[i].name);
    printf("\n");

    /* saved 留在 ann。p = p + 1 才把 p 自己改到 bob。 */
    saved = p;
    p = p + 1;
    printf("7. p = p + 1 之后 p->name，saved 仍是开头\n");
    printf("  %s %s\n", p->name, saved->name);

    /* walk < end 时才读，读完再 ++。end - cls 是学生个数 3，不是字节数。 */
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

    /* walk 先放在 end。先 -- 再读，顺序是 cy bob ann，也不会移到数组开头的前面。 */
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
