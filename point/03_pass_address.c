/* 案例：传地址。*p 改的是原来那个变量。 */
#include <stdio.h>

static void set_target(int *p)
{
    *p = 100;
}

int main(void)
{
    int a = 10;

    set_target(&a);
    printf("a = %d\n", a);
    return 0;
}
