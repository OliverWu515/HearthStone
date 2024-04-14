#ifndef DECK_H
#define DECK_H
#define MaxDeck 10
#include<QDebug>
typedef struct {
    int Hero;
    int Sum;
    int CardID[31];
    QString Name;
}deck;
int GetDeckNum();
void SetDeckNum(int DeckNum);
deck ReadDeck(int x);
void SaveDeck(int x,deck Deck);
void DeleteDeck(int x);
void RenameDeck(QString DeckName,int x);
#endif // DECK_H
