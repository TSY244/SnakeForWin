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

void initConsole();//初始化cmd

void CursorJump(int x, int y);//光标跳转

int runGame();//运行游戏本体

void printBorder();//打印期盼

void setColor(int color);//设置颜色，蛇，菜单，边框等

void printFood();//打印食物

int judge(int x, int y);//判断后面一个的东西

int resetDirec(int *direction, int *tem);//如果用户按下了与蛇行进方向相反的方向，则重新设置一下

int gameOver();//游戏借宿

void reGame(int *direction);//重新开始游戏，相当于对游戏在进行一次初始化，放进一个函数，方便调用

void printGameOver();

void resetFace();

void storeMax();

void importMax();

void ControlMusic();
//关于蛇的
void printSnake(int flag);

void InitSnake();

int snakeMove(int x, int y);

void controlSnake();

int autoRun(int direction);

void selectSkin();
#endif //SNAKEFORWIN_GAME_H
