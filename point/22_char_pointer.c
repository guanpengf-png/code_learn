/* 案例：字符指针。text 可以改成指向另一串字符。
   字面量那份字符不要通过指针去改。word 数组里的字符可以改。 */
#include <stdio.h>

int main(void)
{
    const char *text = "abc";
    char word[] = "abc";
    char *writable = word;
    char *const fixed = word;
    const char *view = word;
    const char *rows[2] = {"abc", "hello"};
    const char **sp = rows;
    const char **walk;

    printf("1. text\n");
    printf("  %s\n", text);
    printf("2. text + 1\n");
    printf("  %s\n", text + 1);
    text = "hello";
    printf("3. text = \"hello\"\n");
    printf("  %s\n", text);
    printf("4. sizeof text，这是指针\n");
    printf("  %zu\n", sizeof text);
    printf("5. sizeof word，这是数组\n");
    printf("  %zu\n", sizeof word);

    writable[0] = 'A';
    printf("6. writable[0] = 'A' 之后 word\n");
    printf("  %s\n", word);
    view = view + 1;
    printf("7. const char *view 改指向 word + 1\n");
    printf("  %s\n", view);

    *fixed = 'Z';
    printf("8. char *const fixed 写 *fixed 之后 word\n");
    printf("  %s\n", word);
    printf("9. fixed 和 word\n");
    printf("  %s\n", (fixed == word) ? "相同" : "不同");

    printf("10. sp[0]、*(sp + 1)\n");
    printf("  %s %s\n", sp[0], *(sp + 1));
    printf("11. *walk++ 两串\n");
    walk = rows;
    printf("  %s\n", *walk++);
    printf("  %s\n", *walk++);
    return 0;
}
