/* 案例：下标。nums[i]、i[nums]、*(nums + i) 是同一个元素。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int i = 2;

    printf("nums[i]     = %d\n", nums[i]);
    printf("i[nums]     = %d\n", i[nums]);
    printf("*(nums + i) = %d\n", *(nums + i));
    return 0;
}
