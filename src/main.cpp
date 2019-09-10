#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<thread>

using namespace std;
int tailLen=0; // Tail length variable
int tailX[100]={0},tailY[100]={0}; // Tail position tracker variable 
bool gameOver; // Set to 1 if Game Over else reset to 0
const int width=70, height = 20;  // Width and Height of the Game Screen 
int score=0; // Score
int x,y; // X & Y axis position tracer for the snake head
int fruitX, fruitY; // X & Y position co-ordinates of the fruit
enum eDir {LEFT, RIGHT, UP, DOWN}; // Directions 
eDir dir; //Direction varable 

//Sets up the new game
void Setup(){
    gameOver = false; //Sets Game Over variable to false inorder for the game to start
    dir = RIGHT; // Initially snake starts moving in the right direction from the center 
    //Set the initial position of the snake to the center of the game screen
    x = width/2;
    y = height/2;

    //Place the fruit randomly on the game screen
    fruitX = rand() % width;
    fruitY = rand() % height;

    //Set the Score to 0
    score = 0;
}

//This is not so important 
//My name is encoded inside the Matrix matx
//Which will be printed above the game screen

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
            //if the element of the 2D array is print # else print space
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
    system("clear"); //Clear the terminal screen for each frame 
    printNelson(); // Draw NELSON 

    //Draw the top border of the game screen
    for(int i=0;i<width+1;i++) 
        cout << "#";
    cout<<endl;//Go to next line


    for(int i=0;i< height;i++){
        for (int j = 0; j < width; j++){
            if(j==0 || j==width-1)
                cout<<"#"; // Print # at index 0 of j to draw the verticle border.
            else {
                if(i==fruitY && j==fruitX)
                    cout<<"*"; // Draw 8 at postion fruitY and fruitY
                else if(i==y && j==x)
                    cout<<"X"; // Draw snake head at position x&y
                else{
                    bool pri = false; // print tail flag is false
                    for(int k=0;k<tailLen;k++){
                        if(tailX[k] == j && tailY[k]==i){
                            cout<<"*"; // Draw tail
                            pri = true; // Set  print tail flag as true 
                        }
                    }
                    if(!pri) 
                        cout<<" "; // if print tail flag is 0 then print "space"
                 }
                    
            }
                
        }
        cout<<endl; // Do to next line
        
    }
    //Draw the bottom horizontal border of the same screen
    for(int i=0;i<width+1;i++)
        cout << "#";
    cout<<endl;
    //Display Score
    cout<<"SCORE:: "<<score<<endl;
}

//Keyboard Input
void Input(){
    while(!gameOver){
    char ch;

    system("stty -echo"); // supress echo
    system("stty cbreak"); // go to RAW mode
    ch = getchar(); // Get character from keyboard
    switch(ch){
        case 'w':
        case 'W':   if(dir!=DOWN)
                        dir = UP; //set direction UP if w is pressed
                    break;
        case 'S':
        case 's':   if(dir!=UP) 
                   dir = DOWN; //set direction DOWN if s is pressed
                    break;
        case 'a':
        case 'A':   if(dir!=RIGHT)
                        dir = LEFT;//set direction LEFT if a is pressed
                    break;
        case 'd':
        case 'D':   if(dir!=LEFT)
                        dir = RIGHT;//set direction RIGHT if d is pressed
                    break;
        case 'x':
        case 'X':      
                    gameOver = true; // Exit game on press x
                    break;
    }
    system ("stty echo"); // Make echo work
    system("stty -cbreak");// go to COOKED mode
    }
}
void Logic(){
    //Track the tail 
    int prevX=tailX[0];  
    int prevY=tailY[0];
    int prev2X,prev2Y;
    // Set the start of the tail to the position of snake head
    tailX[0]=x; 
    tailY[0]=y;
    // Tail tracking logic is similar to the fibonacci non recursive algorithm logic 
    for(int i=1;i<tailLen;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX; 
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    //Move snake in the specified direction 
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
 //If snake eats the fruit increment the score and tail length and set fruit co-ordinates to a new random location with the game screen
    if(x==fruitX && y == fruitY){
        tailLen++;
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
 //If snake hits the border wall then game over i
    if(x==0 || y == -1 || x == width || y == height){
        gameOver = true;
    }
// if snake hits itself game over
    for(int k=1;k<tailLen;k++){
        if(tailX[k]==x && tailY[k]==y)
        gameOver = true;
    }
}

//This function runs the Draw and Logic fucnction as long as game over is set to false
void Run(){   
    while(!gameOver){
        Draw();
        Logic();
        usleep(100000); // Readuce the game speed by addding delay
    }

}
int main(){

    Setup(); // Set up new game 

    thread t1(Input); // Thread t1 takes input from the keyboard 
    thread t2(Run); // Thread t2 run the game logic parallel to the input thread

    t1.join(); // Join t1 to the main thread
    t2.join(); // Join t2 to the main thread 
    
    cout<<"GAMEOVER!!"<<endl; // Print game over if game over is set to true 
    return 0; 
}
