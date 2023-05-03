//
// Created by 12414 on 2023/4/29.
//

#include "userData.h"
void PrintLoginInterface() {
    char* ids;
    CursorJump(COL - 9, ROW / 2 - 5);
    printf("=== log in ===\n");
    CursorJump(COL - 9, ROW / 2 - 4);
    printf("uer id: \n");
    scanf("%s",ids);
}
