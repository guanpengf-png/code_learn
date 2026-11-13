/* 案例：一级指针。p 里放着 a 的地址，*p 顺着地址走进 a。
   const 修饰它左边的那一个；左边什么都没有时，修饰右边紧挨着的那一个。 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 50;
    int *p = &a;                 /* 指针格子里是 &a，*p 就是 a */
    int *q;                      /* 等一下复制 p 里的地址 */
    const int *cp;               /* const 锁 int：能改指向，*cp 只能读 */
    int *const fp = &a;          /* const 锁指针格子：fp 一直是 &a，可以写 *fp */
    const int *const both = &b;  /* 指向和 *both 都锁住，只能读 b */
    void *vp;                    /* 只存地址，不带类型 */
    int *via;

    /* *p 走进 a，读到 10。p 自己没动。 */
    printf("1. *p\n");
    printf("  %d\n", *p);

    /* *p = 20 把 20 写进 a。p 里仍是 &a。 */
    *p = 20;
    printf("2. *p = 20 之后 a\n");
    printf("  %d\n", a);

    /* 两边都是 a 的地址。 */
    printf("3. p 和 &a\n");
    printf("  %s\n", (p == &a) ? "相同" : "不同");
    /* *p 是 a 这个对象，再 & 取回它的地址，和 p 里存的一样。 */
    printf("4. &*p 和 p\n");
    printf("  %s\n", (&*p == p) ? "相同" : "不同");
    /* &a 是地址，紧挨着的 * 走回去，读到 a 里的 20。 */
    printf("5. *&a\n");
    printf("  %d\n", *&a);

    /* q 复制了 p 里的地址，两个指针指着同一格 a。*q = 30 写的是 a，所以 *p 也读到 30。 */
    q = p;
    *q = 30;
    printf("6. 另一个指针 q = p，*q = 30 之后 *p\n");
    printf("  %d\n", *p);

    /* const 在 * 左边，锁的是 int。指针格子没锁，所以 cp 可以先指 a，再改去指 b。
       这里只读：先读到 a 里的 30，再读到 b 里的 50。*cp = ... 会被编译器拒绝。 */
    cp = &a;
    printf("7. const int *cp 读 *cp\n");
    printf("  %d\n", *cp);
    cp = &b;
    printf("8. cp 改指向 b 之后 *cp\n");
    printf("  %d\n", *cp);

    /* const 在 * 右边，锁的是指针格子。fp 不能再赋成 &b。*fp = 40 允许，a 变成 40。 */
    *fp = 40;
    printf("9. int *const fp 写 *fp 之后 a\n");
    printf("  %d\n", a);
    printf("10. fp 和 &a\n");
    printf("  %s\n", (fp == &a) ? "相同" : "不同");

    /* 两边都锁。both 一直指向 b，*both 只读，读到 50。 */
    printf("11. const int *const both 读 *both\n");
    printf("  %d\n", *both);

    /* void * 能接任何对象的地址，但不能直接 *vp。先转回 int *，再 *，读到 a 里的 40。 */
    vp = &a;
    printf("12. *(int *)vp\n");
    printf("  %d\n", *(int *)vp);

    /* &p 是指针变量自己的地址，类型是 int **。*&p 走回去，得到 p 里的 &a。
       via 因此也指向 a，*via 是 40。 */
    via = *&p;
    printf("13. *&p 再解引用\n");
    printf("  %d\n", *via);
    return 0;
}
