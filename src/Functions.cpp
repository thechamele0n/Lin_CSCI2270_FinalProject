#include "Functions.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

Functions::Functions()
{
    player = gameData("player", 25, 5, 1, 0, 0, 0);
    slime = gameData("Slime", 10, 1, 1, 0, 1, 0);
    zombie = gameData("zombie", 20, 5, 1, 0, 5, 0);
    skele = gameData("Skeleton", 30, 10, 2, 0, 10, 0);
    human = gameData("Exiled Human", 40, 15, 3, 0, 15, 0);
    demon = gameData("Demon", 70, 30, 4, 0, 30, 0);
    dragon = gameData("Dragon", 150, 50, 7, 0, 50, 0);
    stat = gameStats(5, 3, 0, 5, 3);

    //ctor
}

Functions::~Functions()
{
    //dtor
}

int Functions::diceRoll(int n){
    int roll = 0;
    for(int i = 0; i < n; ++i){
        srand(time(NULL));
        roll = roll + rand() % 6;
    }
    return roll;
}

int Functions::menu(std::string items[], int length){
    int choice;
    for(int i = 0; i < length; ++i){
        std::cout << i+1 << ":" << items[i] << std::endl;
    }
    std::cout << ">>";
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

gameData Functions::randMonster(){
    srand(time(NULL));
    int rm = rand() % 100 + 1;
    if(rm <= 30) return slime;
    else if(30 < rm && rm <= 53) return zombie;
    else if(53 < rm && rm <= 70) return skele;
    else if(70 < rm && rm <= 85) return human;
    else if(85 < rm && rm <= 95) return demon;
    else return dragon;
}

void Functions::buyWeapon(){
    std::cout << "You have " << player.gold << " gold." << std::endl;
    std::cout << "The cost to upgrade your weapon is: " << stat.weaponcost << std::endl;
    if(player.gold < stat.weaponcost){
        std::cout << "You do not have enough gold." << std::endl;
        return;
    }
    std::cout << "Do you still want to upgrade?" << std::endl;
    std::string b[2] = {"yes","no"};
    int choice = menu(b, 2);
    if(choice == 1){
        player.attack++;
        player.gold = player.gold - stat.weaponcost;
        stat.weaponcost = stat.weaponcost * 2;
    }
}

void Functions::buyArmor(){
    std::cout << "You have " << player.gold << " gold." << std::endl;
    std::cout << "The cost to upgrade your armor is: " << stat.armorcost << std::endl;
    if(player.gold < stat.armorcost){
        std::cout << "You do not have enough gold." << std::endl;
        return;
    }
    std::cout << "Do you still want to upgrade?" << std::endl;
    std::string b[2] = {"yes","no"};
    int choice = menu(b, 2);
    if(choice == 1){
        player.armor++;
        player.gold = player.gold - stat.armorcost;
        stat.armorcost = stat.armorcost++;
    }
}

gameData Functions::copyMonster(gameData monster){
    gameData tempMonst = monster;
    return tempMonst;
}

void Functions::experience(gameData monster){
    player.experience = player.experience + monster.experience;
    if(player.experience >= stat.levelxp){
        player.experience = std::abs(player.experience - stat.levelxp);
        stat.levelxp = stat.levelxp * 2;
        player.level++;
        player.health = 25 + (5 * player.level);
        std::cout << "Congratulations! You have Leveled up!" << std::endl;
        std::cout << "You are healed to full health and you gain 5 hp!" << std::endl;
        std::cout << "You are now level: " << player.level << std::endl;
    }
}

int Functions::fightMonster(gameData monster){
    gameData mstr = copyMonster(monster);
    std::string d[2] = {"Attack","Run"};
    std::cout << "You have encountered a: " << mstr.name << std::endl;
    std::cout << "Attack: " << mstr.attack << " Health: " << mstr.health << std::endl;
    std::cout << std::endl;
    while(mstr.health > 0 && player.health > 0){
        std::cout << "You have " << player.health << " Health." << std::endl;
        std::cout << "The " << mstr.name << " has " << mstr.health << std::endl;
        std::cout << std::endl;
        std::cout << "What do you want to do?" << std::endl;
        int choice = menu(d, 2);
        if(choice == 1){
            int damage = diceRoll(player.attack);
            std::cout << "You did " << damage << " damage to the " << mstr.name << std::endl;
            mstr.health = mstr.health - damage;

            damage = diceRoll(mstr.attack) - player.armor;
            if(damage < 0) damage = 0;
            std::cout << "The " << mstr.name << " did " << damage << " damage to you." << std::endl;
            player.health = player.health - damage;
        }
        else if(choice == 2){
            if(diceRoll(1) <= 3){
                std::cout << "You've escaped!" << std::endl;
                return 0;
            }
            else{
                std::cout << "You did not escape." << std::endl;
                int damage = diceRoll(mstr.attack) - player.armor;
                if(damage < 0) damage = 0;
                std::cout << "The " << mstr.name << " did " << damage << " damage to you." << std::endl;
                player.health = player.health - damage;
            }
        }
    }
    if(mstr.health <= 0){
        std::cout << "You've beaten the " << mstr.name << ", and you got " << mstr.gold << " gold, and " << mstr.experience << " experience!" << std::endl;
        player.gold = player.gold + mstr.gold;
        experience(mstr);
        std::cout << std::endl;
        return 0;
    }
    else if(player.health <= 0){
        std::cout << "You have died!" << std::endl;
        std::cout << "Your journey ends here." << std::endl;
        stat.gamemode = 4;
        return 3;
    }
}

int Functions::dungeon(){
    int choice = 0;
    std::string c[3] = {"Explore Dungeon","Check character","Leave Dungeon"};
    std::cout << "You have entered the dungeon." << std::endl;
    std::cout << "What do you want to do?" << std::endl;
    while(choice != 3){
        choice = menu(c, 3);
        if(choice == 1) choice = fightMonster(randMonster());
        else if(choice == 2) character();
    }
}

int Functions::town(){
    int tngame = 0;
    std::string tn[4] = {"Check Shop","See the Healer","Check Character","Leave Town"};
    while(tngame != 4){
        std::cout << "Where do you want go?" << std::endl;
        tngame = menu(tn, 4);
        while(tngame == 1){
            std::string a[3] = {"upgrade your weapon", "upgrade your armor","leave shop"};
            std::cout << "What would you like to do?" << std::endl;
            int choice = menu(a, 3);
            if(choice == 1) buyWeapon();
            else if(choice == 2) buyArmor();
            else tngame = 0;
        }
        if(tngame == 2){
            std::string b[2] = {"yes","no"};
            std::cout << "It will cost 5 gold." << std::endl;
            std::cout << "Do you still want to heal?" <<std::endl;
            int healchoice = menu(b, 2);
            if(player.gold < stat.healprice){
                std::cout << "Sorry, you don't have enough gold." << std::endl;
                tngame = 0;
                break;
            }
            if(healchoice == 1){
                player.health = 25 + (5*player.level);
                std::cout << "You have been healed to full health." << std::endl;
                player.gold = player.gold - stat.healprice;
            }
        }
        if(tngame == 3){
            character();
        }
    }
}

int Functions::character(){
    std::cout << "Your health is at: " << player.health << std::endl;
    std::cout << "You have " << player.gold << " coins." << std::endl;
    std::cout << "Your attacks roll " << player.attack << " die(s)." << std::endl;
    std::cout << "The damage your armor blocks is: " << player.armor << std::endl;
    std::cout << "Your level is " << player.level << " and you have " << player.experience << " experience" << std::endl;
    std::cout << stat.levelxp << " experience is needed for the next level." << std::endl;
    std::cout << std::endl;
}
