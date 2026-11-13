/* 案例：二级指针。实参是 &cursor，函数里的 *pp 就是 cursor 自己。
   pp = pp + 1 只改形参。*pp 才换掉 main 里的指针，**pp 才改到那个 int。 */
#include <stdio.h>

static void hop(int **pp)
{
    *pp = *pp + 1;
}

static int read_two(int **pp)
{
    return **pp;
}

static void aim(int **pp, int *target)
{
    *pp = target;
}

static void local_step(int **pp)
{
    int **income = pp;

    pp = pp + 1;
    printf("  函数里的二级指针%s\n", pp == income ? "没动" : "动了");
}

static void write_int(int **pp, int value)
{
    **pp = value;
}

static void clear(int **pp)
{
    *pp = NULL;
}

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
    int *cursor = nums;
    int **pp = &cursor;
    int a = 1;
    int b = 2;
    int *pa = &a;
    int *pb = &b;

    printf("1. **pp\n");
    printf("  %d\n", **pp);
    printf("2. *pp 和 cursor\n");
    printf("  %s\n", (*pp == cursor) ? "相同" : "不同");

    printf("3. hop(&cursor)\n");
    hop(&cursor);
    printf("  %d\n", *cursor);

    printf("4. read_two(&cursor)\n");
    printf("  %d\n", read_two(&cursor));

    printf("5. aim(&cursor, &nums[2])\n");
    aim(&cursor, &nums[2]);
    printf("  %d\n", *cursor);

    printf("6. local_step(&cursor)\n");
    local_step(&cursor);
    printf("  main 里 *cursor = %d\n", *cursor);

    printf("7. write_int(&cursor, 7)\n");
    write_int(&cursor, 7);
    printf("  %d\n", *cursor);
    printf("  nums[2] = %d\n", nums[2]);

    printf("8. swap(&pa, &pb) 之后 *pa、*pb\n");
    swap(&pa, &pb);
    printf("  %d %d\n", *pa, *pb);

    printf("9. clear(&cursor)\n");
    clear(&cursor);
    printf("  cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");

    printf("10. aim(&cursor, &nums[0])\n");
    aim(&cursor, &nums[0]);
    printf("  %d\n", *cursor);
    return 0;
}
