/* 案例：数组指针。block 指向整段有 5 个 int 的数组。
   下面每种写法都打出 nums[2]，也就是 30。 */
#include <stdio.h>

static int at2(int (*block)[5])
{
    return (*block)[2];
}

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int (*block)[5] = &nums;
    int *p = nums;

    printf("sizeof nums = %zu，sizeof *block = %zu，sizeof p = %zu\n",
           sizeof nums, sizeof *block, sizeof p);

    printf("1. (*block)[2]\n");
    printf("  %d\n", (*block)[2]);
    printf("2. block[0][2]\n");
    printf("  %d\n", block[0][2]);
    printf("3. *(*block + 2)\n");
    printf("  %d\n", *(*block + 2));
    printf("4. *(block[0] + 2)\n");
    printf("  %d\n", *(block[0] + 2));
    printf("5. 2[*block]\n");
    printf("  %d\n", 2[*block]);
    printf("6. 2[block[0]]\n");
    printf("  %d\n", 2[block[0]]);
    printf("7. *&(*block)[2]\n");
    printf("  %d\n", *&(*block)[2]);
    printf("8. p[2]，p 的类型是 int *\n");
    printf("  %d\n", p[2]);
    printf("9. at2(&nums)\n");
    printf("  %d\n", at2(&nums));
    printf("10. (*block)[k] 整段\n");
    printf("  ");
    {
        int k;

        for (k = 0; k < 5; k++)
            printf("%d ", (*block)[k]);
    }
    printf("\n");
    return 0;
}
