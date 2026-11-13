/* 案例：函数指针当参数。形参 fn 的格子里是调用者传来的函数地址。
   函数名和 &函数名 传进去是同一个地址。调用前要先看 fn 是不是 NULL。 */
#include <stdio.h>

static int inc(int x)
{
    return x + 1;
}

static int dec(int x)
{
    return x - 1;
}

static int twice(int x)
{
    return x * 2;
}

static int add(int a, int b)
{
    return a + b;
}

static int sub(int a, int b)
{
    return a - b;
}

/* p 指向调用者的 int。fn(当前值) 算出新数，再写回那一格。 */
static void apply(int *p, int (*fn)(int))
{
    *p = fn(*p);
}

/* (*fn) 先取出函数再调用，和 fn(...) 调用的是同一个函数。 */
static void apply_deref(int *p, int (*fn)(int))
{
    *p = (*fn)(*p);
}

/* fn 收两个 int。这里只把结果交回来，不改调用者的变量。 */
static int call2(int a, int b, int (*fn)(int, int))
{
    return fn(a, b);
}

/* 格子里是 NULL 时不要调用。原数原样交回。 */
static int keep_if_null(int x, int (*fn)(int))
{
    if (fn == NULL)
        return x;
    return fn(x);
}

/* 同一个函数指针套到连续的 n 个 int 上。p[i] = fn(p[i]) 写回原数组。 */
static void each(int *p, int n, int (*fn)(int))
{
    int i;

    for (i = 0; i < n; i++)
        p[i] = fn(p[i]);
}

int main(void)
{
    int n = 10;
    int (*op)(int) = inc; /* op 和直接写 inc 指的是同一个函数 */
    int nums[3] = {10, 20, 30};
    int i;

    /* inc 把 10 加 1，写回 n，得到 11。传的是函数名。 */
    printf("1. apply(&n, inc)\n");
    apply(&n, inc);
    printf("  %d\n", n);

    /* &dec 和 dec 是同一个地址。11 减 1，n 回到 10。 */
    printf("2. apply(&n, &dec)\n");
    apply(&n, &dec);
    printf("  %d\n", n);

    /* 10 乘 2，n 变成 20。 */
    printf("3. apply(&n, twice)\n");
    apply(&n, twice);
    printf("  %d\n", n);

    /* 参数也可以是已经装好地址的函数指针变量。20 加 1，n 变成 21。 */
    printf("4. apply(&n, op)，op 里是 inc\n");
    apply(&n, op);
    printf("  %d\n", n);

    /* 函数里面写成 (*fn)(*p)，21 再加 1，n 变成 22。 */
    printf("5. apply_deref(&n, inc)，函数里写 (*fn)(*p)\n");
    apply_deref(&n, inc);
    printf("  %d\n", n);

    /* add(20, 3) 是 23。&sub 和 sub 相同，20 - 3 是 17。 */
    printf("6. call2(20, 3, add)\n");
    printf("  %d\n", call2(20, 3, add));
    printf("7. call2(20, 3, &sub)\n");
    printf("  %d\n", call2(20, 3, &sub));

    /* NULL 不调用，交回 10。inc 则会把 10 加成 11，这里没有写回某个变量。 */
    printf("8. keep_if_null(10, NULL)\n");
    printf("  %d\n", keep_if_null(10, NULL));
    printf("9. keep_if_null(10, inc)\n");
    printf("  %d\n", keep_if_null(10, inc));

    /* 10 20 30 各自加 1，数组变成 11 21 31。 */
    printf("10. each(nums, 3, inc)\n");
    each(nums, 3, inc);
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}
