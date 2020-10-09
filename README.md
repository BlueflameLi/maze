# maze
这是我数据结构的作业  
主要内容是迷宫求解的动态显示  
核心为用动态顺序栈实现的dfs  

**注意：由于迷宫的绘制采用的是中文特殊字符，为了方便在windows控制台显示，代码全都以GB2312编码（stack.c和stack.h除外，是UTF-8的）**

## 1.0
采用默认的10*10地图，仅动态显示找出口的过程  

## 2.0
新增地图随机生成，探索方向的顺序随机生成  
暂时不支持用户自定义，地图大小依旧默认10*10  

## 3.0
新增简单的用户交互界面  
新增是否使用默认地图选项  
新增是否使用默认探索顺序选项  
支持用户自定义随机生成的地图大小  
支持用户导入地图文件  

地图文件为map.txt  
格式为两个正整数n和m表示地图的大小  
接下来n行，每行m个正整数为地图  
0表示有路，1表示墙  
入口默认第一列的第二行，出口默认最后一列倒数第二行，请不要设置墙  

## 4.0
新增多路径显示，由于路径可能过多，全部动态显示耗时较长，其余路径均直接打印  
新增显示最短路径，直接打印其长度和路径编号  
由于多路径需要走之前已经走过的路，所以第一条路径更绕路了一点  
优化了显示的方式，改成了局部刷新，防止闪烁  
美化了代码的风格，使代码看上去更简洁一点  

# 5.0
修复了只能走正方形迷宫的bug  
优化了动态显示的第一条路径，不再走走过的路（多路径不受影响）  
新增当前位置的标识  
重构了代码，大大降低了代码的量（同时也降低了代码的可读性。。。），使得代码更简洁  