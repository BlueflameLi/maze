//this code is GB2312
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "stack.h"
#define prdr(a) printf("%s", dr[a]) //打印迷宫
#define MAXN 100 + 10
#define SLEEPTIME 500
#define WALL_P 3 //生成墙的概率0-10

stack S;

//路径数
int num;

//地图大小
int n = 10, m = 10;

//min_s为最短路长度，min_k为最短的路序号
int min_s = 0x3f3f3f3f, min_k;

//显示迷宫所用的字符
char *dr[7] = {"■", "□", "▓ ", "→", "↓", "←", "↑"};

//坐标移动数组，依次为左下右上
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

//控制方向的顺序，默认左下右上
int d[4] = {0, 1, 2, 3};

//默认地图
int map[MAXN][MAXN] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

//光标移动
void gotoxy(unsigned char x, unsigned char y)
{
    //COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
    COORD cor;

    //句柄
    HANDLE hout;

    //设定我们要定位到的坐标
    cor.X = x;
    cor.Y = y;

    //GetStdHandle函数获取一个指向特定标准设备的句柄，包括标准输入，标准输出和标准错误。
    //STD_OUTPUT_HANDLE正是代表标准输出（也就是显示屏）的宏
    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    //SetConsoleCursorPosition函数用于设置控制台光标的位置
    SetConsoleCursorPosition(hout, cor);
}

//文件导入地图
void readmap()
{
    FILE *fp;

    //读取失败
    if ((fp = fopen("map.txt", "r")) == NULL)
    {
        puts("Failed to read map");
        Sleep(1000);
        exit(1);
    }

    //读取地图
    fscanf(fp, "%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(fp, "%d", &map[i][j]);

    puts("Import succeeded");
    Sleep(1000);

    fclose(fp);
}

//随机生成地图
void maprand()
{
    //外围墙
    for (int i = 0; i < n; i++)
        map[i][0] = map[i][m - 1] = 1;
    for (int j = 0; j < m; j++)
        map[0][j] = map[n - 1][j] = 1;

    //出入口
    map[1][0] = map[n - 2][m - 1] = 0;

    //迷宫内部生成
    int rd;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
        {
            rd = rand() % 10;                //0-9随机数
            map[i][j] = rd < WALL_P ? 1 : 0; //默认30%概率生成墙
        }
}

//方向顺序随机
void drand()
{
    int rd;

    //已生成的方向的数量
    int k = 0;

    //标记已生成的方向
    int v[4] = {0, 0, 0, 0};

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

//打印地图
void prmap()
{
    //清空屏幕
    system("cls");

    //打印
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            prdr(map[i][j]);
        printf("\n");
    }

    //延时
    Sleep(SLEEPTIME);
}

//打印路径
void prpath()
{
    //初始坐标
    int x = 1, y = 0;

    //路径长度
    int s = 0;

    printf("Path %d: ", ++num);

    while (x != n - 2 || y != n - 1)
    {
        s++;
        printf("(%d,%d) -> ", x, y);

        //p为下一步的方向
        int p = map[x][y] - 3;

        x += dx[p];
        y += dy[p];
    }

    //打印终点
    printf("(%d,%d)\n", x, y);

    //更新最短路
    if (s < min_s)
    {
        min_s = s;
        min_k = num;
    }
}

//地图更新
void mapupdate(int x, int y)
{
    //只有第一条路动态显示
    if (num)
        return;

    //移动光标到指定位置输出
    gotoxy(y * 2, x);
    prdr(map[x][y]);

    //为了美观，让光标在输出完后回到迷宫下方
    gotoxy(0, n);

    //延时
    Sleep(SLEEPTIME);
}

//判断越界
int check(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 0;
    if (x < n - 1 && y < n - 1)
        return 1;

    //终点特判
    if (x == n - 2 && y == n - 1)
        return 1;

    return 0;
}

//核心走迷宫
void dfs(int x, int y)
{
    // 栈初始化
    initstack(&S);

    //第三个参数标记走过的方向
    point s = {x, y, {0, 0, 0, 0}};

    push(&S, s); //起点入栈

    while (!stackempty(&S)) //栈非空就还有路可走
    {
        point *p = gettop(&S);

        //到达终点
        if (p->x == n - 2 && p->y == n - 1)
        {
            map[p->x][p->y] = 3;
            mapupdate(p->x, p->y);
            prpath();
        }

        //标记是否能往下走
        int flag = 1;

        for (int i = 0; i < 4; i++) //遍历四个方向
        {
            //跳过已经走过的方向
            if (p->z[i])
                continue;

            //标记当前方向
            p->z[i] = 1;

            //计算下一坐标
            point next = {p->x + dx[d[i]], p->y + dy[d[i]], {0, 0, 0, 0}};

            if (check(next.x, next.y) && (map[next.x][next.y] == 0 || map[next.x][next.y] == 2)) //没越界且不是墙
            {
                //当前路变成指向走的方向的箭头
                map[p->x][p->y] = d[i] + 3;

                //下一个点入栈
                push(&S, next);

                //标记有路可走
                flag = 0;

                break;
            }
        }

        //如果四个方向都没走通
        if (flag)
        {
            p = gettop(&S);

            //出栈
            pop(&S);

            //当前路变成走过的路
            map[p->x][p->y] = 2;
        }

        //更新地图
        mapupdate(p->x, p->y);
    }

    //销毁栈
    desroy(&S);
}
int main()
{
    //初始化种子
    srand((unsigned)time(NULL));

    puts("Do you want to use the default map? [y/n] ");

    //清空缓存区
    fflush(stdin);

    char c;
    while (c = getchar())
    {
        if (c == 'y' || c == 'Y')
        {
            //读到回车键确认
            while (c = getchar() != '\n')
                ;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            //读到回车键确认
            while (c = getchar() != '\n')
                ;

            //刷新屏幕
            system("cls");

            puts("Please choose to generate map randomly or import map");
            puts("[1] import map");
            puts("[2] Randomly generated map");

            int k, t;
            while ((t = scanf("%d", &k)) != EOF)
                if (t != 1 || k < 1 || k > 2) //非法输入处理
                {
                    puts("Please re-enter");

                    //刷新缓存区
                    fflush(stdin);
                }
                else
                    break;

            if (k == 1)
            {
                readmap();
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

                //随机地图
                maprand();

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
            while (c = getchar() != '\n')
                ;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            while (c = getchar() != '\n')
                ;

            //随机方向顺序
            drand();
            break;
        }
    }

    //打印地图
    prmap();

    dfs(1, 0);

    if (!num)
        puts("No Solution");
    else
    {
        printf("Total %d paths\n", num);
        printf("The shortest path is path %d,The number of steps is %d\n", min_k, min_s);
    }

    system("pause");

    return 0;
}