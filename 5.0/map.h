//this code is GB2312
#ifndef _MAP_H_
#define _MAP_H_

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include <time.h>
#define prdr(a) printf("%s", dr[a]) //打印迷宫
#define MAXN 100 + 10
#define SLEEPTIME 500
#define WALL_P 3 //生成墙的概率0-10
#define CLS system("cls")

//路径数
int num;

//地图大小
int n, m;

//min_s为最短路长度，min_k为最短的路序号
int min_s, min_k;

//显示迷宫所用的字符
char *dr[8];

//坐标移动数组，依次为左下右上
int dx[4];
int dy[4];

//控制方向的顺序，默认左下右上
int d[4];

//默认地图
int map[MAXN][MAXN];

//光标移动
void gotoxy(unsigned char x, unsigned char y);

//文件导入地图
void readmap();

//随机生成地图
void maprand();

//方向顺序随机
void drand();

//打印地图
void prmap();

//打印路径
void prpath();

//地图更新
void mapupdate(int x, int y, int nx, int ny);

#endif