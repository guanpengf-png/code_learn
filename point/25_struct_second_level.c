/* 案例：结构体的二级指针。函数通过 *seat 改掉调用者的那个结构体指针。
   seat = seat + 1 只改形参。(*seat)->id 改的是那个学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
    struct Student *next; /* 指向下一个学生。NULL 表示后面没有了 */
};

/* *seat = who 把调用者的结构体指针改去指 who。 */
static void appoint(struct Student **seat, struct Student *who)
{
    *seat = who;
}

/* (*seat) 是那个学生，->id 写进他的 id。指针格子本身不变。 */
static void set_id(struct Student **seat, int id)
{
    (*seat)->id = id;
}

/* seat + 1 只挪形参。调用者的 monitor 仍指着原来的学生。 */
static void local_step(struct Student **seat)
{
    struct Student **income = seat;

    seat = seat + 1;
    printf("  函数里的二级指针%s\n", seat == income ? "没动" : "动了");
}

/* *seat = NULL 清的是调用者那个结构体指针。 */
static void clear(struct Student **seat)
{
    *seat = NULL;
}

/* node 插到链表头。先让 node->next 接住原来的头，再让头改指 node。 */
static void push(struct Student **head, struct Student *node)
{
    node->next = *head;
    *head = node;
}

int main(void)
{
    struct Student cls[2] = {
        {1, "ann", NULL},
        {2, "bob", NULL}
    };
    struct Student *monitor = NULL; /* 还没有指着任何学生 */
    struct Student **seat;
    struct Student *it;

    /* monitor 改去指 bob，id 是 2。 */
    printf("1. appoint(&monitor, &cls[1])\n");
    appoint(&monitor, &cls[1]);
    printf("  %s %d\n", monitor->name, monitor->id);

    seat = &monitor;
    /* (*seat)->name 先到 monitor，再取 name。
       (**seat).name 是同一条路：两层 * 得到学生，再用 . 取 name。都是 bob。 */
    printf("2. (*seat)->name\n");
    printf("  %s\n", (*seat)->name);
    printf("3. (**seat).name\n");
    printf("  %s\n", (**seat).name);

    /* 写的是 bob 的 id。monitor 和 cls[1] 是同一个学生，两处都变成 8。 */
    printf("4. set_id(&monitor, 8) 之后 monitor->id 和 cls[1].id\n");
    set_id(&monitor, 8);
    printf("  %d %d\n", monitor->id, cls[1].id);

    /* monitor 改去指 ann。 */
    printf("5. appoint(&monitor, &cls[0])\n");
    appoint(&monitor, &cls[0]);
    printf("  %s\n", monitor->name);

    /* 函数里打印“动了”。main 里仍是 ann。 */
    printf("6. local_step(&monitor)\n");
    local_step(&monitor);
    printf("  main 里仍是 %s\n", monitor->name);

    /* monitor 变成空。这里只比较，不再 ->name。 */
    printf("7. clear(&monitor)\n");
    clear(&monitor);
    printf("  monitor == NULL ? %s\n", monitor == NULL ? "是" : "否");

    /* 先把头设成 ann，再把 bob 插到 ann 前面。沿 next 走出来是 bob、ann。 */
    push(&monitor, &cls[0]);
    push(&monitor, &cls[1]);
    printf("8. push 两次之后沿 next 走\n");
    it = monitor;
    while (it != NULL) {
        printf("  %s\n", it->name);
        it = it->next;
    }
    return 0;
}
