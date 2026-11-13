/* 案例：下标。下面指向第 2 个元素的写法都打出 30。
   nums 是 {10, 20, 30, 40, 50}。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;
    int *at = nums + 2;
    int i = 2;
    int k;

    printf("1. nums[i]\n");
    printf("  %d\n", nums[i]);
    printf("2. i[nums]\n");
    printf("  %d\n", i[nums]);
    printf("3. *(nums + i)\n");
    printf("  %d\n", *(nums + i));
    printf("4. *(i + nums)\n");
    printf("  %d\n", *(i + nums));
    printf("5. p[i]\n");
    printf("  %d\n", p[i]);
    printf("6. i[p]\n");
    printf("  %d\n", i[p]);
    printf("7. *(p + i)\n");
    printf("  %d\n", *(p + i));
    printf("8. *(i + p)\n");
    printf("  %d\n", *(i + p));
    printf("9. (&nums[0])[i]\n");
    printf("  %d\n", (&nums[0])[i]);
    printf("10. *(&nums[i])\n");
    printf("  %d\n", *(&nums[i]));

    printf("11. at 指向第 2 个，at[0]\n");
    printf("  %d\n", at[0]);
    printf("12. at[-1]\n");
    printf("  %d\n", at[-1]);
    printf("13. at[1]\n");
    printf("  %d\n", at[1]);

    printf("14. 用 p[k] 走完整段\n");
    printf("  ");
    for (k = 0; k < 5; k++)
        printf("%d ", p[k]);
    printf("\n");
    return 0;
}
