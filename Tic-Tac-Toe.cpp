#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char winner);

int main()
{
    srand(time(NULL)); // Seed the random number generator
    char winner = ' ';
    resetBoard();
    while (winner == ' ' && checkFreeSpaces() > 0)
    {
        printBoard();
        playerMove();
        winner = checkWinner();
        if (winner != ' ')
        {
            break;
        }
        printBoard();
        computerMove();
        winner = checkWinner();
    }
    printBoard();
    printWinner(winner);
    printf("press any key to exit\n");
    getch();
    return 0;
}

void resetBoard()
{
   for( int i= 0; i<3; i++)
   {
     for( int j= 0; j<3; j++)
     {
        board[i][j] = ' ';
     }
   }
}

void printBoard()
{
  printf("\t%c\t | %c\t | %c\n", board[0][0], board[0][1], board[0][2]);
  printf("\t  ------------------------\n");
  printf("\t%c\t | %c\t | %c\n", board[1][0], board[1][1], board[1][2]);
  printf("\t  ------------------------\n");
  printf("\t%c\t | %c\t | %c\n\n", board[2][0], board[2][1], board[2][2]);
}

int checkFreeSpaces()
{
    int freeSpaces = 9;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++) 
        {
            if(board[i][j] !=' ')
            {
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}

void playerMove()
{
    int x, y;

    do
    {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (x < 0 || x > 2 || y < 0 || y > 2)
        {
            printf("Invalid input! Please enter numbers between 1 and 3.\n");
        }
        else if (board[x][y] != ' ')
        {
            printf("Invalid move! That space is already occupied.\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove()
{
    int x, y;
    char winner;

    // Check for a winning move
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if (board[x][y] == ' ')
            {
                board[x][y] = COMPUTER;
                winner = checkWinner();
                if (winner == COMPUTER)
                    return; // Winning move found
                else
                    board[x][y] = ' '; // Reset the move
            }
        }
    }

    // Check for a blocking move
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if (board[x][y] == ' ')
            {
                board[x][y] = PLAYER;
                winner = checkWinner();
                if (winner == PLAYER)
                {
                    board[x][y] = COMPUTER; // Block the player's winning move
                    return;
                }
                else
                    board[x][y] = ' '; // Reset the move
            }
        }
    }

    // Make a random move
    do
    {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
}

char checkWinner()
{
    for(int i= 0; i<3; i++)
    {
        if(board[i][0] == board[i][1] &&  board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // check columns
    for(int j= 0; j<3; j++)
    {
        if(board[0][j] == board[1][j] &&  board[0][j] == board[2][j])
        {
            return board[0][j];
        }
    }

    // check diagonals
    if(board[0][0] == board[1][1] &&  board[0][0] == board[2][2])
        {
            return board[0][0];
        }
     if(board[0][2] == board[1][1] &&  board[0][2] == board[2][0])
        {
            return board[0][2];
        }
 
     return ' ';
}     

void printWinner(char winner)
{
  if(winner == PLAYER)
  {
    printf("YOU WIN!\n");
  }
  else if(winner == COMPUTER)
  {
    printf("YOU LOSE\n");
  }
  else
  {
    printf("IT's a TIE\n");
  }  
}
