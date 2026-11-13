/* 案例：函数指针数组。ops 的每个元素都指向一个函数。
   add(8, 2) 是 10，sub(8, 2) 是 6。 */
#include <stdio.h>

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
    int (*ops[2])(int, int) = {add, sub};
    int (*row[3])(int, int) = {add, NULL, sub};
    int (*(*bundle)[2])(int, int) = &ops;
    int (**cursor)(int, int);
    Binary named[2] = {add, sub};
    int i;

    printf("1. ops[0](8, 2)\n");
    printf("  %d\n", ops[0](8, 2));
    printf("2. ops[1](8, 2)\n");
    printf("  %d\n", ops[1](8, 2));
    printf("3. (*ops[0])(8, 2)\n");
    printf("  %d\n", (*ops[0])(8, 2));
    printf("4. (*ops[1])(8, 2)\n");
    printf("  %d\n", (*ops[1])(8, 2));
    printf("5. 0[ops](8, 2)\n");
    printf("  %d\n", 0[ops](8, 2));
    printf("6. 1[ops](8, 2)\n");
    printf("  %d\n", 1[ops](8, 2));
    printf("7. (*(ops + 0))(8, 2)\n");
    printf("  %d\n", (*(ops + 0))(8, 2));
    printf("8. (*(ops + 1))(8, 2)\n");
    printf("  %d\n", (*(ops + 1))(8, 2));

    printf("9. (*cursor++)(8, 2) 走两个元素\n");
    cursor = ops;
    printf("  ");
    for (i = 0; i < 2; i++)
        printf("%d ", (*cursor++)(8, 2));
    printf("\n");

    printf("10. (*bundle)[0](8, 2)\n");
    printf("  %d\n", (*bundle)[0](8, 2));
    printf("11. (*bundle)[1](8, 2)\n");
    printf("  %d\n", (*bundle)[1](8, 2));

    printf("12. 数组里可以有空位\n");
    for (i = 0; i < 3; i++) {
        if (row[i] == NULL)
            printf("  空\n");
        else
            printf("  %d\n", row[i](8, 2));
    }

    ops[0] = sub;
    printf("13. ops[0] = sub 之后 ops[0](8, 2)\n");
    printf("  %d\n", ops[0](8, 2));

    printf("14. typedef Binary named[0](8, 2)\n");
    printf("  %d\n", named[0](8, 2));
    printf("15. named[1](8, 2)\n");
    printf("  %d\n", named[1](8, 2));
    return 0;
}
