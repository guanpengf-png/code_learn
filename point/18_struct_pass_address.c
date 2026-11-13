/* 案例：结构体传地址。形参 s 拿到 &stu 的副本，s-> 写的是原来那个学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

/* -> 改 id，(*s). 改 name[0]。两种写法都进到调用者那一个学生。 */
static void change(struct Student *s)
{
    s->id = 9;
    (*s).name[0] = 'Z';
}

/* 传入的可以是已经指向学生的指针，不必在调用处才写 &。 */
static void set_id(struct Student *s, int id)
{
    s->id = id;
}

/* *x、*y 是两个学生本身。t 先整份拷走，再整份对调。对调的是结构体里的内容。 */
static void swap_stu(struct Student *x, struct Student *y)
{
    struct Student t;

    t = *x;
    *x = *y;
    *y = t;
}

/* s 指向数组第 0 个学生。s[i] 跨过 i 个学生，改那一个的 id 和名字首字母。 */
static void rewrite(struct Student *s, int i, int id, char ch)
{
    s[i].id = id;
    s[i].name[0] = ch;
}

int main(void)
{
    struct Student stu = {1, "ann"};
    struct Student mate = {2, "bob"};
    struct Student cls[2] = {
        {1, "ann"},
        {2, "bob"}
    };
    struct Student *sp;

    /* &stu 传进去。id 变成 9，"ann" 变成 "Znn"。 */
    printf("1. change(&stu)\n");
    change(&stu);
    printf("  %d %s\n", stu.id, stu.name);

    sp = &stu;
    /* sp 里已经是 &stu。再传 sp，id 改成 4，名字仍是 Znn。 */
    printf("2. set_id(sp, 4)\n");
    set_id(sp, 4);
    printf("  %d %s\n", stu.id, stu.name);

    /* 交换前是 4 Znn 和 2 bob。交换后两格内容对调。 */
    printf("3. swap_stu 之前\n");
    printf("  %d %s | %d %s\n", stu.id, stu.name, mate.id, mate.name);
    swap_stu(&stu, &mate);
    printf("4. swap_stu 之后\n");
    printf("  %d %s | %d %s\n", stu.id, stu.name, mate.id, mate.name);

    /* cls 退化成 struct Student *。只改下标 1：id 6，"bob" 变成 "Qob"。下标 0 仍是 1 ann。 */
    printf("5. rewrite(cls, 1, 6, 'Q')\n");
    rewrite(cls, 1, 6, 'Q');
    printf("  %d %s | %d %s\n", cls[0].id, cls[0].name, cls[1].id, cls[1].name);
    return 0;
}
