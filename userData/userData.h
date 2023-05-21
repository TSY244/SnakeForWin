//
// Created by chg on 2023/4/29.
//

/**
 * 本文件用存放数据的信息可考虑实现联网导入信息的功能
 */


#ifndef SNAKEFORWIN_USERDATA_H
#define SNAKEFORWIN_USERDATA_H

#include "../game/game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int PrintLoginInterface();

int isHava(char *ids);

void importDate();

void savaData();

void ChooseLogOrRegister();

void CreateUser();

void DestroyUserList();

int CheckPasswd(char *ids,char *passwd);

void PrintfMenu();

void GetNowUserDate();

int * GetMaxSoc();

void signalHandler();
#endif //SNAKEFORWIN_USERDATA_H
