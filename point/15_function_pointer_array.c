/* 案例：函数指针数组。ops 的每个元素都是一个函数指针。
   add(8, 2) 是 10，sub(8, 2) 是 6。
   数组名退化成 int (**)，一步跨过一个函数指针。
   bundle 指向整段数组，一步跨过两个函数指针。 */
#include <stdio.h>

/* Binary 就是 int (*)(int, int)。 */
typedef int (*Binary)(int, int);

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

int main(void)
{
    int (*ops[2])(int, int) = {add, sub};       /* [0] 是 add，[1] 是 sub */
    int (*row[3])(int, int) = {add, NULL, sub}; /* 中间这一格没有函数 */
    int (*(*bundle)[2])(int, int) = &ops;       /* 指向整段 ops */
    int (**cursor)(int, int);                   /* 用来沿 ops 往前走 */
    Binary named[2] = {add, sub};               /* 和 ops 同一种数组 */
    int i;

    /* ops[0] 取出 add 再调用。(*ops[0]) 先 * 再调用，还是 10。 */
    printf("1. ops[0](8, 2)\n");
    printf("  %d\n", ops[0](8, 2));
    /* ops[1] 是 sub，8 - 2 = 6。 */
    printf("2. ops[1](8, 2)\n");
    printf("  %d\n", ops[1](8, 2));
    printf("3. (*ops[0])(8, 2)\n");
    printf("  %d\n", (*ops[0])(8, 2));
    printf("4. (*ops[1])(8, 2)\n");
    printf("  %d\n", (*ops[1])(8, 2));
    /* 0[ops] 就是 ops[0]。*(ops + 1) 就是 ops[1]。 */
    printf("5. 0[ops](8, 2)\n");
    printf("  %d\n", 0[ops](8, 2));
    printf("6. 1[ops](8, 2)\n");
    printf("  %d\n", 1[ops](8, 2));
    printf("7. (*(ops + 0))(8, 2)\n");
    printf("  %d\n", (*(ops + 0))(8, 2));
    printf("8. (*(ops + 1))(8, 2)\n");
    printf("  %d\n", (*(ops + 1))(8, 2));

    /* cursor 从 ops[0] 出发。(*cursor++) 先用当前函数，再移到下一格。
       两次打出 10 和 6。走完 cursor 停在数组后面，下面改用 bundle。 */
    printf("9. (*cursor++)(8, 2) 走两个元素\n");
    cursor = ops;
    printf("  ");
    for (i = 0; i < 2; i++)
        printf("%d ", (*cursor++)(8, 2));
    printf("\n");

    /* *bundle 取出整段 ops。(*bundle)[1] 是 sub。 */
    printf("10. (*bundle)[0](8, 2)\n");
    printf("  %d\n", (*bundle)[0](8, 2));
    printf("11. (*bundle)[1](8, 2)\n");
    printf("  %d\n", (*bundle)[1](8, 2));

    /* 空格子不要调用。先看是不是 NULL，再 row[i](8, 2)。打出 10、空、6。 */
    printf("12. 数组里可以有空位\n");
    for (i = 0; i < 3; i++) {
        if (row[i] == NULL)
            printf("  空\n");
        else
            printf("  %d\n", row[i](8, 2));
    }

    /* 函数指针格子可以换人。ops[0] 改成 sub 之后，8 - 2 = 6。named 那份没被改。 */
    ops[0] = sub;
    printf("13. ops[0] = sub 之后 ops[0](8, 2)\n");
    printf("  %d\n", ops[0](8, 2));

    printf("14. typedef Binary named[0](8, 2)\n");
    printf("  %d\n", named[0](8, 2));
    printf("15. named[1](8, 2)\n");
    printf("  %d\n", named[1](8, 2));
    return 0;
}
