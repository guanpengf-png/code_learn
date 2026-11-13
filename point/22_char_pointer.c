/* 案例：字符指针。text 可以改成指向另一串字符。 */
#include <stdio.h>

int main(void)
{
    const char *text = "abc";

    printf("现在 %s\n", text);
    text = "hello";
    printf("改指向之后 %s\n", text);
    return 0;
}
