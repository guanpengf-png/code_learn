/* 案例：结构体传值。函数拿到的是整个学生的副本。
   改副本的 id、name，原来的学生不动。
   score 是指针成员：副本里复制的是地址，*s.score 会写到外面那个 int。
   给副本的 score 换指向，外面的 score 格子不动。
   这一章的结构体多了一个 int *，对齐之后是 24 字节。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
    int *score;
};

/* s 是 stu 的副本。id、name 的修改留在副本里。
   *s.score 顺着复制来的地址写进 mark。s.score = NULL 只清副本里的指针。 */
static void change(struct Student s)
{
    s.id = 9;
    s.name[0] = 'Z';
    *s.score = 100;
    s.score = NULL;
}

/* 改的是副本，再把整份副本交回来。调用者要用返回值接住，原来的 stu 不变。 */
static struct Student renamed(struct Student s)
{
    s.id = 7;
    s.name[0] = 'Q';
    return s;
}

int main(void)
{
    int mark = 60;
    struct Student stu = {1, "ann", &mark}; /* score 指向 mark */
    struct Student copy;

    /* 外面仍是 id 1、name ann。mark 被 *s.score 写成 100。 */
    printf("1. change(stu) 之后 id、name、mark\n");
    change(stu);
    printf("  %d %s %d\n", stu.id, stu.name, mark);
    /* 副本里的 score = NULL 没有写回 stu，所以 stu.score 仍是 &mark。 */
    printf("2. stu.score 还指着 mark ?\n");
    printf("  %s\n", stu.score == &mark ? "是" : "否");

    /* 返回值是另一份学生：id 7，名字从 ann 改成 Qnn。score 指针也被复制过来。 */
    copy = renamed(stu);
    printf("3. renamed 返回的副本 id、name\n");
    printf("  %d %s\n", copy.id, copy.name);
    /* 原来的 stu 仍是 1 ann，mark 仍是 100。两份 score 都指着 mark。 */
    printf("4. 原来的 stu.id、stu.name、mark\n");
    printf("  %d %s %d\n", stu.id, stu.name, mark);
    printf("5. 副本的 score 和原来的 score\n");
    printf("  %s\n", copy.score == stu.score ? "相同" : "不同");
    return 0;
}
