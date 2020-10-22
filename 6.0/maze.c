//this code is GB2312
#include "maze.h"

//�ж�Խ��
int check(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 0;
    if (x < n - 1 && y < m - 1)
        return 1;

    //�յ�����
    if (x == n - 2 && y == m - 1)
        return 1;

    return 0;
}

//�������Թ�
void dfs(int x, int y)
{
    // ջ��ʼ��
    initstack(&S);
    int num = 0;

    //��������������߹��ķ���
    point s = {x, y, 0};

    push(&S, s); //�����ջ

    while (!stackempty(&S)) //ջ�ǿվͻ���·����
    {
        point *p = gettop(&S);

        //�����յ�
        if (p->x == n - 2 && p->y == m - 1)
        {
            if (!num && !switch_yn(4))
            {
                destroy(&S);
                return;
            }
            prpath(num++);
        }

        //����Ƿ���������
        int flag = 1;

        for (int i = p->z; i < 4; i++) //�����ĸ�����
        {

            //��ǵ�ǰ����
            ++p->z;

            //������һ����
            point next = {p->x + dx[d[i]], p->y + dy[d[i]], 0};

            if (check(next.x, next.y) && !map[next.x][next.y]) //ûԽ���Ҳ���ǽ
            {
                //��ǰ·���ָ���ߵķ���ļ�ͷ
                map[p->x][p->y] = d[i] + 3;

                //���µ�ͼ
                if (!num)
                    mapupdate(p->x, p->y, next.x, next.y);

                //��һ������ջ
                push(&S, next);

                //�����·����
                flag = 0;

                break;
            }
        }

        //����ĸ�����û��ͨ
        if (flag)
        {
            p = gettop(&S);

            //��ջ
            pop(&S);
            //��ǰ·����߹���·����·��ʱ���ù�
            map[p->x][p->y] = num ? 0 : 2;
            //���µ�ͼ
            if (!num && !stackempty(&S))
            {
                point *q = gettop(&S);
                mapupdate(p->x, p->y, q->x, q->y);
            }
        }
    }

    //����ջ
    destroy(&S);

    if (!num)
        puts("No Solution");
    else
    {
        printf("Total %d paths\n", num);
        printf("The shortest path is path %d,The number of steps is %d\n", min_k, min_s);
    }
}