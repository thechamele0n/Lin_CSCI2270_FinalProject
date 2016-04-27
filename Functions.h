#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>

struct GameData{
    std::string name;
    int health;
    int gold;
    int attack;
    int armor;
    int experience;
    int level;

    GameData(){

    };

    GameData(std::string nom, int hp, int gp, int att, int ar, int ex, int lvl){
        name = nom;
        health = hp;
        gold = gp;
        attack = att;
        armor = ar;
        experience = ex;
        level = lvl;
    }

    ~GameData(){

    }

};

struct GameStats{
    int weaponcost;
    int armorcost;
    int gamemode;
    int levelxp;
    int healprice;

    GameStats(){

    };

    GameStats(int wpc, int arc, int gm, int lxp, int healp){
        weaponcost = wpc;
        armorcost = arc;
        gamemode = gm;
        levelxp = lxp;
        healprice = lxp;
    }

    ~GameStats(){

    }
};

class Functions
{
    public:
        Functions();
        virtual ~Functions();
        int diceRoll(int n);
        GameData randMonster();
        void buyWeapon();
        void buyArmor();
        void experience(GameData monster);
        int fightMonster(GameData monster);
        GameData copyMonster(GameData monster);
        int dungeon();
        int town();
        int character();
        int menu(std::string items[], int length);
        GameStats stat;
        void monsterDamage(GameData monster);

    protected:
    private:
        GameData player;
        GameData slime;
        GameData zombie;
        GameData skele;
        GameData human;
        GameData demon;
        GameData dragon;
};

#endif // FUNCTIONS_H
