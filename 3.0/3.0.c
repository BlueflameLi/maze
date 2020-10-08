//this code is GB2312
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
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
int d[4] = {0, 1, 2, 3}; //控制方向的顺序
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
void readmap() //文件导入地图
{
    FILE *fp;
    if ((fp = fopen("map.txt", "r")) == NULL) //读取失败
    {
        puts("Failed to read map");
        Sleep(1000);
        exit(1);
    }
    fscanf(fp, "%d%d", &n, &m);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(fp, "%d", &map[i][j]);
    fclose(fp);
    puts("Import succeeded");
}
void maprand() //随机生成地图
{
    for (int i = 0; i < n; i++)
        map[i][0] = map[i][m - 1] = 1;
    for (int j = 0; j < m; j++)
        map[0][j] = map[n - 1][j] = 1;
    map[1][0] = map[n - 2][m - 1] = 0;

    int rd;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
        {
            rd = rand() % 10;           //0-9随机数
            map[i][j] = rd < 7 ? 0 : 1; //30%概率生成墙
        }
}
void drand() //方向顺序随机
{
    int rd;
    int v[4] = {0, 0, 0, 0};
    int k = 0;
    while (k < 4)
    {
        rd = rand() % 4;
        if (!v[rd])
        {
            v[rd] = 1;
            d[k++] = rd;
        }
    }
}
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
void init()
{
    initstack(&S);               // 栈初始化
    srand((unsigned)time(NULL)); //初始化种子
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
            point next = {p.x + dx[d[i]], p.y + dy[d[i]]};     //计算下一个点的坐标
            if (check(next.x, next.y) && !map[next.x][next.y]) //没越界，且是没走过的路
            {
                map[p.x][p.y] = d[i] + 3; //当前路变成指向走的方向的箭头
                push(&S, next);           //下一个点入栈
                flag = 0;                 //标记有路可走
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
    init();

    puts("Do you want to use the default map? [y/n] ");

    char c;
    fflush(stdin); //清空缓存区
    while (c = getchar())
    {
        if (c == 'y' || c == 'Y')
        {
            while (c = getchar() != '\n') //读到回车键确认
                ;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            while (c = getchar() != '\n') //读到回车键确认
                ;

            system("cls"); //刷新屏幕
            puts("Please choose to generate map randomly or import map");
            puts("[1] import map");
            puts("[2] Randomly generated map");

            int k, t;
            while ((t = scanf("%d", &k)) != EOF)
                if (t != 1 || k < 1 || k > 2) //非法输入处理
                {
                    puts("Please re-enter");
                    fflush(stdin); //刷新缓存区
                }
                else
                    break;

            if (k == 1)
            {
                readmap();
                puts("Please press enter to continue");
                fflush(stdin);
                while (c = getchar() != '\n')
                    ;
                break;
            }
            else
            {
                system("cls");
                puts("Please input the maze size n and m:");
                while ((t = scanf("%d%d", &n, &m)) != EOF)
                {
                    if (t != 2 || n < 3 || m < 3) //非法输入处理
                    {
                        puts("Please re-enter n and m:");
                        fflush(stdin);
                    }
                    else
                        break;
                }
                maprand(); //随机地图
                break;
            }
        }
    }
    system("cls");
    puts("Do you want to use the default direction order? ("
         "→"
         ", "
         "↓"
         ", "
         "←"
         ", "
         "↑"
         ") [y/n] ");
    fflush(stdin);
    while (c = getchar())
    {
        if (c == 'y' || c == 'Y')
        {
            while (c = getchar() != '\n') //回车键确认
                ;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            while (c = getchar() != '\n')
                ;
            drand(); //随机方向顺序
            puts("Please press enter to continue");
            while (c = getchar() != '\n')
                ;
            break;
        }
    }

    dfs(1, 0);
    prmap();
    system("pause");
}