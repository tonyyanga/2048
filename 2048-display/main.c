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
void upmove(int* origin, long* score);
struct intchain* fall(int* numlist, long*score, int* move);

struct intchain
{
    int value;
    struct intchain* point;
};

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
            case 'w':
            {
                move(status,1,&score);
                break;
            }
            case 'a':
            {
                move(status,3,&score);
                break;
            }
            case 's':
            {
                move(status,2,&score);
                break;
            }
            case 'd':
            {
                move(status,4,&score);
                break;
            }
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

	int* status;
	int convert[16];
    status=origin;
    int i;
	switch(side)
	{
	    case 1:
	    {
	        upmove(status, score);
	        break;
	    }
	    case 2:
	    {
	        for(i=0;i<=15;i++)
            {
                convert[12-4*((int)(i/4))+i%4]=*(origin+i);
            }
            upmove(convert,score);
            for(i=0;i<=15;i++)
            {
            *(status+12-4*((int)(i/4))+i%4)=convert[i];
            }
            break;
	    }
	    case 3:
	    {
	        for(i=0;i<=15;i++)
            {
                convert[3-(int)(i/4)+i%4*4]=*(origin+i);
            }
            upmove(convert,score);
            for(i=0;i<=15;i++)
            {
            *(status+(int)(i/4)+(3-i%4)*4)=convert[i];
            }
            break;
	    }
	    case 4:
	    {
	        for(i=0;i<=15;i++)
            {
                convert[(int)(i/4)+(3-i%4)*4]=*(origin+i);
            }
            upmove(convert,score);
            for(i=0;i<=15;i++)
            {
            *(status+3-(int)(i/4)+i%4*4)=convert[i];
            }
            break;
	    }
	}
}



void upmove(int* origin, long* score)
{

    int moved=0;
    int i=0;
	int j=0;
	int* status;
	int blank=0;
	int row[4];
    struct intchain* list;
	struct intchain* next;
	status=origin;
	//THE FOLLOWING REQUIRES CORRECTION.
	for(i=0;i<=3;i++)
				{
                    row[0]=*(status+i);
                    row[1]=*(status+i+4);
                    row[2]=*(status+i+8);
                    row[3]=*(status+i+12);
                    list=fall(row,score, &moved);
                    next=list;
                    for (j=0;j<=3;j++)
                    {
                        *(status+i+4*j)=list->value;
                        next=list->point;
                        free(list);
                        list=next;
                    }
				}
				blank=(*(status+12)==0)+(*(status+13)==0)+(*(status+14)==0)+(*(status+15)==0);
        if (moved)
        {
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
struct intchain* fall(int* numlist,long* score, int* move)
{
    int i=0;
    int* list=numlist;
    struct intchain* Head=NULL;
    struct intchain* End, *New;
    Head=End=New=(struct intchain*)malloc(sizeof(struct intchain));
    while(i<=1)
    {
        i++;
        New=(struct intchain*)malloc(sizeof(struct intchain));
        End->point=New;
        End->value=*(list++);
        End=New;
    }
    End->value=*(list++);
    New=(struct intchain*)malloc(sizeof(struct intchain));
    End->point=New;
    New->value=*list;
    New->point=NULL;
    End=Head;
    do
    {
        if (End->value==0)
        {
            if (End==Head)
            {
                New=Head;
                Head=Head->point;
                free(New);
                End=Head;
            }
            else
            {
                New->point=End->point;
                free(End);
                End=New;
                if(New->point)
                    if ((New->point)->value!=0)
                        (*move)+=1;
            }
        }
        New=End;
        if (End)
            if (End!=Head||Head->value!=0) End=End->point;
    }while(End);
    if(Head)
    {
        End=Head;
        while(End->point)
        {
            if (End->value==(End->point)->value&&End->value!=0)
            {
                End->value++;
                (*move)+=1;
                *score+=(int)pow(2,End->value);
                New=End->point;
                End->point=New->point;
                free(New);
            }else End=End->point;
        }
    }
    End=Head;
    New=Head;
    for (i=0;i<=3;i++)
    {
        if (!End)
        {
            End=(struct intchain*)malloc(sizeof(struct intchain));
            if (!Head)
            {
                Head=End;
                New=Head;
            }
            else New->point=End;
            End->value=0;
            End->point=NULL;

        }
        New=End;
        End=End->point;
    }

    End=Head;
    if (Head->value!=*numlist)
        (*move)+=1;
    return Head;
}
