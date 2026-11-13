/* 案例：函数指针当参数。apply 在自己内部调用传进来的函数。 */
#include <stdio.h>

static int inc(int x)
{
    return x + 1;
}

static void apply(int *p, int (*fn)(int))
{
    *p = fn(*p);
}

int main(void)
{
    int n = 10;

    apply(&n, inc);
    printf("n = %d\n", n);
    return 0;
}
