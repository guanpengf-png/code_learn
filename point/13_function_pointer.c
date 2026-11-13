/* 案例：函数指针。op 里放的是函数的地址，op(20, 3) 就是在调用那个函数。 */
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
    int (*op)(int, int) = add;

    printf("add: %d\n", op(20, 3));
    op = sub;
    printf("sub: %d\n", op(20, 3));
    return 0;
}
