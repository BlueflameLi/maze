//this code is GB2312
#include "maze.h"

//判断越界
int check(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 0;
    if (x < n - 1 && y < m - 1)
        return 1;

    //终点特判
    if (x == n - 2 && y == m - 1)
        return 1;

    return 0;
}

//核心走迷宫
void dfs(int x, int y)
{
    // 栈初始化
    initstack(&S);
    int num = 0;

    //第三个参数标记走过的方向
    point s = {x, y, 0};

    push(&S, s); //起点入栈

    while (!stackempty(&S)) //栈非空就还有路可走
    {
        point *p = gettop(&S);

        //到达终点
        if (p->x == n - 2 && p->y == m - 1)
        {
            if (!num && !switch_yn(4))
            {
                destroy(&S);
                return;
            }
            prpath(num++);
        }

        //标记是否能往下走
        int flag = 1;

        for (int i = p->z; i < 4; i++) //遍历四个方向
        {

            //标记当前方向
            ++p->z;

            //计算下一坐标
            point next = {p->x + dx[d[i]], p->y + dy[d[i]], 0};

            if (check(next.x, next.y) && !map[next.x][next.y]) //没越界且不是墙
            {
                //当前路变成指向走的方向的箭头
                map[p->x][p->y] = d[i] + 3;

                //更新地图
                if (!num)
                    mapupdate(p->x, p->y, next.x, next.y);

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
            //当前路变成走过的路，多路径时不用管
            map[p->x][p->y] = num ? 0 : 2;
            //更新地图
            if (!num && !stackempty(&S))
            {
                point *q = gettop(&S);
                mapupdate(p->x, p->y, q->x, q->y);
            }
        }
    }

    //销毁栈
    destroy(&S);

    if (!num)
        puts("No Solution");
    else
    {
        printf("Total %d paths\n", num);
        printf("The shortest path is path %d,The number of steps is %d\n", min_k, min_s);
    }
}