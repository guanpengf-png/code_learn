/* 案例：元素地址。&nums[i] 和 nums + i 是同一个地址。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int i = 2;

    printf("这个地址上的值 = %d\n", *(&nums[i]));
    printf("nums + i 与 &nums[i] 相同？ %s\n",
           (nums + i == &nums[i]) ? "相同" : "不同");
    return 0;
}
