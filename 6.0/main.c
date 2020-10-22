//this code is GB2312
#include "maze.h"

int main()
{

    switch_yn(0);

    CLS;

    switch_yn(1);

    //¥Ú”°µÿÕº
    CLS;
    prmap();

    dfs(1, 0);

    system("pause");

    return 0;
}