/* 案例：函数指针当参数。apply 在自己内部调用传进来的函数。 */
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

static void apply(int *p, int (*fn)(int))
{
    *p = fn(*p);
}

static void apply_deref(int *p, int (*fn)(int))
{
    *p = (*fn)(*p);
}

static int call2(int a, int b, int (*fn)(int, int))
{
    return fn(a, b);
}

static int keep_if_null(int x, int (*fn)(int))
{
    if (fn == NULL)
        return x;
    return fn(x);
}

static void each(int *p, int n, int (*fn)(int))
{
    int i;

    for (i = 0; i < n; i++)
        p[i] = fn(p[i]);
}

int main(void)
{
    int n = 10;
    int (*op)(int) = inc;
    int nums[3] = {10, 20, 30};
    int i;

    printf("1. apply(&n, inc)\n");
    apply(&n, inc);
    printf("  %d\n", n);

    printf("2. apply(&n, &dec)\n");
    apply(&n, &dec);
    printf("  %d\n", n);

    printf("3. apply(&n, twice)\n");
    apply(&n, twice);
    printf("  %d\n", n);

    printf("4. apply(&n, op)，op 里是 inc\n");
    apply(&n, op);
    printf("  %d\n", n);

    printf("5. apply_deref(&n, inc)，函数里写 (*fn)(*p)\n");
    apply_deref(&n, inc);
    printf("  %d\n", n);

    printf("6. call2(20, 3, add)\n");
    printf("  %d\n", call2(20, 3, add));
    printf("7. call2(20, 3, &sub)\n");
    printf("  %d\n", call2(20, 3, &sub));

    printf("8. keep_if_null(10, NULL)\n");
    printf("  %d\n", keep_if_null(10, NULL));
    printf("9. keep_if_null(10, inc)\n");
    printf("  %d\n", keep_if_null(10, inc));

    printf("10. each(nums, 3, inc)\n");
    each(nums, 3, inc);
    printf("  ");
    for (i = 0; i < 3; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}
