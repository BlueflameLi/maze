//this code is GB2312
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "stack.h"
#define prroad printf("%s", dr[0])  //��ӡ·
#define prwall printf("%s", dr[1])  //��ӡǽ
#define prvroad printf("%s", dr[2]) //��ӡ�Ѿ��߹���·
#define prdr(a) printf("%s", dr[a]) //��ӡ�Թ�
#define MAXN 100 + 10
int n = 10, m = 10;
stack S;
char *dr[7] = {"��", "��", "�� ", "��", "��", "��", "��"};
int dx[4] = {0, 1, 0, -1}; //����Ϊ��������
int dy[4] = {1, 0, -1, 0};
int d[4] = {0, 1, 2, 3}; //���Ʒ����˳��
int map[MAXN][MAXN] = {
    //Ĭ�ϵ�ͼ
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
void maprand() //������ɵ�ͼ
{
    int rd;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
        {
            rd = rand() % 10;           //0-9�����
            map[i][j] = rd < 7 ? 0 : 1; //30%��������ǽ
        }
}
void drand()
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
void prmap() //��ӡ��ͼ
{
    system("cls"); //�����Ļ
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            prdr(map[i][j]);
        printf("\n");
    }
    Sleep(1000); //��ʱ1��
}
int check(int x, int y) //�ж�Խ��
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
    push(&S, p);            //�����ջ
    while (!stackempty(&S)) //ջ�ǿվͻ���·����
    {
        p = gettop(&S);
        if (p.x == n - 2 && p.y == n - 1) //�����յ�
        {
            map[p.x][p.y] = 3;
            return;
        }
        int flag = 1;               //����Ƿ���������
        for (int i = 0; i < 4; i++) //�����ĸ�����
        {
            point next = {p.x + dx[d[i]], p.y + dy[d[i]]};     //������һ���������
            if (check(next.x, next.y) && !map[next.x][next.y]) //ûԽ�磬����û�߹���·
            {
                map[p.x][p.y] = d[i] + 3; //��ǰ·���ָ���ߵķ���ļ�ͷ
                push(&S, next);           //��һ������ջ
                flag = 0;                 //�����·����
                break;
            }
        }
        if (flag) //����ĸ�����û��ͨ
        {
            p = gettop(&S);
            pop(&S);           //��ջ
            map[p.x][p.y] = 2; //��ǰ·����߹���·
        }
        prmap(); //��ӡ��ͼ
    }
}
int main()
{

    // puts("Please input the maze size n and m:");
    // scanf("%d%d", &n, &m);
    initstack(&S);               // ջ��ʼ��
    srand((unsigned)time(NULL)); //��ʼ������
    maprand();                   //�����ͼ
    drand();                     //�������
    dfs(1, 0);
    prmap(10, 10);
    system("pause");
}