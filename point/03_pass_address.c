/* 案例：传地址。形参 p 拿到的是地址的副本，*p 写的是调用者那一格。 */
#include <stdio.h>

/* p 指向调用者的那一格，*p = 100 写进原件。 */
static void set_target(int *p)
{
    *p = 100;
}

/* 再沿着同一个地址把那一格加 1。 */
static void add_one(int *p)
{
    *p = *p + 1;
}

/* x、y 分别指向调用者的两个 int。t 先存 *x，再把两格的内容对调。
   对调的是格子里的数，main 里的变量还是原来那两个。 */
static void swap(int *x, int *y)
{
    int t;

    t = *x;
    *x = *y;
    *y = t;
}

/* p 指向一段连续的 int。p[i] 就是 *(p + i)，从起点连着写 n 个。 */
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
    int *p = &a; /* main 里的 p 已经指向 a */
    int i;

    /* 传入 &a。a 从 10 变成 100。 */
    printf("1. set_target(&a)\n");
    set_target(&a);
    printf("  %d\n", a);

    /* 传入的是已经指向 a 的指针。函数再复制这个地址，a 变成 101。 */
    printf("2. add_one(p)，p 已经指向 a\n");
    add_one(p);
    printf("  %d\n", a);

    /* 只把第 2 格写成 100。nums[0] 仍是 10。 */
    printf("3. set_target(&nums[2])\n");
    set_target(&nums[2]);
    printf("  %d\n", nums[2]);
    printf("  nums[0] 仍是 %d\n", nums[0]);

    /* 这时 a 是 101，b 是 20。交换后 a 是 20，b 是 101。 */
    printf("4. swap(&a, &b) 之后 a、b\n");
    swap(&a, &b);
    printf("  %d %d\n", a, b);

    /* nums 退化成 int *，指向第 0 格。写成 1 2 3 4 5。 */
    printf("5. fill(nums, 5, 1)\n");
    fill(nums, 5, 1);
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    printf("\n");

    /* 起点仍是第 0 格，这次只写 3 个：7 8 9。后面两格留着上一次的 4 5。 */
    printf("6. fill(&nums[0], 3, 7)，从第 0 个连续写 3 个\n");
    fill(&nums[0], 3, 7);
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}
