/* 案例：指针函数。函数自己返回一个指针，调用处再 * 或 [] 才碰到那个对象。
   从名字往外读：名字右边是 ()，它是函数；返回类型里的 * 说明它交回来的是地址。
   nums 是 {10, 20, 30, 40, 50}，nums[3] 一开始是 40。 */
#include <stdio.h>

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

/* 返回 nums[index] 的地址，类型是 int *。不要返回局部变量的地址，那块内存函数结束就没了。 */
static int *element(int *p, int index)
{
    return p+index;
}

/* p + index 和 &p[index] 是同一地址。 */
static int *by_offset(int *p, int index)
{
    return p + index;
}

/* 下标不合法时交回 NULL。调用者要先看是不是 NULL，再 *。 */
static int *maybe(int *p, int index)
{
    if (index < 0)
        return NULL;
    return &p[index];
}

/* box 是 static，函数返回后这块 int 还在。每次调用返回的都是它的地址。 */
static int *held(void)
{
    static int box = 7;

    return &box;
}

/* 返回的是 slot[index] 这个指针格子的地址，类型是 int **。 */
static int **slot_of(int **slot, int index)
{
    return &slot[index];
}

/* 名字 one_row 右边是 (int grid[][3], int r)，所以它是函数。
   返回类型是 int (*)[3]：指向一整行 3 个 int 的指针。 */
static int (*one_row(int grid[][3], int r))[3]
{
    return &grid[r];
}

/* 返回类型是 int (*)(int, int)：一个函数指针。which 为 0 交回 add，否则交回 sub。 */
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

    /* element 交回 &nums[3]，再 * 读到 40。 */
    printf("1. *element(nums, 3)\n");
    printf("  %d\n", *element(nums, 3));
    /* 地址可以先存进 found，之后 *found 仍是 40。 */
    found = element(nums, 3);
    printf("2. 存进 found 再 *found\n");
    printf("  %d\n", *found);

    /* 返回的 int * 可以再当数组用。[0] 就是它指着的那个 int。0[p] 和 p[0] 相同。 */
    printf("3. element(nums, 3)[0]\n");
    printf("  %d\n", element(nums, 3)[0]);
    printf("4. 0[element(nums, 3)]\n");
    printf("  %d\n", 0[element(nums, 3)]);

    /* &p[3] 和 p + 3 是同一地址。 */
    printf("5. by_offset 和 element 返回的地址\n");
    printf("  %s\n",
           (*by_offset(nums, 3) == *element(nums, 3)) ? "相同" : "不同");

    /* 下标为负，交回空指针。这里只比较，不 *。 */
    printf("6. maybe(nums, -1) == NULL ?\n");
    printf("  %s\n", maybe(nums, -1) == NULL ? "是" : "否");
    /* 下标 1 合法，* 读到 20。 */
    printf("7. *maybe(nums, 1)\n");
    printf("  %d\n", *maybe(nums, 1));

    /* 两次调用返回同一块 static。先读到 7，再写 8，下一次仍读到 8。 */
    printf("8. *held()\n");
    printf("  %d\n", *held());
    *held() = 8;
    printf("9. *held() = 8 之后再读\n");
    printf("  %d\n", *held());

    /* slot[1] 里是 &b。** 先拿到这个 int *，再读到 20。 */
    printf("10. **slot_of(slot, 1)\n");
    printf("  %d\n", **slot_of(slot, 1));
    /* where 指向 slot[1] 这格。*where = &a 把这格改成 &a，*slot[1] 变成 10。
       b 自己还是 20，变的是指针格子里存的地址。 */
    where = slot_of(slot, 1);
    *where = &a;
    printf("11. *where = &a 之后 *slot[1]\n");
    printf("  %d\n", *slot[1]);

    /* one_row(grid, 1) 指向 {4, 5, 6}。再 [2] 读到 6。 */
    printf("12. (*one_row(grid, 1))[2]\n");
    printf("  %d\n", (*one_row(grid, 1))[2]);

    /* choose(0) 交回 add。后面再写 (20, 3) 才调用，20 + 3 = 23。
       choose(1) 交回 sub，20 - 3 = 17。(*choose(1)) 先 * 再调用，结果一样。 */
    printf("13. choose(0)(20, 3)\n");
    printf("  %d\n", choose(0)(20, 3));
    printf("14. (*choose(1))(20, 3)\n");
    printf("  %d\n", (*choose(1))(20, 3));
    /* 返回的函数指针可以存进 picked，之后 picked(20, 3) 仍是 add。 */
    picked = choose(0);
    printf("15. picked = choose(0) 之后 picked(20, 3)\n");
    printf("  %d\n", picked(20, 3));

    /* *element(...) 是 nums[3] 这一格，赋值会改到数组里。nums[3] 变成 99。 */
    *element(nums, 3) = 99;
    printf("16. *element(nums, 3) = 99 之后 nums[3]\n");
    printf("  %d\n", nums[3]);
    return 0;
}
