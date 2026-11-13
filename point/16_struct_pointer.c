/* 案例：结构体指针。sp->id 就是 (*sp).id。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

int main(void)
{
    struct Student stu = {1, "ann"};
    struct Student *sp = &stu;
    struct Student *q;
    int *idp;
    char *np;

    printf("sizeof sp = %zu，sizeof *sp = %zu\n", sizeof sp, sizeof *sp);

    printf("1. sp->id，sp->name\n");
    printf("  %d %s\n", sp->id, sp->name);
    printf("2. (*sp).id，(*sp).name\n");
    printf("  %d %s\n", (*sp).id, (*sp).name);
    printf("3. (&stu)->id\n");
    printf("  %d\n", (&stu)->id);
    printf("4. sp[0].id\n");
    printf("  %d\n", sp[0].id);

    sp->id = 9;
    printf("5. sp->id = 9 之后 stu.id\n");
    printf("  %d\n", stu.id);

    (*sp).name[0] = 'A';
    printf("6. (*sp).name[0] = 'A' 之后 stu.name\n");
    printf("  %s\n", stu.name);

    idp = &sp->id;
    *idp = 4;
    printf("7. *(&sp->id) = 4 之后 stu.id\n");
    printf("  %d\n", stu.id);

    np = sp->name;
    np[1] = 'N';
    printf("8. char *np = sp->name，np[1] = 'N' 之后\n");
    printf("  %s\n", stu.name);

    q = sp;
    q->id = 6;
    printf("9. q = sp 之后，q->id 和 sp->id\n");
    printf("  %d %d\n", q->id, sp->id);
    return 0;
}
