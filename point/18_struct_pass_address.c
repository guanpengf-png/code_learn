/* 案例：结构体传地址。s->id 改的是原来的学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

static void change(struct Student *s)
{
    s->id = 9;
    (*s).name[0] = 'Z';
}

static void set_id(struct Student *s, int id)
{
    s->id = id;
}

static void swap_stu(struct Student *x, struct Student *y)
{
    struct Student t;

    t = *x;
    *x = *y;
    *y = t;
}

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

    printf("1. change(&stu)\n");
    change(&stu);
    printf("  %d %s\n", stu.id, stu.name);

    sp = &stu;
    printf("2. set_id(sp, 4)\n");
    set_id(sp, 4);
    printf("  %d %s\n", stu.id, stu.name);

    printf("3. swap_stu 之前\n");
    printf("  %d %s | %d %s\n", stu.id, stu.name, mate.id, mate.name);
    swap_stu(&stu, &mate);
    printf("4. swap_stu 之后\n");
    printf("  %d %s | %d %s\n", stu.id, stu.name, mate.id, mate.name);

    printf("5. rewrite(cls, 1, 6, 'Q')\n");
    rewrite(cls, 1, 6, 'Q');
    printf("  %d %s | %d %s\n", cls[0].id, cls[0].name, cls[1].id, cls[1].name);
    return 0;
}
