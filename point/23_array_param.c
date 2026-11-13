/* 案例：数组名传进函数后变成指针。
   形参写成 int a[5]、int a[]、int *a，函数里都是 int *。
   int (*block)[5] 指着整段数组，*block 仍是那 5 个 int。 */
#include <stdio.h>

/* 形参写成 int a[5]，函数里 a 的类型仍是 int *。
   sizeof 用旁边的 p 来看，得到指针的大小。a[0] = 99 会写进调用者的数组。 */
static void as_array(int a[5])
{
    int *p = a;

    printf("  sizeof 形参指针 %zu，a[2] = %d\n", sizeof p, a[2]);
    a[0] = 99;
}

/* int a[] 和 int a[5]、int *a 是同一种形参。这里只读 a[1]，不改数组。 */
static void as_open(int a[])
{
    int *p = a;

    printf("  sizeof 形参指针 %zu，a[1] = %d\n", sizeof p, a[1]);
}

/* 形参直接写成 int *。sizeof a 就是这个指针的大小。 */
static void as_pointer(int *a)
{
    printf("  sizeof 形参指针 %zu，a[4] = %d\n", sizeof a, a[4]);
}

/* block 指向整段 5 个 int。sizeof *block 仍是数组的 20 字节，不是指针的 8 字节。
   实参要传 &nums。 */
static void as_block(int (*block)[5])
{
    printf("  sizeof *block %zu，(*block)[2] = %d\n",
           sizeof *block, (*block)[2]);
}

/* g 的类型是 int (*)[3]，sizeof 这个行指针是 8。
   g[0] 是一行，sizeof 是 12。g[1][2] 读到 6。 */
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

    /* main 里 nums 还是数组，sizeof 是 20。传进函数之后才变成指针。 */
    printf("1. main 里 sizeof nums\n");
    printf("  %zu\n", sizeof nums);

    /* 函数里看到的是 8 字节，a[2] 仍是 30。返回后 nums[0] 已被写成 99。 */
    printf("2. 形参 int a[5]\n");
    as_array(nums);
    printf("  main 里 nums[0] = %d\n", nums[0]);

    /* a[] 和 int * 看到的也是 8 字节。a[1] 是 20，a[4] 是 50，这两次没有改数组。 */
    printf("3. 形参 int a[]\n");
    as_open(nums);
    printf("4. 形参 int *a\n");
    as_pointer(nums);
    /* &nums 的类型才是 int (*)[5]。*block 仍是那 5 个 int，sizeof 是 20，[2] 是 30。 */
    printf("5. 形参 int (*block)[5]，实参是 &nums\n");
    as_block(&nums);
    /* 行指针 8 字节，一行 12 字节，g[1][2] 是 6。 */
    printf("6. 形参 int g[][3]\n");
    as_rows(grid);
    return 0;
}
