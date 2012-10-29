#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
/* global decalarations */
int turn = 0;/* this number will record whose turn is it */
int moves1=0,moves2=0;/* for tracking the number of moves played yet by participants*/
int spmove11=0,spmove21=0,spmove31=0,spmove41=0,spmove12=0,spmove22=0,spmove32=0,spmove42=0;/* flags to keep track the special moves of players */
int move_type=0,move=0;
int board[7][6];

/* functions used */
int legal_move();
int add_disk();
int check_win(int team);
int right_up(int x,int y);
int left_up(int x,int y);
int vertical(int x,int y);
int horizontal(int x,int y);
int write_board();
int draw_board();


int main()
{

    srand ( time(NULL) );
    /* initialization to generate a random number*/

    /* deciding the first player whose turn is it */

    ifstream pt ("turn.txt");
    /* opening the file in which the player who got the first turn is written */
    if(pt == NULL)/* no such file exists*/
    {
        turn = rand()%2 + 1;
        /* generatin a random number to decide the first player to play */
        ofstream ptr ("turn.txt");
        ptr<<turn;
        ptr.close();
    }
    else/* file exists */
    {
        pt>>turn;
        pt.close();
        ofstream file ("turn.txt");
        file<<turn+1;
        file.close();
    }
    /*initialzes empty board */
    for(int y=0;y<6;y++)
    for(int x=0;x<7;x++)
    board[x][y] = 0;
    write_board();

    /* call graphics function to draw the board */
    draw_board();

    int match_over = 0;/* flag telling match is over or not */

    while(1)/*starting the infinite loop*/
    {
        write_board();
        /*checking if board is full*/
        for(int y=0;y<6;y++)
        {
            int empty=0;/* flag for board empty */
            for(int x=0;x<7;x++)
            {
            if(board[x][y]==0)
                {
                empty = 1;
                break;
                }
            }
            if(empty==1)
            break;
            else/*board is full*/
                {
                printf("this match is a draw\n");
                match_over = 1;
                break;
                }
        }
        if(match_over==1)
        break;

        /*calling the participant code*/
       for(int temp=0;temp<=3;temp++)/* at max 3 times */
       {
           int legal = 1;
           if(temp == 3)
            {
                printf("game over\n");
                if(turn%2 == 1)
                printf("player 2 wins\n");
                else
                printf("player 1 wins\n");
                match_over = 1;
                break;
            }
            clock_t start = clock();
            if(turn%2 == 1)
            {
                /* call first participant code*/
            }
            else
            {
                /* call second participant code*/
            }
            if((((double)clock() - start) / CLOCKS_PER_SEC) > 2 )/* time taken is less than or equal to 2 secs*/
            continue;

            /* reading output */
            /* for testing only */
            fflush(stdin);
            char testnumber;
            testnumber = getchar();
            ifstream out ("output.txt");
            if(out == NULL)
            continue;
            else
            {
                out>>move_type;
                out>>move;
                out.close();
            }

            /* check if move is legal */
            int check = legal_move();
            if(check == 0)/* move is illegal */
            continue;

            if(legal == 1)/* this means code reaches succesfully i.e. move is legal */
            break;

       }

        if(match_over == 1)
        break;

        else/* match_over == 0 *//* match is not over */
        {
            add_disk();
            if(turn%2 == 0)
            moves2++;
            else
            moves1++;
            if(move_type==1)
            {
                if(turn%2==0)
                spmove12++;
                else
                spmove11++;
            }
            else if(move_type==2)
            {
                if(turn%2==0)
                spmove22++;
                else
                spmove21++;
            }
            else if(move_type==3)
            {
                if(turn%2==0)
                spmove32++;
                else
                spmove31++;
            }
            else if(move_type==4)
            {
                if(turn%2==0)
                spmove42++;
                else
                spmove41++;
            }
            turn++;

            draw_board();


            /* checking winner */
           int check1 = check_win(1);
           int check2 = check_win(2);
           if(check1 == 1 && check2 == 1)
           {
               printf("its a draw\n");
               break;
           }
           else if(check1 == 1)
           {
               printf("player 1 wins\n");
               break;
           }
           else if(check2 == 1)
           {
               printf("player 2 wins\n");
               break;
           }
        }
    }

    return 0;
}

int legal_move()
{
    if(move > 7 || move < 1)
    return 0;
    else if(board[move-1][0] != 0)/* top most position of column is not empty*/
    return 0;
    if(turn%2 == 0)/* for player 2 */
    {
        if(move_type == 1 && spmove12 == 1)
        return 0;
        else if(move_type == 2 && spmove22 == 1)
        return 0;
        else if(move_type == 3 && spmove32 == 1)
        return 0;
        else if(move_type == 4 && spmove42 == 1)
        return 0;
        else if(move_type != 4 && moves2 == 9 && spmove42 == 0)/* move type 4 means dual color block */
        return 0;
        /* move type 5 means normal move */
    }
    else
    {
        if(move_type == 1 && spmove11 == 1)
        return 0;
        else if(move_type == 2 && spmove21 == 1)
        return 0;
        else if(move_type == 3 && spmove31 == 1)
        return 0;
        else if(move_type == 4 && spmove41 == 1)
        return 0;
        else if(move_type != 4 && moves1 == 9 && spmove41 == 0)
        return 0;
    }
    return 1;
}

int add_disk()
{
    cout<<"move type is "<<move_type<<endl;
    for(int y = 0;y<6;y++)
    {
        if(board[move-1][y+1] != 0 || y+1>5)/* bottommost position in that column */
        {
            if(move_type == 1)/* 1 means detroying complete row */
            {
                for(int x=0;x<7;x++)
                {
                    for(int temp = y;temp>=0;temp--)
                    board[x][temp] = board[x][temp-1];
                    board[x][0] = 0;
                }
            }
            else if(move_type == 2)/* destroying complete column */
            {
                for(int temp = 0;temp<7;temp++)
                board[move-1][temp] = 0;
            }
            else if(move_type == 3)/* destroying neighbour block in every direction */
            {
                for(int temp = move-2;temp <= move;temp++)
                {
                    if(temp<0 || temp>6)
                    continue;
                    if(y+1<6)
                    board[temp][y+1]=0;
                    board[temp][y]=0;
                    if(y-1>=0)
                    board[temp][y-1]=0;

                    /* now need to shift zeroes */
                    for(int count=0;count < 3;count++)
                    {
                        for(int change = 5;change > 0;change--)
                        {
                            if(board[temp][change]==0)
                            {
                                board[temp][change] = board[temp][change-1];
                                board[temp][change-1] = 0;
                            }
                        }
                    }
                }

            }

            else if(move_type == 4)/* dual color block */
            {
            board[move-1][y] = 12;
            }
            else/* normal block */
            {
                cout<<"adding normal block\n";
                if(turn % 2 == 1)
                board[move-1][y] = 1;
                else
                board[move-1][y] = 2;
            }
            break;
        }
    }
    return 0;
}

int check_win(int team)
{
    int result=0,temp=0;
    for(int y=5;y>=0;y--)
    for(int x=0;x<7;x++)
    {
        if(board[x][y] == 0)/* block is empty  */
        continue;
        if(board[x][y] == team || board[x][y] == 12)
        {
            result = right_up(x,y);
            if(result!=1)
            result = left_up(x,y);
            if(result!=1)
            result = vertical(x,y);
            if(result!=1)
            result = horizontal(x,y);
        }
        if(result == 1)
        return 1;
    }
    return 0;
}

int right_up(int x,int y)
{
    if(y<3 || x>3)/* not possible */
    return 0;
    else if(x-1>=0 && y+1<6 && (board[x-1][y+1] == board[x][y] || board[x-1][y+1] == 12))
    return 0;/* condition was checked at x-1 and y+1 already */
    else
    {
        int count=1;
        for(int temp = 1;temp<4;temp++)
        {
            if(board[x+temp][y-temp] == board[x][y] || board[x+temp][y-temp] == 12)
            count++;
        }
        if(count == 4)
        return 1;
    }
    return 0;
}

int left_up(int x,int y)
{
    if(y<3 || x<3)/* not possible */
    return 0;
    else if(x+1<7 && y+1<6 && (board[x+1][y+1] == board[x][y] || board[x+1][y+1] == 12))
    return 0;/* condition was checked at x+1 and y+1 already */
    else
    {
        int count=1;
        for(int temp = 1;temp<4;temp++)
        {
            if(board[x-temp][y-temp] == board[x][y])
            count++;
        }
        if(count == 4)
        return 1;
    }
    return 0;
}

int vertical(int x,int y)
{
    if(y<3)
    return 0;
    else if( y+1 < 6 && (board[x][y+1] == board[x][y] || board[x][y+1] == 12))
    return 0;
    int count = 1;
    for(int temp=1;temp<4;temp++)
    {
        if(board[x][y-temp] == board[x][y] || board[x][y-temp] == 12 )
        count++;
    }
    if(count == 4)
    return 1;
    return 0;
}

int horizontal(int x,int y)
{
    if(x>3)
    return 0;
    else if( x-1>=0 && (board[x-1][y] == board[x][y] || board[x-1][y]==12))
    return 0;
    int count=1;
    for(int temp=1;temp<4;temp++)
    {
        if(board[x+temp][y] == board[x][y] || board[x+temp][y] == 12 )
        count++;
    }
    if(count == 4)
    return 1;
    return 0;
}

int write_board()
{

    ofstream pt ("board.txt");
    for(int y = 5 ; y>=0 ; y--)
    {
        for(int x = 0 ; x < 7 ;x++)
        {
            pt<<board[x][y]<<" ";
        }
    }
    pt.close();
    return 0;
}

int draw_board()
{
    printf("\n");
    for(int y = 0 ; y<6;y++)
    {
        for(int x = 0 ; x < 7 ; x++)

        printf("%d  ",board[x][y]);
        printf("\n");
    }
    printf("\n\n");
    return 0;
}
