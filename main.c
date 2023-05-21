

/**
 * @author chg
 * @version 0.0.1
 */

#include <time.h>
#include "game/game.h"
#include "userData/userData.h"
void setRandomNum();

int main(){
    ControlMusic(7);
    importDate();
    //导入最大值
    setRandomNum();
    //初始化cmd
    initConsole();

    ChooseLogOrRegister();
    importMax(GetMaxSoc());
    //游戏选择
    ControlMusic(8);
    optionFunc();
    savaData();
    DestroyUserList();
    return 0;
}

void setRandomNum(){
    srand((unsigned int)time(NULL));
}