#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

#define N 100
#define B 20
//定义坐标x,y结构体
typedef struct pos
{
    int x;
    int y;
    int count;
} POS;
//定义蛇结构体
typedef struct snake
{
    POS node[N];//蛇身坐标
    int length;//蛇长
} SNAKE;
//延时函数
void delay(int i)
{
    while(i)
        i--;
}
//初始化蛇
void makesnake(SNAKE *a)
{
    a->node[0].x=B/2;
    a->node[0].y=B/2;
    a->node[1].x=B/2;
    a->node[1].y=B/2+1;
    a->node[2].x=B/2;
    a->node[2].y=B/2+2;
    a->length=3;
}
//移动蛇
void movesnake(SNAKE *a,char *b,char *oldb,POS *snakeend)
{
    int i,x,y;
    snakeend->x=a->node[a->length-1].x;
    snakeend->y=a->node[a->length-1].y;
    for(i=((a->length)-1); i!=0; i--)
    {
        (a->node[i].x)=(a->node[i-1].x);
        (a->node[i].y)=(a->node[i-1].y);
    }
    if(*oldb=='a'&&*b=='d')
        *b=*oldb;
    else if(*oldb=='w'&&*b=='s')
        *b=*oldb;
    else if(*oldb=='s'&&*b=='w')
        *b=*oldb;
    else if(*oldb=='d'&&*b=='a')
        *b=*oldb;
    if(*b=='d')
        (a->node[0].x)++;
    else if(*b=='w')
        (a->node[0].y)--;
    else if(*b=='a')
        (a->node[0].x)--;
    else if(*b=='s')
        (a->node[0].y)++;
    *oldb=*b;
}
//获取键盘指令
void get_hit(char *ch)
{
    if(!kbhit())
        ;
    else
        *ch=getch();
}
//打印蛇
void printfsnake(SNAKE a,POS food)
{
    int i,j,k,flag;
    system("cls");
    for(i=0; i<B; i++)
    {
        for(j=0; j<B; j++)
        {
            flag=1;
            for(k=0; k<a.length; k++)
            {
                if(((j==a.node[k].x)&&(i==a.node[k].y))||i==0||i==B-1||j==0||j==B-1)
                {
                    printf("■");
                    flag=0;
                    break;
                }
                else if(j==food.x&&i==food.y)
                {
                    printf("●");
                    flag=0;
                    break;
                }
            }
            if(flag==1) printf("  ");
        }
        printf("\n");
    }
    printf("your score is:%d",food.count*10);
}
//消化食物，蛇身+1
void food(POS *a,SNAKE b)
{
    srand(time(0));
    int i,j=1;
    // while(1)
    {
        a->x=rand()%(B-2)+1;
        a->y=rand()%(B-2)+1;
        a->count=0;
        for(i=0; i<b.length; i++)
            if(a->x!=b.node[i].x&&a->y!=b.node[i].y)
            {
                j=0;
                break;
            }
    }
}
//随机生成食物
void dealfood(POS *food,SNAKE *a,POS end)
{
    srand(time(0));
    int i,j=1;
    if(((a->node[0].x)==(food->x))&&((a->node[0].y)==(food->y)))
    {
        a->length++;
        a->node[a->length-1].x=end.x;
        a->node[a->length-1].y=end.y;
        food->y=rand()%(B-2)+1;

        food->count++;
        while(j)
        {

            food->x=rand()%(B-2)+1;
            food->y=rand()%(B-2)+1;
            for(i=0; i<a->length; i++)
                if(food->x!=a->node[i].x&&food->y!=a->node[i].y)
                {
                    j=0;
                    break;
                }
        }
    }
}
//判断蛇是否死亡
void snakedeath(SNAKE snake,int *death)
{
    int i;
    if((snake.node[0].y==0)||(snake.node[0].y==B-1)||(snake.node[0].x==0)||(snake.node[0].x==B-1))
        *death=0;
    for(i=1; i<snake.length; i++)
    {
        if(snake.node[0].x==snake.node[i].x&&snake.node[0].y==snake.node[i].y)
        {

            *death=0;
            break;
        }
    }
}
char ch='a',oldch='a';
POS snakeend;
//主函数
int main()
{
    printf("Please adjust your input method to English\nwelcome to xjf's snake game.\nlet's start it\n\npress \"enter\" key to start it");
    getchar();
    POS FOOD;
    int i,death=1;
    SNAKE snake;
    makesnake(&snake);
    food(&FOOD,snake);
    while(death)
    {
        delay(7000000);
        snakedeath(snake,&death);
        movesnake(&snake,&ch,&oldch,&snakeend);
        dealfood(&FOOD,&snake,snakeend);
        printfsnake(snake,FOOD);
        get_hit(&ch);
    }
    for(ch=0;ch<20;ch++)
    printf("\n\nGame over!!!");
    return 0;
}
