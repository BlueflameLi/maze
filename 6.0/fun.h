//this code is GB2312
#ifndef _FUN_H_
#define _FUN_H_

//读到回车键确认
#define E_CHECK                        \
    {                                  \
        char ch;                       \
        while (ch = getchar() != '\n') \
            ;                          \
    }

//清除缓存区
#define CLEAR_BUF                                     \
    {                                                 \
        int ch;                                       \
        while ((ch = getchar()) != EOF && ch != '\n') \
        {                                             \
            ;                                         \
        }                                             \
    }

//输入检查
#define INPUT_CHECK(a, b)                \
    {                                    \
        while ((t = a) != EOF)           \
            if (b)                       \
            {                            \
                puts("Please re-enter"); \
                CLEAR_BUF                \
            }                            \
            else                         \
                break;                   \
    }

//输出提示语
#define PSTR(a) puts(str[a])

//提示语
char *str[5];

//随机地图和导入地图选择
void fun();

//y/n选择
int switch_yn(int k);

#endif