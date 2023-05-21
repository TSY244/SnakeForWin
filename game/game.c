//
// Created by chg on 2023/4/25.
//


#include "game.h"

/*
extern void (*savaData)();
*/


struct snakeHead {
    int x;
    int y;
    int len;
} head;//不能放在.h文件，会重定义

struct snakeBody {
    int x;
    int y;
} body[ROW * COL];


int score = 380;
int *maxScore = NULL;
int face[COL][ROW] = {KONG};//状态变量，该位置属于什么
int runTime = 10;//蛇自动移动的速度，越小越快
int isKill = 0; //判断是否是reGame的
int skinColor = 8; //设置颜色，8是默认的
int isBuffFood; //是不是buff food

//游戏本体相关
void menu() {
    /*
     *  description: 打印菜单
     */
    ControlMusic(3);
    SetColor(10);
    CursorJump(COL - 9, ROW / 2 - 5);
    printf("=== Menu ===\n");
    CursorJump(COL - 9, ROW / 2 - 4);
    printf("0. exit\n");
    CursorJump(COL - 9, ROW / 2 - 3);
    printf("1. play\n");
    CursorJump(COL - 9, ROW / 2 - 2);
    printf("2. rules\n");
    CursorJump(COL - 9, ROW / 2 - 1);
    printf("3. about me\n");
    CursorJump(COL - 9, ROW / 2);
    printf("4. select skin");
    CursorJump(COL - 9, ROW / 2 + 1);
    printf("Enter your choice: ");

}

void optionFunc() {
    /*
     *  description: 用于提供选择界面
     */
    int op;
    do {
        menu();
        CursorJump(COL + 10, ROW / 2 + 1);
        scanf("%d", &op);
        switch (op) {
            case 0: {
                PrintGameOver();
                //退出打印游戏结束
                break;
            }
            case 1: {
                ControlMusic(4);
                ControlMusic(1);
                if (RunGame() == 2) {
                    //代表游戏结束，返回main，保存数据
                    return;
                }
                system("cls");
                ControlMusic(2);
                break;
            }
            case 2: {
                system("cls");
                CursorJump(COL - 29, ROW / 2 - 5);
                printf("You can use up, down, left and right to control your snake.");
                CursorJump(COL - 29, ROW / 2 - 4);
                printf("If you press 'r' this will reset your game. ");
                CursorJump(COL - 29, ROW / 2 - 3);
                printf("If you only use 'space' it will pause your game. ");
                CursorJump(COL - 29, ROW / 2 - 2);
                printf("Now you can use Enter to return to the menu. >:");
                getch();//提供交互，让用户退出
                system("cls");
                break;
            }
            case 3: {
                system("cls");
                CursorJump(COL - 20, ROW / 2 - 5);
                printf("Author: Chen Honggang");
                CursorJump(COL - 20, ROW / 2 - 4);
                printf("School: CUIT");
                CursorJump(COL - 20, ROW / 2 - 3);
                printf("Specialty: Information Security ");
                CursorJump(COL - 20, ROW / 2 - 2);
                printf("QQ numbers: 1231407552. >:");
                getch();
                system("cls");
                break;
            }
            case 4: {
                //皮肤选择
                SelectSkin();
                break;
            }
            default: {
                CursorJump(COL - 9, ROW / 2);
                printf("input error,please input again");
                break;
            }
        }
    } while (op);
}

int RunGame() {
    /*
     *  description: 游戏运行的主体
     *  return: 用于返回菜单
     *  more information: ControlSnake()有返回，当结束时，代表程序将从gameOver 返回 menu;
     */
    score = 0;
    runTime = 10;
    ResetFace();
    PrintBorder();
    PrintFood();
    InitSnake();
    PrintSnake(1);

    if (ControlSnake() == 1) {
        //正常返回
        return 1;
    }
    //代表游戏结束
    return 2;
}

void PrintFood() {
    /*
     *  description: 打印食物，提供两种食物，一个加10分，buff food 加20
     *  more information: 后续考虑添加其他buff food 比如增加声明
     */
    int x;
    int y;
    do {
        x = rand() % COL;
        y = rand() % ROW;
    } while (face[x][y] != KONG);

    face[x][y] = FOOD;
    CursorJump(x * 2, y);

    //判断是否是buff food
    if (x % 8 == 0 || y % 8 == 0) {
        SetColor(3);
        isBuffFood = 1;
        printf("●");
    } else {
        SetColor(4);
        printf("●");
    }
}

void PrintBorder() {
    /*
     *  description: 打印棋盘
     *  more information: noreturn，不会退出该函数
     */
    system("cls");
    SetColor(6);
    CursorJump(0, 0);
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (j == 0 || j == COL - 1) {
                printf("■");
                face[j][i] = WALL;
            } else if (i == 0 || i == ROW - 1) {
                face[j][i] = WALL;
                printf("■");
            } else {
                printf("  ");
                face[j][i] = KONG;
            }
        }
    }
    SetColor(7);
    CursorJump(0, ROW);
    printf("Score:%d", score);
    CursorJump(COL, ROW);
    printf(" The highest score is :%d", *maxScore);
}

void InitConsole() {
    /*
     *  description: 初始化cmd
     */
    system("title chg's snack");//cmd的标题
    system("mode con cols=168 lines=45");//改变控制台的大小

    //设置光标隐藏，主要作用是让游戏界面更美观
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1; //如果不设置则不能成功
    info.bVisible = FALSE;//0
    //如上只是将光标设置，我们需要获取cmd的句柄
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取cmd的句柄
    SetConsoleCursorInfo(handle, &info);

}

void SetColor(int color) {
    /*
     *  description: 设置颜色
     */
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);//将颜色设置成蓝色
}

void CursorJump(int X, int Y) {
    /*
     *  description: 光标跳转
     */
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    //获取句柄
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获得句柄
    SetConsoleCursorPosition(handle, coord);
}

void ReGame(int *direction) {
    /*
     *  description: 重新开始游戏
     *  parameter: 因为重新开始游戏需要我们将方向也要初始化，所以选择传一个指针修改方向
     */
    ControlMusic(1);
    system("cls");
    *direction = RIGHT;
    isKill = 1;
    runTime = 10;
    if (score > *maxScore) {
        *maxScore = score;
    }
    score = 0;
    ResetFace();
    PrintBorder();
    InitSnake();
    PrintSnake(1);
    PrintFood();
}

void PrintGameOver() {
    /*
     *  description: 打印游戏借宿
     */
    system("cls");
    SetColor(10);
    CursorJump(COL - 15, ROW / 2 - 5);
    printf("Quit the game.  ");
    CursorJump(COL - 15, ROW / 2 - 4);
    printf("Welcome to use again, goodbye!  ");
    CursorJump(COL - 15, ROW / 2 - 3);
    printf("Author: Chen Honggang ");
    Sleep(5000);
}

int judge(int x, int y) {
    /*
     * description: 判断蛇行进的方向上下一个方块是什么
     * return：3，代表吃到食物；gameOver(),可以返回1，代表游戏死亡后选择重新开始游戏，2，代表返回菜单；返回0则是KONG，4代表推出以游戏
     */
    char buffer[BUFSIZ] = {0};
    mciSendString("status begin mode", buffer, sizeof(buffer), 0);
    if (strcmp(buffer, "stopped") == 0) {
        // 歌曲播放完毕
        ControlMusic(1);
    }
    if (face[head.x + x][head.y + y] == FOOD) {
        if (score % 60 == 0 && runTime > 1 && score > 0) {
            runTime -= 1;
        }
        head.len++;
        if (isBuffFood == 1) {
            score += 10;
            isBuffFood = 0;
        }
        score += 10;
        CursorJump(0, ROW);
        SetColor(7);
        printf("Score:%d", score);
        PrintFood();
        return 3;
    } else if (face[head.x + x][head.y + y] == WALL
               || face[head.x + x][head.y + y] == BODY) {
        Sleep(100);
        return gameOver();
    }
    return 0;
}

int gameOver() {
    /*
     * description: 游戏结束，打印死后的游戏数据；提供选择，是否继续
     * return：返回1，代表游戏死亡后选择重新开始游戏，2，代表返回菜单，4，代表退出游戏
     */
    ControlMusic(2);
    ControlMusic(5);
    system("cls");
    for (int i = 0; i < 5; ++i) {
        SetColor(1 + i);
        CursorJump(COL - 7, ROW / 2 - 3);
        printf(" You're dead.");
        Sleep(500);
    }
    int op;
    system("cls");
    SetColor(4);
    CursorJump(COL - 15, ROW / 2 - 5);
    printf("Your score is: %d", score);
    CursorJump(COL - 15, ROW / 2 - 4);
    if (score > *maxScore) {
        printf("The highest score is: %d", score);
    } else {
        printf("The highest score is: %d", *maxScore);
    }
    CursorJump(COL - 15, ROW / 2 - 3);
    printf("If you want to play one more game press 'y' ");
    CursorJump(COL - 15, ROW / 2 - 2);
    printf("Return to menu press 'r' ");
    do {
        CursorJump(COL - 15, ROW / 2 - 1);
        printf("To exit, press 'q' >: ");
        while (getchar() != '\n') {}
        op = getchar();
        switch (op) {
            case 'y':
            case 'Y':
                ControlMusic(6);
                return 1;
            case 'q':
            case 'Q':
                ControlMusic(6);
                if (*maxScore < score) {
                    *maxScore = score;
                }
                PrintGameOver();
                return 4;
            case 'r':
            case 'R':
                if (*maxScore < score) {
                    *maxScore = score;
                }
                ControlMusic(6);
                return 2;
            default:
                CursorJump(COL - 15, ROW / 2);
                printf("input error,please input again");
                break;
        }
    } while (1);

}

void ResetFace() {
    /*
     * description: 重置状态矩阵
     */
    for (int i = 0; i < COL; ++i) {
        for (int j = 0; j < ROW; ++j) {
            face[i][j] = KONG;
        }
    }
}


void ImportMax(int *getMaxSco) {
    /*
     * description: 引入store，使用地址直接操作max
     */
    maxScore = getMaxSco;
}

int ResetDirec(int *direction, int *tem) {
    /*
     * description: 如果用户按下了与蛇行进方向相反的方向，则重新设置一下
     */
    if (*direction == LEFT) {
        if (*tem == LEFT || *tem == RIGHT) {
            *direction = *tem;
            return 0;
        }
    } else if (*direction == RIGHT) {
        if (*tem == LEFT || *tem == RIGHT) {
            *direction = *tem;
            return 0;
        }
    } else if (*direction == UP) {
        if (*tem == UP || *tem == DOWN) {
            *direction = *tem;
            return 0;
        }
    } else if (*direction == DOWN) {
        if (*tem == UP || *tem == DOWN) {
            *direction = *tem;
            return 0;
        }
    } else if (*direction != ESC && *direction != 'r'
               && *direction != 'R' && *direction != ' ') {
        *direction = *tem;
        return 0;
    }
    return 1;
}

void ControlMusic(int op) {
    if (op == 1) {
        mciSendString("open ../music/SnakeGameMusic.wav alias begin", 0, 0, 0);
        mciSendString("seek begin to start", 0, 0, 0);
        mciSendString("play begin", 0, 0, 0);
    } else if (op == 2) {
        mciSendString("stop begin", 0, 0, 0);
    } else if (op == 3) {
        mciSendString("open ../music/meun.wav alias menu", 0, 0, 0);
/*
        mciSendString("seek menu to start",0,0,0);
*/
        mciSendString("play menu", 0, 0, 0);
    } else if (op == 4) {
        mciSendString("pause menu ", 0, 0, 0);
    } else if (op == 5) {
        mciSendString("open ../music/fail.wav alias fail", 0, 0, 0);
        mciSendString("seek fail to start", 0, 0, 0);
        mciSendString("play fail", 0, 0, 0);
    } else if (op == 6) {
        mciSendString("pause fail ", 0, 0, 0);
    } else if (op == 7) {
        mciSendString("open ../music/log_in.wav alias login", 0, 0, 0);
        mciSendString("seek login to start", 0, 0, 0);
        mciSendString("play login", 0, 0, 0);
    } else if (op == 8) {
        mciSendString("pause login ", 0, 0, 0);
    }

}


//与蛇相关
void InitSnake() {
    /*
     * description: 初始化蛇，开局带有两个身体
     */
    //初始化蛇头
    head.x = COL / 2;
    head.y = ROW / 2;
    //初始化蛇尾
    //游戏开始有两个身体
    body[0].x = head.x - 1;
    body[0].y = head.y;
    body[1].x = head.x - 2;
    body[1].y = head.y;
    face[head.x][head.y] = HEAD;
    face[body[0].x][body[0].y] = BODY;
    face[body[0].x][body[0].y] = BODY;
    head.len = 2;
}

void PrintSnake(int flag) {
    /*
     * description: 打印蛇将打印上去，覆盖蛇用于覆盖尾巴，实现往前走的样子
     */
    if (flag == 1) { //打印蛇
        CursorJump(2 * head.x, head.y);
        SetColor(skinColor);
        printf("■");
        for (int i = 0; i < head.len; ++i) {
            CursorJump(2 * body[i].x, body[i].y);
            printf("□");
        }
    } else { //覆盖蛇
        if (2 * body[head.len - 1].x != 0 && body[head.len - 1].y != 0) {
            CursorJump(2 * body[head.len - 1].x, body[head.len - 1].y);
            printf("  ");
        }
    }
}

int ControlSnake() {
    /*
     * description: 如果用户按下了与蛇行进方向相反的方向，则重新设置一下
     * return: 返回1代表返回菜单，返回2代表退出游戏
     */
    int direction = RIGHT;
    int tem = direction;
    int ifContinue = 0;

    while (1) {
        int op = AutoRun(direction);
        if (op == 0) {
            goto END;
        } else if (op == 2) {
            goto EXIT;
        }
        direction = getch();
        if (direction == 224 || direction == 13) {
            direction = getch();
        }
        if (isKill != 1) {
            if (ResetDirec(&direction, &tem)) {
                tem = direction;
            }
        }
        isKill = 0;
        switch (direction) {
            case LEFT:
                ifContinue = SnakeMove(-1, 0);
                if (ifContinue == 1) {
                    ReGame(&direction);
                } else if (ifContinue == 2) {
                    goto END;
                } else if (ifContinue == 4) {
                    goto EXIT;
                }
                break;
            case RIGHT:
                ifContinue = SnakeMove(1, 0);
                if (ifContinue == 1) {
                    ReGame(&direction);
                } else if (ifContinue == 2) {
                    goto END;
                } else if (ifContinue == 4) {
                    goto EXIT;
                }
                break;
            case UP:
                ifContinue = SnakeMove(0, -1);
                if (ifContinue == 1) {
                    ReGame(&direction);
                } else if (ifContinue == 2) {
                    goto END;
                } else if (ifContinue == 4) {
                    goto EXIT;
                }
                break;
            case DOWN:
                ifContinue = SnakeMove(0, 1);
                if (ifContinue == 1) {
                    ReGame(&direction);
                } else if (ifContinue == 2) {
                    goto END;
                } else if (ifContinue == 4) {
                    goto EXIT;
                }
                break;
            case 'r':
            case 'R':
                ReGame(&direction);
                tem = direction;
                break;
            case ' ':
                getch();
                break;
            case ESC:
                if (score > *maxScore) {
                    *maxScore = score;
                }
                /*savaData();*/
                PrintGameOver();
                goto EXIT;
        }
    }
    END:
    return 1;
    EXIT:
    return 2;
}

int AutoRun(int direction) {
    /*
     * description: 实现每一格都要自己走，当我们按下按键，抬出这个
     */
    int t = 0;
    int ifContinue;
    while (1) {
        //判断是否有键盘敲击
        if (kbhit()) {
            break;
        }
        if (t == 0) {
            t = runTime;
        }
        if (t--) {
            Sleep(20);
        }
        if (t == 0) {
            switch (direction) {
                case LEFT:
                    ifContinue = SnakeMove(-1, 0);//返回0，是正常进行
                    if (ifContinue == 1) {
                        ReGame(&direction);//在gameOver 界面直接重新开始
                    } else if (ifContinue == 2) {
                        goto END;//返回菜单，相当于结束函数，重新调用
                    } else if (ifContinue == 4) {
                        goto EXIT;
                    }
                    break;
                case RIGHT:
                    ifContinue = SnakeMove(1, 0);
                    if (ifContinue == 1) {
                        ReGame(&direction);
                    } else if (ifContinue == 2) {
                        goto END;
                    } else if (ifContinue == 4) {
                        goto EXIT;
                    }
                    break;
                case UP:
                    ifContinue = SnakeMove(0, -1);
                    if (ifContinue == 1) {
                        ReGame(&direction);
                    } else if (ifContinue == 2) {
                        goto END;
                    } else if (ifContinue == 4) {
                        goto EXIT;
                    }
                    break;
                case DOWN:
                    ifContinue = SnakeMove(0, 1);
                    if (ifContinue == 1) {
                        ReGame(&direction);
                    } else if (ifContinue == 2) {
                        goto END;
                    } else if (ifContinue == 4) {
                        goto EXIT;
                    }
                    break;
            }
        }
    }
    return 1;//正常结束
    END:
    return 0;//返回菜单
    EXIT:
    return 2;//退出游戏
}

int SnakeMove(int x, int y) {
    /*
     * description: 实现每一格都要自己走，当我们按下按键，抬出这个
     * return: 3，代表吃到食物；返回1，代表游戏死亡后选择重新开始游戏;2，代表返回菜单；返回0则是KONG;返回0，代表地移动完成
     */
    int op = judge(x, y);
    if (op == 2) {
        return 2;
    } else if (op == 1) {
        return 1;
    } else if (op == 4) {
        return 4;//表示退出
    }
    PrintSnake(0);//覆盖
    face[body[head.len - 1].x][body[head.len - 1].y] = KONG;
    //采用后循环，因为值会被覆盖
    for (int i = head.len - 1; i > 0; --i) {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }
    body[0].x = head.x;
    body[0].y = head.y;
    face[head.x][head.y] = BODY;
    head.x = head.x + x;
    head.y = head.y + y;
    face[head.x][head.y] = HEAD;
    PrintSnake(1);
    return 0;
}

void SelectSkin() {
    /*
     * description: 提供皮肤选择功能
     */
    system("cls");
    int skinNum = *maxScore / 100 % 8 + 1;
    if (*maxScore >= 700) {
        skinNum = 8;
    }
    int i = 0;
    char op;
    SetColor(10);
    CursorJump(COL - 13, ROW / 2 - 10);
    printf("=== Select Skin ===");
    CursorJump(COL - 13, ROW / 2 - 9);
    printf(" The skin you have. ");
    CursorJump(COL - 13, ROW / 2 - 8 + i);
    SetColor(8 - i);
    printf("%d.■□□□□□□□□□□□□□□", i + 1);
    i++;
    for (; i < skinNum; ++i) {
        CursorJump(COL - 13, ROW / 2 - 8 + i);
        SetColor(8 - i);
        printf("%d.■□□□□□□□□□□□□□□", i + 1);
    }
    CursorJump(COL - 13, ROW / 2 - 8 + i);
    SetColor(10);
    printf(" The skin you don't have ");
    for (; i < 8; ++i) {
        CursorJump(COL - 13, ROW / 2 - 7 + i);
        SetColor(8 - i);
        printf("%d.■□□□□□□□□□□□□□□", i + 1);
    }
    SetColor(10);
    LOOP:
    CursorJump(COL - 13, ROW / 2 - 7 + i);
    printf("input your choose：");
    op = getch();
    if (op - '1' + 1 >= 1 && op - '1' + 1 <= skinNum) {
        skinColor = 8 - (op - '1');
    } else {
        CursorJump(COL - 13, ROW / 2 - 6 + i);
        printf(" You don't have this skin");
        goto LOOP;
    }
    system("cls");
}

/*
void SelectMode() {
    SetColor(10);
    CursorJump(COL - 13, ROW / 2 - 10);
    printf("=== Select Mode ===");
    CursorJump(COL - 13, ROW / 2 - 9);
    printf(" 1. default difficulty ");
    CursorJump(COL - 13, ROW / 2 - 8);
    printf(" 2. easy difficulty ");
    CursorJump(COL - 13, ROW / 2 - 7);
    printf(" 3. difficulty ");

    int n;
    switch (n) {

    }
}
*/

