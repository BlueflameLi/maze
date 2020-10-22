//this code is GB2312
#ifndef _MAZE_H_
#define _MAZE_H_

#include"stack.h"
#include"map.h"
#include "fun.h"

stack S;

//判断越界
int check(int x, int y);

//核心走迷宫
void dfs(int x, int y);


#endif