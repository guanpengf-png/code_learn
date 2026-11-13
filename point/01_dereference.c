/* 案例：一级指针。p 里放着 a 的地址，*p 就是 a。 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int *p = &a;

    printf("a = %d\n", a);
    *p = 20;
    printf("通过 *p 改成 20 之后，a = %d\n", a);
    return 0;
}
