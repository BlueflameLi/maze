//this code is GB2312
#ifndef _FUN_H_
#define _FUN_H_

//�����س���ȷ��
#define E_CHECK                        \
    {                                  \
        char ch;                       \
        while (ch = getchar() != '\n') \
            ;                          \
    }

//���������
#define CLEAR_BUF                                     \
    {                                                 \
        int ch;                                       \
        while ((ch = getchar()) != EOF && ch != '\n') \
        {                                             \
            ;                                         \
        }                                             \
    }

//������
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

//�����ʾ��
#define PSTR(a) puts(str[a])

//��ʾ��
char *str[5];

//�����ͼ�͵����ͼѡ��
void fun();

//y/nѡ��
int switch_yn(int k);

#endif