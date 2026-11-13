/* 案例：指针函数。函数返回一个指针。
   nums 是 {10, 20, 30, 40, 50}。 */
#include <stdio.h>

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

static int *element(int *p, int index)
{
    return &p[index];
}

static int *by_offset(int *p, int index)
{
    return p + index;
}

static int *maybe(int *p, int index)
{
    if (index < 0)
        return NULL;
    return &p[index];
}

static int *held(void)
{
    static int box = 7;

    return &box;
}

static int **slot_of(int **slot, int index)
{
    return &slot[index];
}

static int (*one_row(int grid[][3], int r))[3]
{
    return &grid[r];
}

static int (*choose(int which))(int, int)
{
    if (which == 0)
        return add;
    return sub;
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int a = 10;
    int b = 20;
    int c = 30;
    int *slot[3] = {&a, &b, &c};
    int *found;
    int **where;
    int (*picked)(int, int);

    printf("1. *element(nums, 3)\n");
    printf("  %d\n", *element(nums, 3));
    found = element(nums, 3);
    printf("2. 存进 found 再 *found\n");
    printf("  %d\n", *found);

    printf("3. element(nums, 3)[0]\n");
    printf("  %d\n", element(nums, 3)[0]);
    printf("4. 0[element(nums, 3)]\n");
    printf("  %d\n", 0[element(nums, 3)]);

    printf("5. by_offset 和 element 返回的地址\n");
    printf("  %s\n",
           (by_offset(nums, 3) == element(nums, 3)) ? "相同" : "不同");

    printf("6. maybe(nums, -1) == NULL ?\n");
    printf("  %s\n", maybe(nums, -1) == NULL ? "是" : "否");
    printf("7. *maybe(nums, 1)\n");
    printf("  %d\n", *maybe(nums, 1));

    printf("8. *held()\n");
    printf("  %d\n", *held());
    *held() = 8;
    printf("9. *held() = 8 之后再读\n");
    printf("  %d\n", *held());

    printf("10. **slot_of(slot, 1)\n");
    printf("  %d\n", **slot_of(slot, 1));
    where = slot_of(slot, 1);
    *where = &a;
    printf("11. *where = &a 之后 *slot[1]\n");
    printf("  %d\n", *slot[1]);

    printf("12. (*one_row(grid, 1))[2]\n");
    printf("  %d\n", (*one_row(grid, 1))[2]);

    printf("13. choose(0)(20, 3)\n");
    printf("  %d\n", choose(0)(20, 3));
    printf("14. (*choose(1))(20, 3)\n");
    printf("  %d\n", (*choose(1))(20, 3));
    picked = choose(0);
    printf("15. picked = choose(0) 之后 picked(20, 3)\n");
    printf("  %d\n", picked(20, 3));

    *element(nums, 3) = 99;
    printf("16. *element(nums, 3) = 99 之后 nums[3]\n");
    printf("  %d\n", nums[3]);
    return 0;
}
