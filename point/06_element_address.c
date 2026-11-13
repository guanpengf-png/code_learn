/* 案例：元素地址。第 2 格（30）的地址可以有好几种写法。
   起始字节可以相同，类型和 +1 跨过的字节可以不同。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;
    int i = 2;

    /* & 和 * 抵消之后就是 nums[2]，读到 30。 */
    printf("1. *(&nums[i])\n");
    printf("  %d\n", *(&nums[i]));
    /* nums + i 和 &nums[i] 都是第 i 格的地址。 */
    printf("2. nums + i 与 &nums[i]\n");
    printf("  %s\n", (nums + i == &nums[i]) ? "相同" : "不同");
    /* i[nums] 就是 nums[i]，再取地址还是同一格。 */
    printf("3. &i[nums] 与 nums + i\n");
    printf("  %s\n", (&i[nums] == nums + i) ? "相同" : "不同");
    /* &*(nums + i)：* 先走到元素，& 再取回地址，和 nums + i 相同。 */
    printf("4. &*(nums + i) 与 nums + i\n");
    printf("  %s\n", (&*(nums + i) == nums + i) ? "相同" : "不同");
    /* p 指向开头时，&p[i] 和 p + i 都是第 i 格。 */
    printf("5. &p[i] 与 p + i\n");
    printf("  %s\n", (&p[i] == p + i) ? "相同" : "不同");
    /* 表达式里的 nums 就是首元素地址，和 &nums[0] 相同。 */
    printf("6. &nums[0] 与 nums\n");
    printf("  %s\n", (&nums[0] == nums) ? "相同" : "不同");

    /* &nums 的类型是 int (*)[5]，&nums[0] 的类型是 int *。
       两者都从数组的第一个字节开始，转成 void * 之后地址相同。
       +1 的步长不同：&nums[0] + 1 跨 4 字节，&nums + 1 跨 20 字节。 */
    printf("7. &nums 和 &nums[0] 的地址\n");
    printf("  %s\n", ((void *)&nums == (void *)&nums[0]) ? "相同" : "不同");

    /* sizeof 里的数组名不退化，整段 5 个 int 是 20 字节。 */
    printf("8. sizeof nums\n");
    printf("  %zu\n", sizeof nums);
    /* 下面两个都是指针，64 位上各是 8 字节。 */
    printf("9. sizeof &nums[0]\n");
    printf("  %zu\n", sizeof &nums[0]);
    printf("10. sizeof &nums\n");
    printf("  %zu\n", sizeof &nums);
    /* 从首元素跨 2 步，再读，得到 30。 */
    printf("11. *(&nums[0] + i)\n");
    printf("  %d\n", *(&nums[0] + i));
    return 0;
}
