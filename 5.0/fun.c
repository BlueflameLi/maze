#include "fun.h"
#include "map.h"

char *str[4] = {"Do you want to use the default map ? [y / n] ",
                "Do you want to use the default direction order? [y/n] ",
                "Please choose to generate map randomly or import map\n"
                "[1] import map\n"
                "[2] Randomly generated map",
                "Please input the maze size n and m:"};

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
        INPUT_CHECK(scanf("%d%d", &n, &m), t != 2 || n < 3 || m < 3)

        //随机地图
        maprand();
    }
}

//y/n选择
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