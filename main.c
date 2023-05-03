

/**
 * @author chg
 * @version 0.0.1
 */

#include <time.h>
#include "game/game.h"
#include "userData/userData.h"
void setRandomNum();

int main(){
    //导入最大值
    importMax();
    setRandomNum();
/*    PrintLoginInterface();*/
    //初始化cmd
    initConsole();
    //游戏选择
    optionFunc();
    return 0;
}

void setRandomNum(){
    srand((unsigned int)time(NULL));
}