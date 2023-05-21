//
// Created by chg on 2023/4/25.
//

/**
 * 这个文件提供游戏相关的函数和蛇相关的函数
 * 本文件如果有问题请联系作者
 */
#ifndef SNAKEFORWIN_GAME_H
#define SNAKEFORWIN_GAME_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>//getch()
#include<mmsystem.h>

#pragma comment(lib, "Winmm.lib")

#define ROW 44 //游戏区行数
#define COL 84 //游戏区列数

#define KONG 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define FOOD 2 //标记食物
#define HEAD 3 //标记蛇头
#define BODY 4 //标记蛇身

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define ESC 27 //退出


void menu();//菜单

void optionFunc();//提供选择，打印菜单

void InitConsole();//初始化cmd

void CursorJump(int x, int y);//光标跳转

int RunGame();//运行游戏本体

void PrintBorder();//打印棋盘

void SetColor(int color);//设置颜色，蛇，菜单，边框等

void PrintFood();//打印食物

int judge(int x, int y);//判断后面一个的东西

int ResetDirec(int *direction, int *tem);//如果用户按下了与蛇行进方向相反的方向，则重新设置一下

int gameOver();//游戏结束

void ReGame(int *direction);//重新开始游戏，相当于对游戏在进行一次初始化，放进一个函数，方便调用

void PrintGameOver();

void ResetFace();

void ImportMax(int *getMaxSco);

void ControlMusic(int op);

/*void SelectMode();*/



//关于蛇的
void PrintSnake(int flag);

void InitSnake();

int SnakeMove(int x, int y);

int ControlSnake();

int AutoRun(int direction);

void SelectSkin();
#endif //SNAKEFORWIN_GAME_H
