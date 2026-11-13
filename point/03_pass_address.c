/* 案例：传地址。函数里的 *p 改的是原来那个变量。 */
#include <stdio.h>

static void set_target(int *p)
{
    *p = 100;
}

static void add_one(int *p)
{
    *p = *p + 1;
}

static void swap(int *x, int *y)
{
    int t;

    t = *x;
    *x = *y;
    *y = t;
}

static void fill(int *p, int n, int value)
{
    int i;

    for (i = 0; i < n; i++)
        p[i] = value + i;
}

int main(void)
{
    int a = 10;
    int b = 20;
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = &a;
    int i;

    printf("1. set_target(&a)\n");
    set_target(&a);
    printf("  %d\n", a);

    printf("2. add_one(p)，p 已经指向 a\n");
    add_one(p);
    printf("  %d\n", a);

    printf("3. set_target(&nums[2])\n");
    set_target(&nums[2]);
    printf("  %d\n", nums[2]);
    printf("  nums[0] 仍是 %d\n", nums[0]);

    printf("4. swap(&a, &b) 之后 a、b\n");
    swap(&a, &b);
    printf("  %d %d\n", a, b);

    printf("5. fill(nums, 5, 1)\n");
    fill(nums, 5, 1);
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    printf("\n");

    printf("6. fill(&nums[0], 3, 7)，从第 0 个连续写 3 个\n");
    fill(&nums[0], 3, 7);
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}
