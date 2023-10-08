#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 10
#define bombs 15
int remainingCells=((size * size) - bombs);

void Place_Bombs(char board[size][size])
//This will make a board that is hidden from the player which allows the code to scan for bombs
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '-';
            // Fill whole board with dashes so that when the player loses or wins the board can show where the bombs are
        }
    }
    int point = 0;
    int x;
    int y;
    while(point < bombs)
    {
        x = rand() % (9 + 1);
        y = rand() % (9 + 1);
        //printf("%d %d\n", x, y);
        //set up the x and y values
        if (board[x][y] != 'X')
        //Make sure that only one bomb is placed in this spot
        {
            board[x][y] = 'X';
            point++;
        }
    }
}
void Create_Field(char board[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '-';
            //Fill whole board with dashes
        }
    }
    //Nothing needs to be returned as everything is printed here
}

void Randomize()
{
    time_t seconds;
    //Initialize time
    seconds = time(NULL);
    //get time based on unix time
    srand((unsigned)seconds);
    //make randomization seed using unix time for good randomization
    //Don't need to return anything to allow the randomization seed to work

}

int countAdjacentBombs(char board2[size][size], char board[size][size], int x, int y, int gameOver)
{
    int bombCount = 0;
    if (board2[y][x] == 'X')
    {
        //This checks if the players has placed chosen a bomb as there coordinate
        gameOver = 1;
    }
    else if (board2[y][x] == '-')
    {
        for (int i = -1; i <= 1; i++)
        //-1 to 1 so that it checks one to the left and to the right as well as up and down
        {
            for (int j = -1; j <= 1; j++)
            {
                if (y + i < 0 || y + i > 9 || x + j < 0 || x + j > 9)
                //Check if that tile is off of the board, if it is ignore it
                {
                    continue;
                }
                else
                {
                    if (board2[y + i][x + j] == 'X')
                    //Check if all of the nearby tiles have a bomb
                    {
                        bombCount++; 
                        //This is the amount of bombs nearby                         
                    }
                }
            }
        }
        //update both the shown and hidden board so that player can see what number it is and what it looks like when they win/lose
        board[y][x] = bombCount + '0';
        board2[y][x] = bombCount + '0';
        //Changes the point on the board to the number of bomvs nearby the + '0' makes it a char
    }
    else
    {
        printf("invalid input\n");
        remainingCells++;
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
        // This clears the inputs that are stored on scanf
    }
    return gameOver;
    //Make sure that the game ends
}
void printBoard(char board[size][size])
{
    int topRow[size];
    for (int i = 0; i <= size; i++)
    {
        topRow[i] = i;
        // Create the top row of the game in integers
    }
    int sideRow[size];
    for (int i = 0; i <= size; i++)
    {
        sideRow[i] = i;
        // Create the side row of the game in integers
    }

    for (int i = 0; i < size; i++)
    {
        switch (i)
        // Switch case makes sure there is a proper spacing of numbers on the top row
        {
        case 0:
            printf("  %d ", topRow[i]);
            break;
        case size - 1:
            printf("%d \n", topRow[i]);
            break;

        default:
            printf("%d ", topRow[i]);
            break;
        }
    }
    for (int k = 0; k < size; k++)
    {
        printf("%d ", sideRow[k]);
        // Print side row here so that it is on the left of the board in the correct row
        for (int l = 0; l < size; l++)
        {
            printf("%c ", board[k][l]);
            // Print out the board left to right top to bottom
        }
        printf("\n");
    }
}

int actualGame(int gameOver, char board[size][size], char board2[size][size])
{
    int x;
    int y;
    while (gameOver == 0)
    {
        if (remainingCells == 0)
        //This is the win condition that checks if the game is over
        {
            printBoard(board2);
            printf("YOU WIN!!\n");
            gameOver = 1;
        }
        else
        {
            printf("Put x and y coordinates you want to choose using integers with a space seperating them\n");
            int choice = scanf("%d %d", &x, &y);
            if (choice > 2 || choice < 2)
            {
                countAdjacentBombs(board2, board, 99, 99, gameOver);
            }
            else if (choice == 2)
            //take input, and make sure there are 2 inputs
            {
                if((x>=0 && x <= 9) && (y>=0 && y <= 9))
                { // Take input from the player
                    gameOver = countAdjacentBombs(board2, board, x, y, gameOver);
                    // Taking gameOver from the function to end or continue the game
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                    }
                    // This clears the inputs that are stored on scanf
                    if (gameOver == 1)
                    // This is the loosing condition, if this occurs the game is over
                    {
                        printBoard(board2);
                        printf("GAME OVER\n");
                    }
                    else
                    {
                        printBoard(board);
                        remainingCells--;
                        // reduce the number of remaing cells
                    }
                }
                else
                {
                    countAdjacentBombs(board2, board, 99, 99, gameOver);
                    continue;
                }
            }
            else
            {
                printf("Error 1\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF){}
                continue;
            }
        }
    }
    return gameOver;
}
void startGame(char board[size][size], char board2[size][size])
{
    Randomize();
    Create_Field(board);
    printBoard(board);
    Place_Bombs(board2);
}

int main()
{
    int gameOver = 0;
    char board[size][size];
    char board2[size][size];
    startGame(board, board2);
    while (gameOver == 0)
    {
        gameOver = actualGame(gameOver, board, board2);
    }
    return 0;
}