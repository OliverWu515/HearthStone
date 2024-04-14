#include<cstdio>
#include<QString>
#include<QFile>
#include<iostream>
#include <QTextStream>
#include"deck.h"
int GetDeckNum()
{
    freopen("DeckNum.txt","r",stdin);
    int DeckNum;
    scanf("%d",&DeckNum);
    fclose(stdin);
    return DeckNum;
}
void SetDeckNum(int DeckNum)
{
    freopen("DeckNum.txt","w",stdout);
    printf("%d",DeckNum);
    fclose(stdout);
    return;
}
deck ReadDeck(int x)
{
    deck Deck;
    char s[30];
    sprintf(s,"deck%d.txt",x);
    freopen(s,"r",stdin);
    QTextStream in(stdin);
    //这样读取不会跳过名称里的空格
    Deck.Name=in.readLine();
    in>>Deck.Hero>>Deck.Sum;
    for (int i=1;i<=Deck.Sum;i++)
        in>>Deck.CardID[i];
    fclose(stdin);
    return Deck;
}
void SaveDeck(int x,deck Deck)
{
    char s[30];
    sprintf(s,"deck%d.txt",x);
    freopen(s,"w",stdout);
    QTextStream out(stdout);
    out<<Deck.Name<<Qt::endl;
    printf("%d\n",Deck.Hero);
    printf("%d\n",Deck.Sum);
    for (int i=1;i<=Deck.Sum;i++)
    printf("%d ",Deck.CardID[i]);
    fclose(stdout);
    return;
}
void DeleteDeck(int x)
{
    int DeckNum=GetDeckNum()-1;
    QFile::remove("deck"+QString::number(x)+".txt");
    for (int i=x;i<=DeckNum;i++)
        QFile::rename("deck"+QString::number(i+1)+".txt","deck"+QString::number(i)+".txt");
    SetDeckNum(DeckNum);
    return;
}
void RenameDeck(QString DeckName,int x)
{
    deck Deck=ReadDeck(x);
    Deck.Name=DeckName;
    SaveDeck(x,Deck);
    return;
}
