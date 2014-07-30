#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void game();
int command(char *choices[]);
int* move(int* status, int side);
void showstatus(int* status);
void initiate(int* status);

char *menu[] = {"a - new game", "q - quit", NULL,};
int main()
{
    int choice=0;
    printf("Welcome to use Tony's 2048! \n");
    do
    {
        choice=command(menu);
        switch (choice)
        {
            case 'a':
            {
                game();
            }
        }
    }while(!(choice == 'q'));


    return 0;
}

int command(char *choices[])    //Get the command contents
{
    int chosen=0;
    int selected;
    char **option;
    do
    {
        option=choices;
        while(*option)
        {
            printf("%s\n",*option);
            option++;
        }
        do
        {
            selected = getchar();
        }while(selected =='\n');
        option = choices;
        while(*option)
        {
            if(selected == *option[0])
            {
                chosen = 1;
                break;
            }
            option++;
        }
        if(!chosen)
        {
            printf("Unknown choice\n");
        }
    }while(!chosen);
    return selected;
}
void game() //main game function
{
    int status[15];
    printf("A game is initiated.\nUse WASD to play.\nWish you good luck!\n");
    initiate(status);
    showstatus(status);



}

void showstatus(int* status)    //display the current status
{
    int i;
    int j;
    char display[4];
    for(i=0;i<=15;i++)
    {
        if (i%4==0)
        {
            printf("#####################\n#    #    #    #\n#    #    #    #\n");
            printf("#");
        }
        sprintf(display,"%i",*(status++));
        printf("%4s#",display);
        if (i%4==3)
        {
            printf("\n#    #    #    #\n");
        }
        if (i==15) printf("#####################\n");
    }
}

void initiate(int* status)
{
    int i;
    int count;
    int j;
    srand((unsigned)time(NULL));
    i=rand() %16;
    do
    {
        j=rand() %16;
    }while(j==i);
    for(count=0;count<=15;count++)
    {
        if(count==i)
        {
            *status=1;
            if(rand()>0.9) (*status)++;
        }
        else if(count==j)
            {
                *status=1;
                if(rand()>0.9) (*status)++;
            }
            else *status=0;
            status++;
    }
}

int* move(int* status, int side)    //calculate one move
//side: 1=up;2=down;3=left;4=right
{

}
