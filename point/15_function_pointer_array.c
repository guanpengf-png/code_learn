/* 案例：函数指针数组。ops 有两个元素，每个元素都指向一个函数。 */
#include <stdio.h>

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

    printf("ops[0](8, 2) = %d\n", ops[0](8, 2));
    printf("ops[1](8, 2) = %d\n", ops[1](8, 2));
    return 0;
}
