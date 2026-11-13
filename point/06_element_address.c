/* 案例：元素地址。下面这些地址都指着 30，nums[2] 是 30。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;
    int i = 2;

    printf("1. *(&nums[i])\n");
    printf("  %d\n", *(&nums[i]));
    printf("2. nums + i 与 &nums[i]\n");
    printf("  %s\n", (nums + i == &nums[i]) ? "相同" : "不同");
    printf("3. &i[nums] 与 nums + i\n");
    printf("  %s\n", (&i[nums] == nums + i) ? "相同" : "不同");
    printf("4. &*(nums + i) 与 nums + i\n");
    printf("  %s\n", (&*(nums + i) == nums + i) ? "相同" : "不同");
    printf("5. &p[i] 与 p + i\n");
    printf("  %s\n", (&p[i] == p + i) ? "相同" : "不同");
    printf("6. &nums[0] 与 nums\n");
    printf("  %s\n", (&nums[0] == nums) ? "相同" : "不同");
    printf("7. &nums 和 &nums[0] 的地址\n");
    printf("  %s\n", ((void *)&nums == (void *)&nums[0]) ? "相同" : "不同");

    printf("8. sizeof nums\n");
    printf("  %zu\n", sizeof nums);
    printf("9. sizeof &nums[0]\n");
    printf("  %zu\n", sizeof &nums[0]);
    printf("10. sizeof &nums\n");
    printf("  %zu\n", sizeof &nums);
    printf("11. *(&nums[0] + i)\n");
    printf("  %d\n", *(&nums[0] + i));
    return 0;
}
