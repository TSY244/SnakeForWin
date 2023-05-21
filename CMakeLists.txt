cmake_minimum_required(VERSION 3.25)
project(SnakeForWin C)

set(CMAKE_C_STANDARD 11)

add_executable(SnakeForWin main.c game/game.c game/game.h userData/userData.c userData/userData.h getInforFormInt/Intnet.c getInforFormInt/Intnet.h)

target_link_libraries(SnakeForWin winmm)
add_executable(game game/game.c)