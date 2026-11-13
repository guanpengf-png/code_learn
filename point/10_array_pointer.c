/* 案例：数组指针。block 的类型是 int (*)[5]，指向整段 nums。
   p 的类型是 int *，指向第一个元素。两个指针从同一个字节出发。
   sizeof nums 和 sizeof *block 都是 20；sizeof p 是指针，这里是 8。
   第 1–9 条都读 nums[2]，也就是 30。 */
#include <stdio.h>

/* 形参 block 是 &nums 的副本。(*block)[2] 仍读原来的 30。
   实参必须是 &nums，类型才是 int (*)[5]。 */
static int at2(int (*block)[5])
{
    return (*block)[2];
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int (*block)[5] = &nums;
    int *p = nums;
    int k;

    printf("sizeof nums = %zu，sizeof *block = %zu，sizeof p = %zu\n",
           sizeof nums, sizeof *block, sizeof p);

    /* 先 * 取出整段数组，再取下标 2。 */
    printf("1. (*block)[2]\n");
    printf("  %d\n", (*block)[2]);
    /* block[0] 就是 *block。 */
    printf("2. block[0][2]\n");
    printf("  %d\n", block[0][2]);
    /* *block 退化成 int *，再跨 2 个 int。 */
    printf("3. *(*block + 2)\n");
    printf("  %d\n", *(*block + 2));
    printf("4. *(block[0] + 2)\n");
    printf("  %d\n", *(block[0] + 2));
    /* 2[*block] 是 *(2 + *block)。 */
    printf("5. 2[*block]\n");
    printf("  %d\n", 2[*block]);
    printf("6. 2[block[0]]\n");
    printf("  %d\n", 2[block[0]]);
    /* & 和 * 抵消，还是这一格。 */
    printf("7. *&(*block)[2]\n");
    printf("  %d\n", *&(*block)[2]);
    /* p 一步 4 字节，p[2] 同样到 30。 */
    printf("8. p[2]，p 的类型是 int *\n");
    printf("  %d\n", p[2]);
    printf("9. at2(&nums)\n");
    printf("  %d\n", at2(&nums));

    /* block 没有被移动，从下标 0 读到 4。 */
    printf("10. (*block)[k] 整段\n");
    printf("  ");
    for (k = 0; k < 5; k++)
        printf("%d ", (*block)[k]);
    printf("\n");
    return 0;
}
