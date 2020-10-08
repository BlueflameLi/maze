#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#define INITSIZE 100 //储存空间的初始分配量
//typedef int ElemType;
typedef struct
{
    int x, y;
}point;
typedef point ElemType;
typedef struct
{
    ElemType *base; //存放元素的动态数组空间
    int top;        //栈顶指针
    int stacksize;  //当前栈空间的大小
} stack;

void initstack(stack *S);
int stacklength(stack *S);
ElemType gettop(stack *S);
int push(stack *S, ElemType x);
int pop(stack *S);
int stackempty(stack *S);
void list(stack *S);
void clear(stack *S);
void desroy(stack *S);
#endif