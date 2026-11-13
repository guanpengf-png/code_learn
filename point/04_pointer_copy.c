/* 案例：指针参数也是副本。
   给形参 p 换指向，main 里的指针不动。*p 写的是原来那个 int。
   要换掉 main 里的指针，参数得是 int **，实参传 &cursor。 */
#include <stdio.h>

/* 形参变成 NULL。调用者的 cursor 还指着原来的数。 */
static void drop(int *p)
{
    p = NULL;
    printf("  函数里 p == NULL ? %s\n", p == NULL ? "是" : "否");
}

/* 形参自己 +1，和进来时的地址不同。调用者的 cursor 不动。 */
static void step(int *p)
{
    int *income = p;

    p = p + 1;
    printf("  函数里的指针%s\n", p == income ? "没动" : "动了");
}

/* *p = 100 写进 cursor 当前指着的那一格，指向本身不变。 */
static void write_star(int *p)
{
    *p = 100;
}

/* pp 的类型是 int **，指向 cursor 这格。
   *pp 就是 cursor。*pp + 1 从当前元素跨到下一个，再写回 cursor。 */
static void move_caller(int **pp)
{
    *pp = *pp + 1;
}

/* *pp 是 cursor，再 * 进到那个 int，写成 7。cursor 仍指向这一格。 */
static void write_through(int **pp)
{
    **pp = 7;
}

int main(void)
{
    int nums[3] = {10, 20, 30};
    int *cursor = nums; /* 指向 nums[0]，里面是 10 */

    /* 函数里打印“是”。main 里 cursor 仍指向 10，打印“否”。 */
    printf("1. drop(cursor)\n");
    drop(cursor);
    printf("  main 里 cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");
    printf("  *cursor = %d\n", *cursor);

    /* 函数里打印“动了”。cursor 仍指向 10。 */
    printf("2. step(cursor)\n");
    step(cursor);
    printf("  *cursor = %d\n", *cursor);

    /* nums[0] 变成 100。cursor 还指着这一格，所以 *cursor 也是 100。 */
    printf("3. write_star(cursor)，*p = 100\n");
    write_star(cursor);
    printf("  *cursor = %d\n", *cursor);
    printf("  nums[0] = %d\n", nums[0]);

    /* 传入 &cursor。cursor 从 nums[0] 挪到 nums[1]，*cursor 变成 20。 */
    printf("4. move_caller(&cursor)，*pp = *pp + 1\n");
    move_caller(&cursor);
    printf("  *cursor = %d\n", *cursor);

    /* **pp 写的是 nums[1]。cursor 仍指向它，所以两处都是 7。 */
    printf("5. write_through(&cursor)，**pp = 7\n");
    write_through(&cursor);
    printf("  *cursor = %d\n", *cursor);
    printf("  nums[1] = %d\n", nums[1]);
    return 0;
}
