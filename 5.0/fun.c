#include "fun.h"
#include "map.h"

char *str[4] = {"Do you want to use the default map ? [y / n] ",
                "Do you want to use the default direction order? [y/n] ",
                "Please choose to generate map randomly or import map\n"
                "[1] import map\n"
                "[2] Randomly generated map",
                "Please input the maze size n and m:"};

//�����ͼ�͵����ͼѡ��
void fun()
{
    //ˢ����Ļ
    CLS;

    PSTR(2);

    int k, t;
    INPUT_CHECK(scanf("%d", &k), t != 1 || k < 1 || k > 2)

    if (k == 1)
        readmap(); //�����ͼ
    else
    {
        CLS;
        PSTR(3);
        INPUT_CHECK(scanf("%d%d", &n, &m), t != 2 || n < 3 || m < 3)

        //�����ͼ
        maprand();
    }
}

//y/nѡ��
void switch_yn(int k)
{
    PSTR(k);
    char c;
    while (c = getchar())
        if (c == 'y' || c == 'Y')
        {
            E_CHECK
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            E_CHECK

            k ? drand() : fun();

            break;
        }
}