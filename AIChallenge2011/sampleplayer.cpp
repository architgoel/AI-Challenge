#include<stdio.h>
#include<iostream>
#include"parameter.h"

class sampleplayer
{
    private:
        char playerid;
     public:   
        sampleplayer(char id)
        {
            playerid=id;
        } 
        
        int getmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx, int acc_direction,int life_left)// Funtion which will return the move by the player
        {
            //Return moves as #define UP ,DOWN ,RIGHT ,LEFT  
            //here just for stimulation a random move is returned
            int s=rand()%4;
            switch(s)
            {
                case 0: return UP;
                case 1: return DOWN;
                case 2: return LEFT;
                case 3: return RIGHT;
            }    
        }    
};    
