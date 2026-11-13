/* 案例：结构体的二级指针。函数通过 *seat 改掉调用者的那个结构体指针。
   seat = seat + 1 只改形参。(*seat)->id 改的是那个学生。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
    struct Student *next;
};

static void appoint(struct Student **seat, struct Student *who)
{
    *seat = who;
}

static void set_id(struct Student **seat, int id)
{
    (*seat)->id = id;
}

static void local_step(struct Student **seat)
{
    struct Student **income = seat;

    seat = seat + 1;
    printf("  函数里的二级指针%s\n", seat == income ? "没动" : "动了");
}

static void clear(struct Student **seat)
{
    *seat = NULL;
}

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
    struct Student *monitor = NULL;
    struct Student **seat;
    struct Student *it;

    printf("1. appoint(&monitor, &cls[1])\n");
    appoint(&monitor, &cls[1]);
    printf("  %s %d\n", monitor->name, monitor->id);

    seat = &monitor;
    printf("2. (*seat)->name\n");
    printf("  %s\n", (*seat)->name);
    printf("3. (**seat).name\n");
    printf("  %s\n", (**seat).name);

    printf("4. set_id(&monitor, 8) 之后 monitor->id 和 cls[1].id\n");
    set_id(&monitor, 8);
    printf("  %d %d\n", monitor->id, cls[1].id);

    printf("5. appoint(&monitor, &cls[0])\n");
    appoint(&monitor, &cls[0]);
    printf("  %s\n", monitor->name);

    printf("6. local_step(&monitor)\n");
    local_step(&monitor);
    printf("  main 里仍是 %s\n", monitor->name);

    printf("7. clear(&monitor)\n");
    clear(&monitor);
    printf("  monitor == NULL ? %s\n", monitor == NULL ? "是" : "否");

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
