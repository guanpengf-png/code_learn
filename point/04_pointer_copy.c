/* 案例：指针参数也是副本。函数里 p = NULL，外面的指针不动。 */
#include <stdio.h>

static void drop(int *p)
{
    p = NULL;
    printf("函数里 p == NULL ? %s\n", p == NULL ? "是" : "否");
}

int main(void)
{
    int a = 10;
    int *cursor = &a;

    drop(cursor);
    printf("main 里 *cursor = %d\n", *cursor);
    return 0;
}
