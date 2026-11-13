/* 案例：下标。a[b] 就是 *(a + b)，加法左右可以换。
   nums 是 {10, 20, 30, 40, 50}，i 是 2。第 1–10 条都进到 30。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;       /* 退化后的首元素地址，指向 10 */
    int *at = nums + 2;  /* 已经站在 30 上 */
    int i = 2;
    int k;

    /* *(nums + 2)。数组名在表达式里退化成 int *。 */
    printf("1. nums[i]\n");
    printf("  %d\n", nums[i]);
    /* *(2 + nums)。和上一条是同一格。 */
    printf("2. i[nums]\n");
    printf("  %d\n", i[nums]);
    printf("3. *(nums + i)\n");
    printf("  %d\n", *(nums + i));
    printf("4. *(i + nums)\n");
    printf("  %d\n", *(i + nums));
    /* p 里已经是首元素地址，p[2] 就是 *(p + 2)。 */
    printf("5. p[i]\n");
    printf("  %d\n", p[i]);
    printf("6. i[p]\n");
    printf("  %d\n", i[p]);
    printf("7. *(p + i)\n");
    printf("  %d\n", *(p + i));
    printf("8. *(i + p)\n");
    printf("  %d\n", *(i + p));
    /* &nums[0] 就是退化后的 nums。 */
    printf("9. (&nums[0])[i]\n");
    printf("  %d\n", (&nums[0])[i]);
    /* & 和 * 抵消，就是 nums[2]。 */
    printf("10. *(&nums[i])\n");
    printf("  %d\n", *(&nums[i]));

    /* 下标从 at 当前这格往两边数：at[-1] 是 *(at - 1)，还在数组里面。 */
    printf("11. at 指向第 2 个，at[0]\n");
    printf("  %d\n", at[0]);
    printf("12. at[-1]\n");
    printf("  %d\n", at[-1]);
    printf("13. at[1]\n");
    printf("  %d\n", at[1]);

    /* p 一直指向开头。k 从 0 到 4，打出整段。 */
    printf("14. 用 p[k] 走完整段\n");
    printf("  ");
    for (k = 0; k < 5; k++)
        printf("%d ", p[k]);
    printf("\n");
    return 0;
}
