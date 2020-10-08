//this code is GB2312
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stack.h"
#define prroad printf("%s", dr[0])  //打印路
#define prwall printf("%s", dr[1])  //打印墙
#define prvroad printf("%s", dr[2]) //打印已经走过的路
#define prdr(a) printf("%s", dr[a]) //打印迷宫
#define MAXN 100 + 10
int n = 10, m = 10;
stack S;
char *dr[7] = {"■", "□", "▓ ", "→", "↓", "←", "↑"};
int dx[4] = {0, 1, 0, -1}; //依次为左下右上
int dy[4] = {1, 0, -1, 0};
int map[MAXN][MAXN] = {
    //默认地图
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void prmap() //打印地图
{
    system("cls"); //清空屏幕
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            prdr(map[i][j]);
        printf("\n");
    }
    Sleep(1000); //延时1秒
}
int check(int x, int y) //判断越界
{
    if (x <= 0 || y <= 0)
        return 0;
    if (x < n - 1 && y < n - 1)
        return 1;
    if (x == n - 2 && y == n - 1)
        return 1;
    return 0;
}
void dfs(int x, int y)
{
    point p = {x, y};
    push(&S, p);            //起点入栈
    while (!stackempty(&S)) //栈非空就还有路可走
    {
        p = gettop(&S);
        if (p.x == n - 2 && p.y == n - 1) //到达终点
        {
            map[p.x][p.y] = 3;
            return;
        }
        int flag = 1;               //标记是否能往下走
        for (int i = 0; i < 4; i++) //遍历四个方向
        {
            point next = {p.x + dx[i], p.y + dy[i]};           //计算下一个点的坐标
            if (check(next.x, next.y) && !map[next.x][next.y]) //没越界，且是没走过的路
            {
                map[p.x][p.y] = i + 3; //当前路变成指向走的方向的箭头
                push(&S, next);        //下一个点入栈
                flag = 0;              //标记有路可走
                break;
            }
        }
        if (flag) //如果四个方向都没走通
        {
            p = gettop(&S);
            pop(&S);           //出栈
            map[p.x][p.y] = 2; //当前路变成走过的路
        }
        prmap(); //打印地图
    }
}
int main()
{

    // puts("Please input the maze size n and m:");
    // scanf("%d%d", &n, &m);

    initstack(&S); //栈初始化
    dfs(1, 0);
    prmap(10, 10);
    system("pause");
}