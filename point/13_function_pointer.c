/* 案例：函数指针和指针函数。
   从名字往外读：名字右边是 ()，它是函数；名字被 (* ) 包住，它是指针。
   函数指针里放的是函数地址。指针函数返回一个指针。
   下面每种写法都打出它算出来的数。 */
#include <stdio.h>

typedef int (*Binary)(int, int);

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

/* 指针函数：返回 int *。 */
static int *element(int *p, int index)
{
    return &p[index];
}

/* 指针函数：返回「指向 3 个 int 的数组」的指针，类型是 int (*)[3]。 */
static int (*one_row(int grid[][3], int r))[3]
{
    return &grid[r];
}

/* 指针函数：返回一个函数指针。 */
static int (*choose(int which))(int, int)
{
    if (which == 0)
        return add;
    return sub;
}

/* 参数 fn 是函数指针。 */
static int apply(int a, int b, int (*fn)(int, int))
{
    return fn(a, b);
}

int main(void)
{
    int (*op)(int, int) = add;
    int nums[5] = {10, 20, 30, 40, 50};
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int *(*back)(int *, int) = element;
    int (*picked)(int, int);
    int (*(*chooser)(int))(int, int) = choose;
    int (*ops[2])(int, int) = {add, sub};
    int (*(*bundle)[2])(int, int) = &ops;
    int *(*backs[1])(int *, int) = {element};
    Binary named = sub;

    /* 1. 函数指针直接调用。op 里现在是 add。 */
    printf("1. op(20, 3)\n");
    printf("  %d\n", op(20, 3));

    /* 2. 先 * 取出函数，再调用。 */
    printf("2. (*op)(20, 3)\n");
    printf("  %d\n", (*op)(20, 3));

    /* 3. 函数名用在表达式里会退化成函数指针，再 * 一次还能调用。 */
    printf("3. (**op)(20, 3)\n");
    printf("  %d\n", (**op)(20, 3));

    /* 4. 换成 sub。函数名和 &函数名 赋进去是同一个地址。 */
    op = &sub;
    printf("4. op = &sub 之后 op(20, 3)\n");
    printf("  %d\n", op(20, 3));
    printf("5. add 和 &add\n");
    printf("  %s\n", (add == &add) ? "相同" : "不同");
    printf("6. (&add)(20, 3)\n");
    printf("  %d\n", (&add)(20, 3));

    /* 7. 指针函数。element 返回 nums[3] 的地址，再 * 得到 40。 */
    printf("7. *element(nums, 3)\n");
    printf("  %d\n", *element(nums, 3));

    /* 8. 返回的指针可以再当数组用。 [0] 就是它指着的那个 int。 */
    printf("8. element(nums, 3)[0]\n");
    printf("  %d\n", element(nums, 3)[0]);
    printf("9. 0[element(nums, 3)]\n");
    printf("  %d\n", 0[element(nums, 3)]);

    /* 10. back 的类型是 int *(*)(int *, int)，指向指针函数 element。
       () 比 * 紧，*back(...) 先调用，得到 int *，再解引用。 */
    printf("10. *back(nums, 3)\n");
    printf("  %d\n", *back(nums, 3));
    printf("11. *(*back)(nums, 3)\n");
    printf("  %d\n", *(*back)(nums, 3));

    /* 12. 返回数组指针。one_row(grid, 1) 指着 {4, 5, 6}。 */
    printf("12. (*one_row(grid, 1))[2]\n");
    printf("  %d\n", (*one_row(grid, 1))[2]);

    /* 13. 返回函数指针，调用处再写一对 () 才执行 add 或 sub。 */
    printf("13. choose(0)(20, 3)\n");
    printf("  %d\n", choose(0)(20, 3));
    printf("14. (*choose(1))(20, 3)\n");
    printf("  %d\n", (*choose(1))(20, 3));
    picked = choose(0);
    printf("15. 把返回的函数指针存进 picked，picked(20, 3)\n");
    printf("  %d\n", picked(20, 3));

    /* 16. chooser 是函数指针，指向「返回函数指针的函数」choose。 */
    printf("16. chooser(0)(20, 3)\n");
    printf("  %d\n", chooser(0)(20, 3));
    printf("17. (*chooser)(1)(20, 3)\n");
    printf("  %d\n", (*chooser)(1)(20, 3));

    /* 18. 函数指针当参数。传 add 或 &sub 都可以。 */
    printf("18. apply(20, 3, add)\n");
    printf("  %d\n", apply(20, 3, add));
    printf("19. apply(20, 3, &sub)\n");
    printf("  %d\n", apply(20, 3, &sub));

    /* 20. 函数指针数组。ops[i] 是一个函数指针。 */
    printf("20. ops[0](20, 3)\n");
    printf("  %d\n", ops[0](20, 3));
    printf("21. (*ops[1])(20, 3)\n");
    printf("  %d\n", (*ops[1])(20, 3));
    printf("22. 0[ops](20, 3)\n");
    printf("  %d\n", 0[ops](20, 3));

    /* 23. bundle 指向整段函数指针数组，一步跨过 ops 的两个元素。 */
    printf("23. (*bundle)[1](20, 3)\n");
    printf("  %d\n", (*bundle)[1](20, 3));

    /* 24. 数组元素是「指向指针函数的指针」。
       backs[0] 指向 element，调用后得到 int *，再解引用。 */
    printf("24. *backs[0](nums, 3)\n");
    printf("  %d\n", *backs[0](nums, 3));

    /* 25. typedef 给函数指针类型起名。Binary 就是 int (*)(int, int)。 */
    printf("25. named(20, 3)\n");
    printf("  %d\n", named(20, 3));

    return 0;
}
