/* 案例：数组名传进函数后变成指针。
   形参写成 int a[5]、int a[]、int *a，函数里都是 int *。
   int (*block)[5] 指着整段数组，*block 仍是那 5 个 int。 */
#include <stdio.h>

static void as_array(int a[5])
{
    int *p = a;

    printf("  sizeof 形参指针 %zu，a[2] = %d\n", sizeof p, a[2]);
    a[0] = 99;
}

static void as_open(int a[])
{
    int *p = a;

    printf("  sizeof 形参指针 %zu，a[1] = %d\n", sizeof p, a[1]);
}

static void as_pointer(int *a)
{
    printf("  sizeof 形参指针 %zu，a[4] = %d\n", sizeof a, a[4]);
}

static void as_block(int (*block)[5])
{
    printf("  sizeof *block %zu，(*block)[2] = %d\n",
           sizeof *block, (*block)[2]);
}

static void as_rows(int g[][3])
{
    int (*p)[3] = g;

    printf("  sizeof 行指针 %zu，sizeof 一行 %zu，g[1][2] = %d\n",
           sizeof p, sizeof g[0], g[1][2]);
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("1. main 里 sizeof nums\n");
    printf("  %zu\n", sizeof nums);

    printf("2. 形参 int a[5]\n");
    as_array(nums);
    printf("  main 里 nums[0] = %d\n", nums[0]);

    printf("3. 形参 int a[]\n");
    as_open(nums);
    printf("4. 形参 int *a\n");
    as_pointer(nums);
    printf("5. 形参 int (*block)[5]，实参是 &nums\n");
    as_block(&nums);
    printf("6. 形参 int g[][3]\n");
    as_rows(grid);
    return 0;
}
