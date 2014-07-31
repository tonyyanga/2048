#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

void game();
int command(char *choices[], int display);
void move(int* origin, int side, long* score);
void showstatus(int* origin,long score);
void initiate(int* origin);

char *menu[] = {"a - new game", "q - quit", NULL,};
char *direction[] = {"w","a","s","d",NULL};
int main()
{
    int choice=0;
    printf("Welcome to use Tony's 2048! \n");
    do
    {
        choice=command(menu,TRUE);
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

int command(char *choices[], int display)    //Get the command contents
{
    int chosen=0;
    int selected;
    char **option;
    do
    {
        option=choices;
        if (display)
        {
            while(*option)
            {
                printf("%s\n",*option);
                option++;
            }
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
    int status[16];
    int choice;
    long score=0;
    int i;
    int die=FALSE;
    printf("A game is initiated.\nUse WASD to play.\nWish you good luck!\n");
    initiate(status);
    do
    {
        showstatus(status, score);
        choice=command(direction,FALSE);
        switch (choice)
        {
            case 'w':move(status,1,&score);
            case 'a':move(status,3,&score);
            case 's':move(status,2,&score);
            case 'd':move(status,4,&score);
            case 'q':break;
        }
        for(i=0;i<=15;i++)
        {
            if (status[i]==0) break;
            if ((i==15)&&(status[15]!=0))
                die=TRUE;
        }
    }while(!die);
    printf("The game is over. Your final score is %ld\n",score);
}

void showstatus(int* origin,long score)    //display the current status
{
    int i;
    int j;
    int result;
    int* status;
    status=origin;
    for(i=0;i<=15;i++)
    {
        if (i%4==0)
        {
            printf("#####################\n#    #    #    #    #\n#    #    #    #    #\n");
            printf("#");
        }
        result=(int)pow(2,*(status++));
        for(j=0;j<3-(int)log10(result);j++)
        {
            printf(" ");
        }
        if (result!=1)
            printf("%i#",result);
        else
            printf(" #");
        if (i%4==3)
        {
            printf("\n#    #    #    #    #\n");
        }
        if (i==15) printf("#####################\n");
    }
    printf("Current Score:%ld\n",score);
}

void initiate(int* origin)
{
    int i;
    int count;
    int j;
    int* status=origin;
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
            if((rand()%10)==9) (*status)++;
        }
        else if(count==j)
            {
                *status=1;
                if((rand()%10)==9) (*status)++;
            }
            else *status=0;
            status++;
    }
}

void move(int* origin, int side, long* score)    //calculate one move
//side: 1=up;2=down;3=left;4=right
{
	int i=0;
	int j=0;
	int* status;
	int blank=0;
	status=origin;
	switch (side)
	{
		case 1:
			{
				for(i=0;i<=3;i++)
				{
				    j=0;
				    do
                    {
                        if(*(status+4*(3-j)+i)!=0)
                        {
                            if (*(status+4*(2-j)+i)==0)
                            {
                                *(status+4*(2-j)+i)=*(status+4*(3-j)+i);
                                *(status+4*(3-j)+i)=0;
                                j++;
                            }else if (*(status+4*(2-j)+i)==*(status+4*(3-j)+i))
                                {
                                    *(status+4*(2-j)+i)+=1;
                                    *score+=*(status+4*(2-j)+i);
                                    *(status+4*(3-j)+i)=0;
                                    break;
                                }else j++;
                        }else j++;
                    }while(j<=2);
				}
				blank=(*(status+12)==0)+(*(status+13)==0)+(*(status+14)==0)+(*(status+15)==0);
				for(i=12;i<=15;i++)
				{
				    if (*(status+i)==0)
				    {
				        if ((int)rand()%blank==0)
				        {
                            if((rand()%10)==9) *(status+i)=2;
                             else *(status+i)=1;
				            break;
				        }else blank--;
				    }
				}
            }
	}
}
