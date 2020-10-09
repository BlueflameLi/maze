//this code is GB2312
#include "map.h"

int n = 10, m = 10;

int min_s = 0x3f3f3f3f;

char *dr[8] = {"��", "��", "�� ", "��", "��", "��", "��", "��"};

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
    //��ʼ������
    srand((unsigned)time(NULL));

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
    //��ʼ������
    srand((unsigned)time(NULL));

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
    CLS;

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

    while (x != n - 2 || y != m - 1)
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
    min_s = s < min_s ? min_k = num, s : min_s;
}

//��ͼ����
void mapupdate(int x, int y, int nx, int ny)
{
    //�ƶ���굽ָ��λ�����
    gotoxy(y * 2, x);
    prdr(map[x][y]);

    //�ƶ���굽��ǰλ�����
    gotoxy(ny * 2, nx);
    prdr(7); //7�Ǳ�ʾ��ǰ����λ�õ��ַ�

    //Ϊ�����ۣ��ù����������ص��Թ��·�
    gotoxy(0, n);

    //��ʱ
    Sleep(SLEEPTIME);
}