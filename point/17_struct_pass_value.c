/* 案例：结构体传值。函数改的是副本。
   副本里的指针和外面指着同一个 int，*s.score 会改到那个 int。
   给副本的 score 换指向，外面的 score 不动。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
    int *score;
};

static void change(struct Student s)
{
    s.id = 9;
    s.name[0] = 'Z';
    *s.score = 100;
    s.score = NULL;
}

static struct Student renamed(struct Student s)
{
    s.id = 7;
    s.name[0] = 'Q';
    return s;
}

int main(void)
{
    int mark = 60;
    struct Student stu = {1, "ann", &mark};
    struct Student copy;

    printf("1. change(stu) 之后 id、name、mark\n");
    change(stu);
    printf("  %d %s %d\n", stu.id, stu.name, mark);
    printf("2. stu.score 还指着 mark ?\n");
    printf("  %s\n", stu.score == &mark ? "是" : "否");

    copy = renamed(stu);
    printf("3. renamed 返回的副本 id、name\n");
    printf("  %d %s\n", copy.id, copy.name);
    printf("4. 原来的 stu.id、stu.name、mark\n");
    printf("  %d %s %d\n", stu.id, stu.name, mark);
    printf("5. 副本的 score 和原来的 score\n");
    printf("  %s\n", copy.score == stu.score ? "相同" : "不同");
    return 0;
}
