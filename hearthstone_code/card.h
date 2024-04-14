#ifndef CARD_H
#define CARD_H
#define MaxCard 42
#include <QDebug>
#include <stdio.h>
#include <QMetaType>

typedef struct minion{
    int Attack;
    int Health;
    int MaxAttack;
    int MaxHealth;
    bool Taunt;
    bool Stealth;
    bool Charge;
    bool Frozen;
    bool Windfury;
    bool DivineShield;
    //Battlecry
    //Deathrattle
}MINION;
typedef struct weapon{
    int Attack;
    int Durability;
}WEAPON;
typedef struct spell{
}SPELL;

typedef struct card{
    int ID;
    bool Rarity;//0 for common,1 for legendary
    int Hero;
    int Type;
    char Name[31];
//    char Description[100];
    int Cost;
    MINION Minion;
    WEAPON Weapon;
    SPELL Spell;
}CARD;

Q_DECLARE_METATYPE(MINION);
Q_DECLARE_METATYPE(WEAPON);
Q_DECLARE_METATYPE(SPELL);
Q_DECLARE_METATYPE(CARD);

void SetCard(CARD Card[]);
int GetHeroCard(int x,int CardNum[],CARD Card[]);
QString GetHeroName(int x);
#endif // CARD_H
