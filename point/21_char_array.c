/* 案例：字符数组。word 里有一份可以改的字符，含结尾的 \\0。 */
#include <stdio.h>

int main(void)
{
    char word[] = "abc";

    printf("改之前 %s\n", word);
    word[0] = 'A';
    printf("改之后 %s\n", word);
    return 0;
}
