/* 案例：指针参数也是副本。
   函数里给 p 换指向，main 里的指针不动。
   *p 写的是原来那个变量。
   要换掉 main 里的指针，参数得是 int **。 */
#include <stdio.h>

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

static void write_star(int *p)
{
    *p = 100;
}

static void move_caller(int **pp)
{
    *pp = *pp + 1;
}

static void write_through(int **pp)
{
    **pp = 7;
}

int main(void)
{
    int nums[3] = {10, 20, 30};
    int *cursor = nums;

    printf("1. drop(cursor)\n");
    drop(cursor);
    printf("  main 里 cursor == NULL ? %s\n", cursor == NULL ? "是" : "否");
    printf("  *cursor = %d\n", *cursor);

    printf("2. step(cursor)\n");
    step(cursor);
    printf("  *cursor = %d\n", *cursor);

    printf("3. write_star(cursor)，*p = 100\n");
    write_star(cursor);
    printf("  *cursor = %d\n", *cursor);
    printf("  nums[0] = %d\n", nums[0]);

    printf("4. move_caller(&cursor)，*pp = *pp + 1\n");
    move_caller(&cursor);
    printf("  *cursor = %d\n", *cursor);

    printf("5. write_through(&cursor)，**pp = 7\n");
    write_through(&cursor);
    printf("  *cursor = %d\n", *cursor);
    printf("  nums[1] = %d\n", nums[1]);
    return 0;
}
