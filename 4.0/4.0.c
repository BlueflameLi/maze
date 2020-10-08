//this code is GB2312
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "stack.h"
#define prdr(a) printf("%s", dr[a]) //��ӡ�Թ�
#define MAXN 100 + 10
#define SLEEPTIME 500
#define WALL_P 3 //����ǽ�ĸ���0-10

stack S;

//·����
int num;

//��ͼ��С
int n = 10, m = 10;

//min_sΪ���·���ȣ�min_kΪ��̵�·���
int min_s = 0x3f3f3f3f, min_k;

//��ʾ�Թ����õ��ַ�
char *dr[7] = {"��", "��", "�� ", "��", "��", "��", "��"};

//�����ƶ����飬����Ϊ��������
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

//���Ʒ����˳��Ĭ����������
int d[4] = {0, 1, 2, 3};

//Ĭ�ϵ�ͼ
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

//����ƶ�
void gotoxy(unsigned char x, unsigned char y)
{
    //COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
    COORD cor;

    //���
    HANDLE hout;

    //�趨����Ҫ��λ��������
    cor.X = x;
    cor.Y = y;

    //GetStdHandle������ȡһ��ָ���ض���׼�豸�ľ����������׼���룬��׼����ͱ�׼����
    //STD_OUTPUT_HANDLE���Ǵ����׼�����Ҳ������ʾ�����ĺ�
    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    //SetConsoleCursorPosition�����������ÿ���̨����λ��
    SetConsoleCursorPosition(hout, cor);
}

//�ļ������ͼ
void readmap()
{
    FILE *fp;

    //��ȡʧ��
    if ((fp = fopen("map.txt", "r")) == NULL)
    {
        puts("Failed to read map");
        Sleep(1000);
        exit(1);
    }

    //��ȡ��ͼ
    fscanf(fp, "%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(fp, "%d", &map[i][j]);

    puts("Import succeeded");
    Sleep(1000);

    fclose(fp);
}

//������ɵ�ͼ
void maprand()
{
    //��Χǽ
    for (int i = 0; i < n; i++)
        map[i][0] = map[i][m - 1] = 1;
    for (int j = 0; j < m; j++)
        map[0][j] = map[n - 1][j] = 1;

    //�����
    map[1][0] = map[n - 2][m - 1] = 0;

    //�Թ��ڲ�����
    int rd;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
        {
            rd = rand() % 10;                //0-9�����
            map[i][j] = rd < WALL_P ? 1 : 0; //Ĭ��30%��������ǽ
        }
}

//����˳�����
void drand()
{
    int rd;

    //�����ɵķ��������
    int k = 0;

    //��������ɵķ���
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

//��ӡ��ͼ
void prmap()
{
    //�����Ļ
    system("cls");

    //��ӡ
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            prdr(map[i][j]);
        printf("\n");
    }

    //��ʱ
    Sleep(SLEEPTIME);
}

//��ӡ·��
void prpath()
{
    //��ʼ����
    int x = 1, y = 0;

    //·������
    int s = 0;

    printf("Path %d: ", ++num);

    while (x != n - 2 || y != n - 1)
    {
        s++;
        printf("(%d,%d) -> ", x, y);

        //pΪ��һ���ķ���
        int p = map[x][y] - 3;

        x += dx[p];
        y += dy[p];
    }

    //��ӡ�յ�
    printf("(%d,%d)\n", x, y);

    //�������·
    if (s < min_s)
    {
        min_s = s;
        min_k = num;
    }
}

//��ͼ����
void mapupdate(int x, int y)
{
    //ֻ�е�һ��·��̬��ʾ
    if (num)
        return;

    //�ƶ���굽ָ��λ�����
    gotoxy(y * 2, x);
    prdr(map[x][y]);

    //Ϊ�����ۣ��ù����������ص��Թ��·�
    gotoxy(0, n);

    //��ʱ
    Sleep(SLEEPTIME);
}

//�ж�Խ��
int check(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 0;
    if (x < n - 1 && y < n - 1)
        return 1;

    //�յ�����
    if (x == n - 2 && y == n - 1)
        return 1;

    return 0;
}

//�������Թ�
void dfs(int x, int y)
{
    // ջ��ʼ��
    initstack(&S);

    //��������������߹��ķ���
    point s = {x, y, {0, 0, 0, 0}};

    push(&S, s); //�����ջ

    while (!stackempty(&S)) //ջ�ǿվͻ���·����
    {
        point *p = gettop(&S);

        //�����յ�
        if (p->x == n - 2 && p->y == n - 1)
        {
            map[p->x][p->y] = 3;
            mapupdate(p->x, p->y);
            prpath();
        }

        //����Ƿ���������
        int flag = 1;

        for (int i = 0; i < 4; i++) //�����ĸ�����
        {
            //�����Ѿ��߹��ķ���
            if (p->z[i])
                continue;

            //��ǵ�ǰ����
            p->z[i] = 1;

            //������һ����
            point next = {p->x + dx[d[i]], p->y + dy[d[i]], {0, 0, 0, 0}};

            if (check(next.x, next.y) && (map[next.x][next.y] == 0 || map[next.x][next.y] == 2)) //ûԽ���Ҳ���ǽ
            {
                //��ǰ·���ָ���ߵķ���ļ�ͷ
                map[p->x][p->y] = d[i] + 3;

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

            //��ǰ·����߹���·
            map[p->x][p->y] = 2;
        }

        //���µ�ͼ
        mapupdate(p->x, p->y);
    }

    //����ջ
    desroy(&S);
}
int main()
{
    //��ʼ������
    srand((unsigned)time(NULL));

    puts("Do you want to use the default map? [y/n] ");

    //��ջ�����
    fflush(stdin);

    char c;
    while (c = getchar())
    {
        if (c == 'y' || c == 'Y')
        {
            //�����س���ȷ��
            while (c = getchar() != '\n')
                ;
            break;
        }
        else if (c == 'N' || c == 'n')
        {
            //�����س���ȷ��
            while (c = getchar() != '\n')
                ;

            //ˢ����Ļ
            system("cls");

            puts("Please choose to generate map randomly or import map");
            puts("[1] import map");
            puts("[2] Randomly generated map");

            int k, t;
            while ((t = scanf("%d", &k)) != EOF)
                if (t != 1 || k < 1 || k > 2) //�Ƿ����봦��
                {
                    puts("Please re-enter");

                    //ˢ�»�����
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
                    if (t != 2 || n < 3 || m < 3) //�Ƿ����봦��
                    {
                        puts("Please re-enter n and m:");

                        fflush(stdin);
                    }
                    else
                        break;
                }

                //�����ͼ
                maprand();

                break;
            }
        }
    }

    system("cls");

    puts("Do you want to use the default direction order? ("
         "��"
         ", "
         "��"
         ", "
         "��"
         ", "
         "��"
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

            //�������˳��
            drand();
            break;
        }
    }

    //��ӡ��ͼ
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