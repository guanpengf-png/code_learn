/* 案例：传值。函数里改的是形参副本，main 里的 a 不变。 */
#include <stdio.h>

static void set_copy(int x)
{
    x = 100;
    printf("函数里的 x = %d\n", x);
}

int main(void)
{
    int a = 10;

    set_copy(a);
    printf("main 里的 a = %d\n", a);
    return 0;
}
