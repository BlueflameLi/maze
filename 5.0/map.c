//this code is GB2312
#include "map.h"

int n = 10, m = 10;

int min_s = 0x3f3f3f3f;

char *dr[8] = {"■", "□", "▓ ", "→", "↓", "←", "↑", "☉"};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int d[4] = {0, 1, 2, 3};

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
    //初始化种子
    srand((unsigned)time(NULL));

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
    //初始化种子
    srand((unsigned)time(NULL));

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
    CLS;

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

    while (x != n - 2 || y != m - 1)
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
    min_s = s < min_s ? min_k = num, s : min_s;
}

//地图更新
void mapupdate(int x, int y, int nx, int ny)
{
    //移动光标到指定位置输出
    gotoxy(y * 2, x);
    prdr(map[x][y]);

    //移动光标到当前位置输出
    gotoxy(ny * 2, nx);
    prdr(7); //7是表示当前所在位置的字符

    //为了美观，让光标在输出完后回到迷宫下方
    gotoxy(0, n);

    //延时
    Sleep(SLEEPTIME);
}