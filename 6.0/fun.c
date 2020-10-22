#include "fun.h"
#include "map.h"

char *str[5] = {"Do you want to use the default map ? [y / n]",
                "Do you want to use the default direction order? [y/n]",
                "Please choose to generate map randomly or import map\n"
                "[1] import map\n"
                "[2] Randomly generated map",
                "Please input the maze size n and m:",
                "Do you want to show multiple paths? the number of paths may be large [y/n]"};

//随机地图和导入地图选择
void fun()
{
    //刷新屏幕
    CLS;

    PSTR(2);

    int k, t;
    INPUT_CHECK(scanf("%d", &k), t != 1 || k < 1 || k > 2)

    if (k == 1)
        readmap(); //导入地图
    else
    {
        CLS;
        PSTR(3);
        INPUT_CHECK(scanf("%d%d", &n, &m), t != 2 || n < 3 || m < 3 || n >= MAXN || m >= MAXN)

        //随机地图
        maprand();
    }
}

//y/n选择
int switch_yn(int k)
{
    PSTR(k);
    char c;
    while (c = getchar())
        if (c == 'y' || c == 'Y')
        {
            E_CHECK
            return 1;
        }
        else if (c == 'N' || c == 'n')
        {
            E_CHECK

            switch (k)
            {
            case 0:
                fun();
                break;
            case 1:
                drand();
                break;
            default:
                break;
            }

            return 0;
        }
}