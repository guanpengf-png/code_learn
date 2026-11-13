/* 案例：指针数组怎么遍历。slot 有 3 个元素，每个元素都是一个 int *。
   下面每一种都打出 10、20、30。 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 20;
    int c = 30;
    int *slot[3] = {&a, &b, &c};
    int **p = slot;
    int *(*block)[3] = &slot;
    int i;

    /* 1. 下标：slot[i] 是第 i 个指针，再 * 才是它指着的数。 */
    printf("1. *slot[i]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *slot[i]);

    /* 2. 下标对调。和 05 一样：i[slot] 就是 slot[i]。 */
    printf("2. *i[slot]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *i[slot]);

    /* 3. 先移到第 i 个指针，再解两层。slot + i 的类型是 int **。 */
    printf("3. **(slot + i)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(slot + i));

    /* 4. 用元素地址。&slot[i] 和 slot + i 是同一个地址。 */
    printf("4. **(&slot[i])\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(&slot[i]));

    /* 5. 每个元素是指针，可以再当成长度为 1 的数组。
       slot[i][0] 就是 *(slot[i] + 0)。 */
    printf("5. slot[i][0]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", slot[i][0]);

    /* 6. 复制出一个二级指针，按下标走。p 自己不动。 */
    printf("6. **(p + i)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(p + i));

    /* 7. 二级指针自己往前走。*p++ 只解开一层，得到的是指针；
       要打出 int，得 *(*p++)。走完后 p 已经越过最后一个元素。 */
    printf("7. *(*p++)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *(*p++));

    /* 8. 数组指针包住整段。block 一步跨过 3 个 int *，
       (*block)[i] 才是里面的第 i 个指针。 */
    printf("8. *(*block)[i]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *(*block)[i]);

    return 0;
}
