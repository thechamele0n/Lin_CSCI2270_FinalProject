#include <iostream>
#include "Functions.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    Functions f;

    std::cout << "Hello warrior! Welcome to a game I just made." << std::endl;
    std::cout << "Just so you know, your character doesn't sleep." << std::endl;
    std::cout << "Unless you die, then he/she sleeps forever." << std::endl;
    std::cout << std::endl;

    while(f.stat.gamemode != 4){
        std::string game[4] = {"Enter the Dungeon","Go to Town","Character","Quit"};
        std::cout << "What would you like to do?" << std::endl;
        f.stat.gamemode = f.menu(game, 4);
        if(f.stat.gamemode == 1) f.dungeon();
        else if(f.stat.gamemode == 2) f.town();
        else if(f.stat.gamemode == 3) f.character();
    }
    return 0;
}
