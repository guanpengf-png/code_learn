/* 案例：传值。函数里改的是形参那一格，main 里的原件不动。
   传进去的是数的副本，或者指针格子里那个地址的副本。 */
#include <stdio.h>

/* x 是 a 的副本。x = 100 只改这一份，函数结束 x 就没了。 */
static void set_copy(int x)
{
    x = 100;
    printf("  函数里的 x = %d\n", x);
}

/* p 复制了调用者指针里的地址。p = NULL 只清这一份副本。 */
static void drop(int *p)
{
    p = NULL;
    printf("  函数里 p == NULL ? %s\n", p == NULL ? "是" : "否");
}

/* income 记下进来时的地址。p = p + 1 只让形参自己挪一格。 */
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
    int *cursor = &a; /* cursor 指向 a，*cursor 是 10 */

    /* 传的是 10 这个数。函数里 x 变成 100，main 里 a 仍是 10。 */
    printf("1. set_copy(a)\n");
    set_copy(a);
    printf("  main 里的 a = %d\n", a);

    /* *cursor 先读出 10，传进去的仍是数的副本，不是 cursor 这个指针。a 还是 10。 */
    printf("2. set_copy(*cursor)\n");
    set_copy(*cursor);
    printf("  main 里的 *cursor = %d\n", *cursor);

    /* 传进去的是 30 的副本。nums[2] 还是 30。 */
    printf("3. set_copy(nums[2])\n");
    set_copy(nums[2]);
    printf("  main 里的 nums[2] = %d\n", nums[2]);

    /* cursor 里的地址被复制进形参 p。函数里 p == NULL 打印“是”。
       main 里 cursor 仍是 &a，所以这里打印“否”，*cursor 仍是 10。 */
    printf("4. drop(cursor)，形参被赋成 NULL\n");
    drop(cursor);
    printf("  main 里 cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");
    printf("  main 里的 *cursor = %d\n", *cursor);

    /* 函数里形参和进来时的地址不同，打印“动了”。cursor 自己没有 +1，*cursor 仍是 10。 */
    printf("5. step(cursor)，形参自己 +1\n");
    step(cursor);
    printf("  main 里的 *cursor = %d\n", *cursor);
    return 0;
}
