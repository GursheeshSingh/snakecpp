#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
using namespace std;
void ClearScreen();
const int length=100;
int len=6;
char choice='d'; // 'd'=forward 'w'=upward 's'=downward 'a' = backward

class screen;


int count=0;

class snakepart
{
public:
    int own[2];         // its own location
    int next[2];        //next location of the snakepart
public:
    void initializeLocation();
    void display();
    // friend void intializeLocation(snakepart &,snakepart &);
    void oneStepHeadForward();                      //only for head
    void oneStepHeadUpward();                       //only for head
    void oneStepHeadDownward();                     //only for head
    void oneStepHeadBackward();
    bool checkPrevious(snakepart);
    bool checkFood(int,int);
    void moveToNext();                                      // others will move to next location
    friend void updateNextLocation(snakepart &,snakepart &);
    friend void toScreen(screen &,snakepart &);

};


class screen
{
    int p[21][61];

public:
    screen(); //inititalize all to zero
    friend void display();
    int checkPlace(int,int); //check if snake is at the passed position
    friend void toScreen(screen &,snakepart &);
    void resetScreen();
    friend void toScreenFood(screen &,int,int);
    void gameOver();

};


void snakepart :: display()
{
    cout << "Own Elements = " << own[0] << ' ' << own[1] << endl << "Next= " << next[0] << ' ' << next[1] << endl;
}

/*
void initializeLocation(snakepart &s1,snakepart &s2) //pairs in 2 will be called each time different than last
{
    s1.own[0]=s2.own[0]=s1.next[0]=s2.next[0]=10;
    s1.own[1]=count+1;
    s1.next[1]=count+2;
    s2.own[1]=count+2;
    s2.next[1]=count+3;
    count=count+2;
}

*/


void screen :: resetScreen()
{
    for(int i=0; i<=20; i++)
    {
        for(int j=0; j<=60; j++)
        {
            p[i][j]=0;
        }
    }
}


void snakepart :: oneStepHeadForward()      // s[5] is head if length
{
    if(own[1]>=60)
        own[1]=0;
    if(next[1]>=60)
        next[1]=0;

    own[1]=own[1]+1;
    next[1]=next[1]+1;
}


void snakepart :: oneStepHeadBackward()      // s[5] is head if length
{
    if(own[1]<=1)
        own[1]=61;
    if(next[1]<=1)
        next[1]=61;
    own[1]=own[1]-1;
    next[1]=next[1]-1;
}


void snakepart :: oneStepHeadUpward()
{
    if(own[0]<=1)
    {
        own[0]=21;
    }
    if(next[0]<=1)
    {
        next[0]=21;
    }
    own[0]=own[0]-1;
    next[0]=next[0]-1;
}


void snakepart :: oneStepHeadDownward()
{
    if(own[0]>=20)
    {
        own[0]=0;
    }
    if(next[0]<=20)
    {
        next[0]=0;
    }
    own[0]=own[0]+1;
    next[0]=next[0]+1;
}


void snakepart :: moveToNext()      // this is for all others than head
{
    own[0]=next[0];
    own[1]=next[1];
}


void updateNextLocation(snakepart &s1,snakepart &s2) //in this 2nd one will be called again as first and till 4
{
    s1.next[0]=s2.own[0];
    s1.next[1]=s2.own[1];
}


void toScreen(screen &s,snakepart &s1)
{
    int a,b;
    a=s1.own[0];        //this is row location of snakepart
    b=s1.own[1];        //this is column location of snakepart
    s.p[a][b]=1;
}

void toScreenFood(screen &s,int r,int c)
{
    s.p[r][c]=2;
}

void snakepart :: initializeLocation()
{
    own[0]=next[0]=10;
    own[1]=(count+1)%61;
    next[1]=(count+2)%61;
    ++count;
}

bool snakepart ::checkPrevious(snakepart s1)
{
    if((own[0]==s1.own[0]) && (own[1]==s1.own[1]))
    {
        return 1;
    }
    else
        return 0;
}

bool snakepart ::checkFood(int r,int c)
{
    if((own[0]==r) && (own[1]==c))
        return 1;
    else
        return 0;
}
//initializes all to zero

screen :: screen()
{
    int i,j;
    for(i=1; i<=20; i++)
    {
        for(j=1; j<=61; j++)
        {
            p[i][j]=0;
        }
    }
}



//checks if snake part is at location i,j
int screen ::checkPlace(int i,int j)
{
    if(p[i][j]==0)
    {
        return 0;
    }
    else if(p[i][j]==1)
        return 1;
    else if(p[i][j]==2)
        return 2;
}



void display(screen s)
{
    int i,j;

    //printing borders
    for(i=0; i<=21; i++)
    {

        for(j=0; j<=61; j++)
        {
            //displays boxes
            if( (j==0 || j==61) || (i==0 || i==21))
            {
                cout << char(178) << flush;
            }
            //display snake at places where function return 1
            else if(s.checkPlace(i,j)==1)
            {
                cout << char(167) << flush;
            }
            else if(s.checkPlace(i,j)==2)
            {
                cout << char(224) << flush;
            }
            else
                cout << ' ' << flush;
        }


        cout << endl;
    }
}



int main()
{
    int f=1,row,column; // if f is 1 food location is generated randomly and row and column specify the location


    srand(time(NULL)); // sets seed


    screen s1;
    snakepart s[length];


//  cout << "Initialize" << endl;
    /* for(int i=0; i<=5; i++)
    {
        s[i].initializeLocation();
    }


    */
    //for head=0;
    for(int i=length-1; i>=0; i--) // in this order is 543210 and 0 is head
    {
        s[i].initializeLocation();
        //   cout << i << endl;
        //  s[i].display();
    }

    for(;;)
    {
        //food initialize location


        //snake parts to screen
        for(int i=0; i<=len-1; i++)
        {
            toScreen(s1,s[i]);
        }

        while(f==1) // in the first turn during initialization f is 1 and is set to zero when we found an empty location on screen
        {
            row=(rand()%20)+1;
            column=(rand()%60)+1;
            if(s1.checkPlace(row,column)==0)
            {
                f=0;
            }
        }
        toScreenFood(s1,row,column); //send food location to screen

        display(s1);                  //displays screen with food and snake


        //system("cls");


        choice=getch();
        if(choice=='d')
            s[0].oneStepHeadForward();
        else if(choice=='w')
            s[0].oneStepHeadUpward();
        else if(choice=='s')
            s[0].oneStepHeadDownward();
        else if(choice=='a')
            s[0].oneStepHeadBackward();
        else
        {
            //   display(s1);
            ClearScreen(); //  if we comment this and any wrong key is entered a new window will be created and we will have 2 of them on screen
            continue;
        }
        //  s[0].display();


        for(int i=1; i<=length-1; i++) // this moves all other parts to next location from 1 to 5 where 0 is head and is already moved
        {

            s[i].moveToNext();

        }
//     cout << "Update Next Locations till 5" << endl;
        for(int i=length-1; i>=1; i--)     // this updates location of the next part
            // tail 5 notes location of 4 and 4 for 3 and so on will 1 for 0
        {
            updateNextLocation(s[i],s[i-1]);
            //    s[i].display();
        }



        int flag=0;

        for(int i=1; i<len; i++) //this checks after change of location if two parts have same location
        {
            if(s[0].checkPrevious(s[i])==1)
                flag=1;
        }
        if(flag==1)
        {
            cout << "You Lost" << endl;
            exit(1);
        }


        //   display(s1);
        ClearScreen();
        // system("cls");
        if(s[0].checkFood(row,column)==1) //checks if head is on location of food if yes then length of snake is increased by 1
        {
            len++;
            f=1;
        }



        s1.resetScreen();
    }
    return 0;
}
void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}


