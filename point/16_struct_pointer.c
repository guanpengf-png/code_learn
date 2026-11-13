/* 案例：结构体指针。sp 里放着 stu 的地址。
   sp->id 就是 (*sp).id。-> 先顺着指针走到结构体，再取成员。
   sizeof sp 是指针，这里是 8。sizeof *sp 是这个学生，int 加 char[8]，这里是 12。 */
#include <stdio.h>

struct Student {
    int id;
    char name[8];
};

int main(void)
{
    struct Student stu = {1, "ann"};
    struct Student *sp = &stu; /* 指向这一个学生 */
    struct Student *q;
    int *idp;
    char *np;

    /* 指针 8 字节，学生本身 12 字节。 */
    printf("sizeof sp = %zu，sizeof *sp = %zu\n", sizeof sp, sizeof *sp);

    /* -> 和 (*sp). 走到同一组 id、name。 */
    printf("1. sp->id，sp->name\n");
    printf("  %d %s\n", sp->id, sp->name);
    printf("2. (*sp).id，(*sp).name\n");
    printf("  %d %s\n", (*sp).id, (*sp).name);
    /* &stu 就是 sp 里那个地址，再 -> 仍是 id 1。 */
    printf("3. (&stu)->id\n");
    printf("  %d\n", (&stu)->id);
    /* 一个结构体指针也能写成下标 0，sp[0] 就是 *sp。 */
    printf("4. sp[0].id\n");
    printf("  %d\n", sp[0].id);

    /* 写的是 stu.id。sp 里的地址没变。 */
    sp->id = 9;
    printf("5. sp->id = 9 之后 stu.id\n");
    printf("  %d\n", stu.id);

    /* name 是结构体里面的字符数组。改 [0]，"ann" 变成 "Ann"。 */
    (*sp).name[0] = 'A';
    printf("6. (*sp).name[0] = 'A' 之后 stu.name\n");
    printf("  %s\n", stu.name);

    /* &sp->id 是成员 id 的地址，类型是 int *。*idp = 4 写进 stu.id。 */
    idp = &sp->id;
    *idp = 4;
    printf("7. *(&sp->id) = 4 之后 stu.id\n");
    printf("  %d\n", stu.id);

    /* sp->name 退化成 char *，指向 'A'。np[1] 把第二个字符改成 'N'，名字变成 "ANn"。 */
    np = sp->name;
    np[1] = 'N';
    printf("8. char *np = sp->name，np[1] = 'N' 之后\n");
    printf("  %s\n", stu.name);

    /* q 复制了 sp 里的地址，两个指针指着同一个 stu。q->id = 6 之后 sp->id 也是 6。 */
    q = sp;
    q->id = 6;
    printf("9. q = sp 之后，q->id 和 sp->id\n");
    printf("  %d %d\n", q->id, sp->id);
    return 0;
}
