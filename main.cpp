#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const int width=20;
const int height=20;
int x , y, fruitX ,fruitY, score;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};     //tracking directions
eDirection dir;
int tailX[100], tailY[100];
int nTail;

bool gameOver;
 void Setup(){
      gameOver=false;
      dir= STOP;         //start
      x=width/2;         //option of head ...center
      y=height/2;
      fruitX= rand()% width;
      fruitY= rand() % height;
      score=0;


 }

 void Draw(){
     system("cls"); // it will clear the system (console window)
     for(int i=0;i<width+2;i++)
        //for top wall
        cout<<"#";
    cout<<endl;
    //printing the map
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            
                if(j==0)
                    cout<<"#";
                if(i==y && j==x)
                    cout<<"O";            
                else if(i==fruitY && j==fruitX)
                    cout<<"F";
                else{
                    bool print=false;
                    for(int k=0;k<nTail; k++){
                        
                        //we are redrawing our tail again,
                        if(tailX[k]==j && tailY[k]==i){
                            cout<<"O";
                            print=true;
                        }
                       
                    }
                    if(!print)
                            cout<<" ";

                }
                   
                if(j==width-1)
                    cout<<"#";
                
            }
            cout<<endl;
        }
          
        for(int i=0;i<width+2;i++)
            //for bottom wall
            cout<<"#";
        cout<<endl;
        cout<<"SCORE:"<<score<<endl;
     
 }
   
 // a w s d used as commands

 void Input(){
   
   //we will use 2 functions from this libary and they are used for getting the input from the console
   if(_kbhit()){
    //if character presssed it will return a boolean value otherwise 0
      switch (_getch()){
            case 'a':
                dir=LEFT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 'x':
                gameOver=true;
                break;
        } 
   }
 }


  void Logic(){
        int prevX=tailX[0];
        int prevY=tailY[0];
        int prev2X, prev2Y;
        tailX[0]=x;
        tailY[0]=y;
        for(int i=1;i<nTail;i++){
            prev2X=tailX[i];
            prev2Y=tailY[i];
            tailX[i]=prev2X;
            tailY[i]=prev2Y;
            prevX=prev2X;
            prevY=prev2Y;
        }
        switch(dir){
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
               break;
        }
        if(x>width || x<0 || y<0 || y>height){
            gameOver=true; 
            //if it hits the wall the game is over.
        }

        // if you want the snake to cross the walls without loosing.
        /*
        if(x>=width) x=0; else if(x<0) x=width-1;
        if(y>=height) y=0; else if(y<0) y=height-1;
        
         */
        for(int i=0;i<nTail;i++){
            //if it hits itself the game is over.
            if(tailX[i]==x && tailY[i]==y){
                gameOver=true;
            }
        }
        
        if(x==fruitX && y==fruitY ){
            nTail++;
            score +=10; 
            fruitX= rand()% width;
            fruitY= rand() % height;

        }

 }

int main(){
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(50); //slows our game
    }
    return 0;
 }
  
 