//this code is GB2312
#ifndef _MAP_H_
#define _MAP_H_

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include <time.h>
#define prdr(a) printf("%s", dr[a]) //��ӡ�Թ�
#define MAXN 100 + 10
#define SLEEPTIME 500
#define WALL_P 3 //����ǽ�ĸ���0-10
#define CLS system("cls")

//·����
int num;

//��ͼ��С
int n, m;

//min_sΪ���·���ȣ�min_kΪ��̵�·���
int min_s, min_k;

//��ʾ�Թ����õ��ַ�
char *dr[8];

//�����ƶ����飬����Ϊ��������
int dx[4];
int dy[4];

//���Ʒ����˳��Ĭ����������
int d[4];

//Ĭ�ϵ�ͼ
int map[MAXN][MAXN];

//����ƶ�
void gotoxy(unsigned char x, unsigned char y);

//�ļ������ͼ
void readmap();

//������ɵ�ͼ
void maprand();

//����˳�����
void drand();

//��ӡ��ͼ
void prmap();

//��ӡ·��
void prpath();

//��ͼ����
void mapupdate(int x, int y, int nx, int ny);

#endif