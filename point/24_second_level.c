/* 案例：二级指针。实参是 &cursor，函数里的 *pp 就是 cursor 自己。
   pp = pp + 1 只改形参。*pp 才换掉 main 里的指针，**pp 才改到那个 int。 */
#include <stdio.h>

/* *pp 就是 cursor。*pp + 1 从当前元素跨到下一个，再写回 cursor。 */
static void hop(int **pp)
{
    *pp = *pp + 1;
}

/* *pp 是 cursor，再 * 读它指着的 int。 */
static int read_two(int **pp)
{
    return **pp;
}

/* 把 cursor 这格改成 target。 */
static void aim(int **pp, int *target)
{
    *pp = target;
}

/* pp + 1 只让形参自己挪一格。main 里的 cursor 不动。 */
static void local_step(int **pp)
{
    int **income = pp;

    pp = pp + 1;
    printf("  函数里的二级指针%s\n", pp == income ? "没动" : "动了");
}

/* **pp 写进 cursor 当前指着的那个 int。cursor 的指向不变。 */
static void write_int(int **pp, int value)
{
    **pp = value;
}

/* *pp = NULL 清的是 cursor 这格。清完不要再 *cursor。 */
static void clear(int **pp)
{
    *pp = NULL;
}

/* *x、*y 是两个 int *。这里对调的是指针格子里的地址，不是那两个 int 的值。 */
static void swap(int **x, int **y)
{
    int *t;

    t = *x;
    *x = *y;
    *y = t;
}

int main(void)
{
    int nums[3] = {10, 20, 30};
    int *cursor = nums;   /* 指向 10 */
    int **pp = &cursor;   /* pp 指向 cursor 这格，不是指向 nums */
    int a = 1;
    int b = 2;
    int *pa = &a;
    int *pb = &b;

    /* **pp：先到 cursor，再到它指着的 10。*pp 和 cursor 是同一个指针。 */
    printf("1. **pp\n");
    printf("  %d\n", **pp);
    printf("2. *pp 和 cursor\n");
    printf("  %s\n", (*pp == cursor) ? "相同" : "不同");

    /* cursor 从 nums[0] 挪到 nums[1]，*cursor 变成 20。 */
    printf("3. hop(&cursor)\n");
    hop(&cursor);
    printf("  %d\n", *cursor);

    /* 再 * 一次，仍读到 20。 */
    printf("4. read_two(&cursor)\n");
    printf("  %d\n", read_two(&cursor));

    /* cursor 改去指 nums[2]，读到 30。 */
    printf("5. aim(&cursor, &nums[2])\n");
    aim(&cursor, &nums[2]);
    printf("  %d\n", *cursor);

    /* 函数里打印“动了”。main 里 cursor 仍指着 30。 */
    printf("6. local_step(&cursor)\n");
    local_step(&cursor);
    printf("  main 里 *cursor = %d\n", *cursor);

    /* nums[2] 写成 7。cursor 还指着这一格。 */
    printf("7. write_int(&cursor, 7)\n");
    write_int(&cursor, 7);
    printf("  %d\n", *cursor);
    printf("  nums[2] = %d\n", nums[2]);

    /* pa、pb 交换的是地址。*pa 变成 2，*pb 变成 1。a、b 两格本身还在原处。 */
    printf("8. swap(&pa, &pb) 之后 *pa、*pb\n");
    swap(&pa, &pb);
    printf("  %d %d\n", *pa, *pb);

    /* cursor 变成空。这里只比较，不再 *cursor。下一条再把它指回 nums[0]，读到 10。 */
    printf("9. clear(&cursor)\n");
    clear(&cursor);
    printf("  cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");

    printf("10. aim(&cursor, &nums[0])\n");
    aim(&cursor, &nums[0]);
    printf("  %d\n", *cursor);
    return 0;
}
