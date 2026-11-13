/* 案例：一级指针。p 里放着 a 的地址，*p 就是 a。
   下面每种写法都打出当前这个数。 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 50;
    int *p = &a;
    int *q;
    const int *cp;
    int *const fp = &a;
    const int *const both = &b;
    void *vp;
    int *via;

    printf("1. *p\n");
    printf("  %d\n", *p);

    *p = 20;
    printf("2. *p = 20 之后 a\n");
    printf("  %d\n", a);

    printf("3. p 和 &a\n");
    printf("  %s\n", (p == &a) ? "相同" : "不同");
    printf("4. &*p 和 p\n");
    printf("  %s\n", (&*p == p) ? "相同" : "不同");
    printf("5. *&a\n");
    printf("  %d\n", *&a);

    q = p;
    *q = 30;
    printf("6. 另一个指针 q = p，*q = 30 之后 *p\n");
    printf("  %d\n", *p);

    cp = &a;
    printf("7. const int *cp 读 *cp\n");
    printf("  %d\n", *cp);
    cp = &b;
    printf("8. cp 改指向 b 之后 *cp\n");
    printf("  %d\n", *cp);

    *fp = 40;
    printf("9. int *const fp 写 *fp 之后 a\n");
    printf("  %d\n", a);
    printf("10. fp 和 &a\n");
    printf("  %s\n", (fp == &a) ? "相同" : "不同");

    printf("11. const int *const both 读 *both\n");
    printf("  %d\n", *both);

    vp = &a;
    printf("12. *(int *)vp\n");
    printf("  %d\n", *(int *)vp);

    via = *&p;
    printf("13. *&p 再解引用\n");
    printf("  %d\n", *via);
    return 0;
}
