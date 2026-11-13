/* 案例：传值。函数里改的是形参副本，main 里的原变量还是原来的数。 */
#include <stdio.h>

static void set_copy(int x)
{
    x = 100;
    printf("  函数里的 x = %d\n", x);
}

static void drop(int *p)
{
    p = NULL;
    printf("  函数里 p == NULL ? %s\n", p == NULL ? "是" : "否");
}

static void step(int *p)
{
    int *income = p;

    p = p + 1;
    printf("  函数里的指针%s\n", p == income ? "没动" : "动了");
}

int main(void)
{
    int a = 10;
    int nums[3] = {10, 20, 30};
    int *cursor = &a;

    printf("1. set_copy(a)\n");
    set_copy(a);
    printf("  main 里的 a = %d\n", a);

    printf("2. set_copy(*cursor)\n");
    set_copy(*cursor);
    printf("  main 里的 *cursor = %d\n", *cursor);

    printf("3. set_copy(nums[2])\n");
    set_copy(nums[2]);
    printf("  main 里的 nums[2] = %d\n", nums[2]);

    printf("4. drop(cursor)，形参被赋成 NULL\n");
    drop(cursor);
    printf("  main 里 cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");
    printf("  main 里的 *cursor = %d\n", *cursor);

    printf("5. step(cursor)，形参自己 +1\n");
    step(cursor);
    printf("  main 里的 *cursor = %d\n", *cursor);
    return 0;
}
