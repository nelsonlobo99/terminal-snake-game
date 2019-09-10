#include<iostream>
#include<time.h>
#include<unistd.h>
#include<stdio.h>
#include<thread>
//#include <ncurses.h>

using namespace std;
int tailLen=0;
int tailX[100]={0},tailY[100]={0};
bool gameOver;
const int width=70, height = 20; 
int score=0;
int x,y;
int fruitX, fruitY;
enum eDir {LEFT, RIGHT, UP, DOWN};
eDir dir;
void Setup(){
    gameOver = false;
    dir = LEFT;
    x = width/2;
    y = height/2;

    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void printNelson(){
    int matx[5][50] = {
{0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,1,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}
    };

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if(matx[i][j]==1){
                cout<<"#";
            }else
            {
                    cout<<" ";
            }
            
        }
        cout<<endl;
        
    }
}

void Draw(){
    system("clear");
    printNelson();
    for(int i=0;i<width+1;i++)
        cout << "#";
    cout<<endl;

    for(int i=0;i< height;i++){
        for (int j = 0; j < width; j++){
            if(j==0)
                cout<<"#";
            else {
                if(i==fruitY && j==fruitX)
                    cout<<"*";
                else if(i==y && j==x)
                    cout<<"X";
                else{
                    bool pri = false;
                    for(int k=0;k<tailLen;k++){
                        if(tailX[k] == j && tailY[k]==i){
                            cout<<"*";
                            pri = true;
                        }
                    }
                    if(!pri)
                        cout<<" ";
                }
                    
            }
                
            
            if(j==width-1)
                cout<<"#";
        }
        cout<<endl;
        
    }

    for(int i=0;i<width+1;i++)
        cout << "#";
    cout<<endl;

    cout<<"SCORE:: "<<score<<endl;
}
void Input(){
    while(!gameOver){
    char ch;

    system("stty -echo"); // supress echo
    system("stty cbreak"); // go to RAW mode
    ch = getchar();
    switch(ch){
        case 'w':
        case 'W':   if(dir!=DOWN)
                        dir = UP;
                    break;
        case 's':   if(dir!=UP)
        case 'S':       dir = DOWN;
                    break;
        case 'a':
        case 'A':   if(dir!=RIGHT)
                        dir = LEFT;
                    break;
        case 'd':
        case 'D':   if(dir!=LEFT)
                        dir = RIGHT;
                    break;
        case 'x':
        case 'X':      
                    gameOver = true;
                    break;
    }
    system ("stty echo"); // Make echo work
    system("stty -cbreak");// go to COOKED mode
    }
}
void Logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<tailLen;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX; 
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
 switch(dir){
    case LEFT:  x--;
                break;
    case RIGHT: x++;
                break;
    case UP:    y--;
                break;
    case DOWN:  y++;
                break;
    default: break;
 }
 if(x==fruitX && y == fruitY){
    tailLen++;
    score++;
    fruitX = rand() % width;
    fruitY = rand() % height;
 }
if(x==0 || y == -1 || x == width || y == height){
    gameOver = true;
 }

 for(int k=1;k<tailLen;k++){
     if(tailX[k]==x && tailY[k]==y)
        gameOver = true;
 }
}
void Run(){\    
    while(!gameOver){
        Draw();
        Logic();
        usleep(100000);
    }

}
int main(){
   // void *run = &Run;
    //void *input = &Input;

    Setup();
    thread t1(Input);
    thread t2(Run);

    cout<<dir;
    t1.join();
    t2.join();
    cout<<"GAMEOVER!!"<<endl;
    return 0;
}
