/* 案例：结构体的二级指针。函数通过 *seat 改掉调用者的那个结构体指针。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

static void appoint(struct Student **seat, struct Student *who)
{
    *seat = who;
}

int main(void)
{
    struct Student cls[2] = {
        {1, "ann"},
        {2, "bob"}
    };
    struct Student *monitor = NULL;

    appoint(&monitor, &cls[1]);
    printf("班长是 %s\n", monitor->name);
    return 0;
}
