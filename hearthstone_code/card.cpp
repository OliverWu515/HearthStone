#include<cstdio>
#include <card.h>
void SetCard(CARD Card[])
{
    if(freopen("card.txt","r",stdin)==NULL)
        {
            qDebug()<<"wrong!";
            return;
        }
    else qDebug()<<"successfully read!";
    for (int i=1;i<=MaxCard;i++)
    {
        Card[i].ID=i;
        scanf("%s%d%d%d%d",Card[i].Name,&Card[i].Type,&Card[i].Hero,&Card[i].Rarity,&Card[i].Cost);
        if (Card[i].Type==1)
        scanf("%d%d%d%d%d%d%d",
        &Card[i].Minion.MaxAttack,
        &Card[i].Minion.MaxHealth,
        &Card[i].Minion.Taunt,
        &Card[i].Minion.Stealth,
        &Card[i].Minion.Charge,
        &Card[i].Minion.Windfury,
        &Card[i].Minion.DivineShield);
        else
        if (Card[i].Type==2)
        scanf("%d%d",
        &Card[i].Weapon.Attack,
        &Card[i].Weapon.Durability);
    }
    fclose(stdin);
}
int GetHeroCard(int x,int CardNum[],CARD Card[])
{
    int Total=0;
    for (int i=1;i<=MaxCard;i++)
         if (Card[i].Hero==x)
             Total++,CardNum[Total]=i;
    return Total;
}

QString GetHeroName(int x)
{
    QString HeroName[]={"中立","德鲁伊","猎人","法师","圣骑士","牧师","潜行者","萨满祭司","术士","战士"};
    return HeroName[x];
}
