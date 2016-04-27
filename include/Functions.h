#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>

struct gameData{
    std::string name;
    int health;
    int gold;
    int attack;
    int armor;
    int experience;
    int level;

    gameData(){

    };

    gameData(std::string nom, int hp, int gp, int att, int ar, int ex, int lvl){
        name = nom;
        health = hp;
        gold = gp;
        attack = att;
        armor = ar;
        experience = ex;
        level = lvl;
    }

    ~gameData(){

    }

};

struct gameStats{
    int weaponcost;
    int armorcost;
    int gamemode;
    int levelxp;
    int healprice;

    gameStats(){

    };

    gameStats(int wpc, int arc, int gm, int lxp, int healp){
        weaponcost = wpc;
        armorcost = arc;
        gamemode = gm;
        levelxp = lxp;
        healprice = lxp;
    }

    ~gameStats(){

    }
};

class Functions
{
    public:
        Functions();
        virtual ~Functions();
        int diceRoll(int n);
        gameData randMonster();
        void buyWeapon();
        void buyArmor();
        void experience(gameData monster);
        int fightMonster(gameData monster);
        gameData copyMonster(gameData monster);
        int dungeon();
        int town();
        int character();
        int menu(std::string items[], int length);
        gameStats stat;

    protected:
    private:
        gameData player;
        gameData slime;
        gameData zombie;
        gameData skele;
        gameData human;
        gameData demon;
        gameData dragon;
};

#endif // FUNCTIONS_H
