/* 案例：指针数组。slot 的每个元素都是一个 int *，里面放的是 a、b、c 的地址。
   用 i = 1 来看：先走到 slot[1] 里的 &b，再 * 才读到 20。
   p 是 int **，一步 8 字节，跨过一个指针。
   block 是 int *(*)[3]，指向整段 slot，一步 24 字节。
   下面每一种都打出 10、20、30。 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 20;
    int c = 30;
    int *slot[3] = {&a, &b, &c};
    int **p = slot;              /* 和退化后的 slot 指向同一格，循环里先不移动它 */
    int *(*block)[3] = &slot;    /* 包住整段 3 个 int * */
    int i;

    /* [] 比 * 紧。slot[i] 先取出 int *，再 * 读它指着的数。 */
    printf("1. *slot[i]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *slot[i]);

    /* i[slot] 是 *(i + slot)，和 slot[i] 同一格。 */
    printf("2. *i[slot]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *i[slot]);

    /* slot 退化成 int **。slot + i 跨过 i 个指针。
       第一层 * 得到 int *，第二层 * 得到那个 int。 */
    printf("3. **(slot + i)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(slot + i));

    /* &slot[i] 和 slot + i 是同一个地址，类型也是 int **。 */
    printf("4. **(&slot[i])\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(&slot[i]));

    /* slot[i] 是指针。再写 [0] 就是 *(slot[i] + 0)，读它指着的那一个 int。 */
    printf("5. slot[i][0]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", slot[i][0]);

    /* p 是 slot 的副本。这里只用 p + i，没有给 p 赋值，走完 p 仍指着 slot[0]。 */
    printf("6. **(p + i)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", **(p + i));

    /* *p++ 只解开一层，得到的是 int *。再写一层 * 才是 int。
       每读一个数，p 就移到下一个指针。走完后 p 停在最后一个元素的后面。 */
    printf("7. *(*p++)\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *(*p++));

    /* block 没有跟着第 7 条移动。*block 是整段 slot，
       (*block)[i] 是里面的 int *，再 * 得到 10、20、30。
       *(*slot + i) 不是这种走法：*slot 已经是 &a，+ i 按 int 从 a 旁边挪，到不了 b。 */
    printf("8. *(*block)[i]\n");
    for (i = 0; i < 3; i++)
        printf("   %d\n", *(*block)[i]);

    return 0;
}
