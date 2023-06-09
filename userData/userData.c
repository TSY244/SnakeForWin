//
// Created by 12414 on 2023/4/29.
//


#include "userData.h"

#define MAXSIZEID 11
#define MAXSIZEPASSWD 20


//采用类似通讯的协议的方式，目的是减小内存开销
typedef struct UserData {
    int* maxScore;
    char id[MAXSIZEID];
    char passwd[MAXSIZEPASSWD];
    struct UserData *next;
} UserData, *pUDList;

//头指针存放现在的用户
pUDList pUdListHead = NULL;

void CreateNode(pUDList *pUdList) {
    (*pUdList) = (pUDList) malloc(sizeof(UserData));
    (*pUdList)->next = NULL;
    (*pUdList)->maxScore = (int*)malloc(sizeof(int));
    *(*pUdList)->maxScore=0;
    memset((*pUdList)->id, 0, sizeof((*pUdList)->id));
    memset((*pUdList)->passwd, 0, sizeof((*pUdList)->passwd));
}

void GetNowUserDate(pUDList nowUser) {
    strcpy(pUdListHead->id, nowUser->id);
    strcpy(pUdListHead->passwd, nowUser->passwd);
    free(pUdListHead->maxScore);
    pUdListHead->maxScore=nowUser->maxScore;
}


int PrintLoginInterface() {
    /**
     * 打印登录界面
     */
    char ids[20] = {0};
    for (int i = 0; i < 3; ++i) {
        CursorJump(COL - 9, ROW / 2 - 5);
        printf("=== log in ===\n");
        CursorJump(COL - 9, ROW / 2 - 4);
        printf("uer id: ");
        scanf("%s", ids);
        //ip比对
        int returnNum = isHava(ids);
        if (!returnNum) {
            if (i == 2) {
                CursorJump(COL - 9, ROW / 2 - 3);
                printf("You don't have a chance \n");
                Sleep(10);
                system("cls");
                return 0;
            }
            system("cls");
            CursorJump(COL - 9, ROW / 2 - 3);
            printf("input error you, You have %d more chance \n", 2 - i);
        } else {
            //密码检查
            //获得密码，可以写一个函数，然后调用
            char passwd[20] = {0};
            int size = 0;
            char tem;
            CursorJump(COL - 9, ROW / 2 - 3);
            printf("uer passwd:                                         ");
            for (size = 0; size < 21; ++size) {

                tem = getch();
                if ((tem == '\n' && size == 0) || size == 20) {
                    size = 0;
                    system("cls");
                    CursorJump(COL - 9, ROW / 2 - 4);
                    printf("Your password is not valid. ");
                    CursorJump(COL - 9, ROW / 2 - 3);
                    printf("The password should be greater than 0 and less than 20.");
                    CursorJump(COL - 9, ROW / 2 - 2);
                    printf("Please enter again.");
                    while (getch() != '\n') {}
                    break;
                } else if (tem == '\r') {
                    //存入data
                    if (CheckPasswd(ids, passwd)) {
                        system("cls");
                        return 1;
                    } else {
                        CursorJump(COL - 9, ROW / 2 - 2);
                        printf("Your password is error. ");
                        memset(passwd, 0, sizeof(passwd));
                        size = -1;
                        continue;
                    }
                }
                passwd[size] = tem;
            }
        }

    }
}

int isHava(char *ids) {
    UserData *moveNode = pUdListHead;
    while (moveNode != NULL) {
        if (!strcmp(moveNode->id, ids)) {
            return 1;
        }
        moveNode = moveNode->next;
    }
    return 0;
}

void importDate() {
    CreateNode(&pUdListHead);
    free(pUdListHead->maxScore);
    pUdListHead->maxScore=NULL;
    FILE *file = fopen("Data.txt", "rb");
    if (file == NULL) {
        file = fopen("Data.txt", "w+b");
    }
    pUDList moveNode = pUdListHead;
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fclose(file);
        return;
    }
    fseek(file, 0, SEEK_SET);
    int flag = 0;
    while (!feof(file)) {
        pUDList tem = NULL;
        CreateNode(&tem);
        fread(tem->id, sizeof(tem->id), 1, file);
        fread(tem->passwd, sizeof(tem->passwd), 1, file);
        fread(tem->maxScore, sizeof(*tem->maxScore), 1, file);
        if (flag == 0) {
            free(tem);
            tem = NULL;
            flag = 1;
            continue;
        }
        if (!feof(file)) {
            moveNode->next = tem;
            moveNode = moveNode->next;
        } else {
            free(tem);
            tem = NULL;
        }
    }

    fclose(file);
}


void savaData() {
    FILE *file = fopen("Data.txt", "w+b");
    if (file == NULL) {
        exit(-1);
    }
    pUDList moveNode = pUdListHead;
    while (moveNode != NULL) {
        fwrite(moveNode->id, sizeof(moveNode->id), 1, file);
        fwrite(moveNode->passwd, sizeof(moveNode->passwd), 1, file);
        fwrite(moveNode->maxScore, sizeof(*moveNode->maxScore), 1, file);
        moveNode = moveNode->next;
    }
    fclose(file);
}

void ChooseLogOrRegister() {
    BEGIN:
    PrintfMenu();
    int op;
    while (1) {
        int time = 3;
        PrintfMenu();
        scanf("%d", &op);
        system("cls");
        if (op == 1) {
            //注册
            REGISTER:
            CreateUser();
            break;
        } else if (op == 2) {
            //登录
            if (!PrintLoginInterface()) {
                char op;
                CursorJump(COL - 9, ROW / 2 - 5);
                printf("Do you want to register an account?:");
                do {
                    CursorJump(COL - 9, ROW / 2 - 4);
                    printf("input[Y,y]or[N,n]:");
                    getchar();
                    scanf("%c", &op);
                    switch (op) {
                        case 'Y':
                        case 'y':
                            goto REGISTER;
                        case 'N':
                        case 'n':
                            system("cls");
                            goto BEGIN;
                        default:
                            CursorJump(COL - 9, ROW / 2 - 3);
                            printf("input error");
                            break;
                    }
                } while (1);
            } else {
                break;
            }
        } else if (op == 3) {
            exit(0);
        } else {
            CursorJump(COL - 9, ROW / 2 - 1);
            printf("input error");
        }
    }
}

void CreateUser() {
    system("cls");
    UserData *user = (UserData *) malloc(sizeof(UserData));
    user->maxScore=(int*)malloc(sizeof(int));
    *user->maxScore = 0;
    user->next = NULL;
    memset(user->id, 0, sizeof(user->id));
    memset(user->passwd, 0, sizeof(user->passwd));
    int size = 0;
    char tem = '0';
    getchar();

    while (1) {
        inputAgin:
        CursorJump(COL - 9, ROW / 2 - 5);
        printf("please input your ids: ");
        for (size = 0; size < 12; ++size) {
            tem = getchar();
            if ((size == 0 && tem == '\n') || size == 11) {
                isHava:
                size = 0;
                memset(user->id, 0, sizeof(user->id));
                system("cls");
                CursorJump(COL - 9, ROW / 2 - 4);
                printf("Your account is not valid. ");
                CursorJump(COL - 9, ROW / 2 - 3);
                printf("The ID should be greater than 0 and less than 11.");
                CursorJump(COL - 9, ROW / 2 - 2);
                printf("Or the account already exists.");
                CursorJump(COL - 9, ROW / 2 - 1);
                printf("Please enter again.");
                while (getchar() != '\n') {}
                getchar();
                system("cls");
                goto inputAgin;
            } else if (tem == '\n') {
                if (isHava(user->id)) {
                    goto isHava;
                }
                goto passwd;
            }
            user->id[size] = tem;
        }
        passwd:
        system("cls");
        while (1) {
            CursorJump(COL - 9, ROW / 2 - 4);
            printf("Your account is valid.  Your password should be less than 20 characters.");
            CursorJump(COL - 9, ROW / 2 - 3);
            printf("Please enter your password now: ");
            for (size = 0; size < 21; ++size) {
                tem = getch();
                if ((tem == '\r' && size == 0) || size == 20) {
                    size = 0;
                    memset(user->passwd, 0, sizeof(user->passwd));
                    system("cls");
                    CursorJump(COL - 9, ROW / 2 - 4);
                    printf("Your password is not valid. ");
                    CursorJump(COL - 9, ROW / 2 - 3);
                    printf("The password should be greater than 0 and less than 20.");
                    CursorJump(COL - 9, ROW / 2 - 2);
                    printf("Please enter again.");
                    while (getchar() != '\n') {}
                    break;
                } else if (tem == '\r') {
                    //存入data
                    //采取带有头结点的链表的头插法
                    system("cls");
                    UserData *moveNode = pUdListHead->next;
                    pUdListHead->next = user;
                    user->next = moveNode;
                    GetNowUserDate(user);
                    return;
                }
                user->passwd[size] = tem;
            }
        }
    }
}

void DestroyUserList() {
    UserData *moveNode = pUdListHead;
    UserData *deleteNode = NULL;
    while (moveNode != NULL) {
        deleteNode = moveNode;
        moveNode = moveNode->next;
        free(deleteNode);
        deleteNode = NULL;//防止指针悬空
    }
}


int CheckPasswd(char *ids, char *passwd) {
    UserData *moveNode = pUdListHead->next;

    while (moveNode != NULL) {
        if (!strcmp(ids, moveNode->id) && !strcmp(passwd, moveNode->passwd)) {
            GetNowUserDate(moveNode);
            return 1;
        }
        moveNode = moveNode->next;
    }
    return 0;
}

void PrintfMenu() {
    CursorJump(COL - 9, ROW / 2 - 5);
    printf("1.Register\n");
    CursorJump(COL - 9, ROW / 2 - 4);
    printf("2.log in");
    CursorJump(COL - 9, ROW / 2 - 3);
    printf("3.exit");
    CursorJump(COL - 9, ROW / 2 - 2);
    printf("Choose: ");
}

int *GetMaxSoc() {
    return pUdListHead->maxScore;
}

void signalHandler() {
    printf("error");
}


