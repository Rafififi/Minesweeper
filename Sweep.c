#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 10
#define bombs 15
int remainingCells = ((size * size) - bombs);

void placeBombs(char board[size][size])
// This will make a board that is hidden from the player which allows the code to scan for bombs
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
    int xPos;
    int yPos;
    while (point < bombs)
    {
        xPos = rand() % (9 + 1);
        yPos = rand() % (9 + 1);
        // set up the x and y values of the bombs
        if (board[xPos][yPos] != 'X')
        // Make sure that only one bomb is placed in this spot
        {
            board[xPos][yPos] = 'X';
            point++;
        }
    }
}
void createField(char board[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '-';
            // Fill whole board with dashes
        }
    }
    // Nothing needs to be returned as everything is printed here
}

void randomize()
{
    time_t seconds;
    // Initialize time
    seconds = time(NULL);
    // get time based on unix time
    srand((unsigned)seconds);
    // make randomization seed using unix time for good randomization
    // Don't need to return anything to allow the randomization seed to work
}

int countAdjacentBombs(char board2[size][size], char board[size][size], int xPos, int yPos, int gameOver)
{
    int bombCount = 0;
    // bombCount is the number of bombs around the selected point
    if (board2[yPos][xPos] == 'X')
    {
        // This checks if the players has placed chosen a bomb as there coordinate
        gameOver = 1;
    }
    else if (board2[yPos][xPos] == '-')
    {
        for (int i = -1; i <= 1; i++)
        //-1 to 1 so that it checks one to the left and to the right as well as up and down
        {
            for (int j = -1; j <= 1; j++)
            {
                if (yPos + i < 0 || yPos + i > 9 || xPos + j < 0 || xPos + j > 9)
                // Check if that tile is off of the board, if it is ignore it
                {
                    continue;
                }
                else
                {
                    if (board2[yPos + i][xPos + j] == 'X')
                    // Check if all of the nearby tiles have a bomb
                    {
                        bombCount++;
                        // This is the amount of bombs nearby
                    }
                }
            }
        }
        // update both the shown and hidden board so that player can see what number it is and what it looks like when they win/lose
        board[yPos][xPos] = bombCount + '0';
        board2[yPos][xPos] = bombCount + '0';
        // Changes the point on the board to the number of bomvs nearby the + '0' makes it a char
    }
    else
    {
        // This will occur if the x and y coordinates are out the range of the board
        printf("input already done or outside of range\n");
        remainingCells++;
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
        // Clears the input buffer gotten from stack overflow (https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c)
    }
    return gameOver;
    // Make sure that the game ends
}
void printBoard(char board[size][size])
{
    int topRow[size];
    for (int i = 0; i < size; i++)
    {
        topRow[i] = i;
        // Create the top row of the game in integers
    }
    int sideRow[size];
    for (int i = 0; i < size; i++)
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
    int xPos;
    int yPos;
    while (gameOver == 0)
    {
        if (remainingCells == 0)
        // This is the win condition that checks if the game is over
        {
            printBoard(board2);
            printf("YOU WIN!!\n");
            gameOver = 1;
        }
        else
        {
            printf("Put x and y coordinates with a space seprating them: ");
            int choice = scanf("%d %d", &xPos, &yPos);
            if (choice > 2 || choice < 2)
            {
                countAdjacentBombs(board2, board, 99, 99, gameOver);
                //The 99 makes it so that it does not break due to non integers
            }
            else
            // take input, and make sure there are 2 inputs 
            {
                // Take input from the player
                // If in range of board goes here
                if (board2[yPos][xPos] != 'X' && board2[yPos][xPos] != '-')
                {
                    //Makes sure that this input has not already been inputted
                    countAdjacentBombs(board2, board, xPos, yPos, gameOver);
                    remainingCells--;
                }
                else
                {
                    gameOver = countAdjacentBombs(board2, board, xPos, yPos, gameOver);
                    // Taking gameOver from the function to end or continue the game
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF){}
                    // Clears the input buffer gotten from stack overflow (https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c)
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
            }
        }
    }
    return gameOver;
}
int main()
{
    int gameOver = 0;
    char board[size][size];
    char board2[size][size];
    //Initialize both the shown and hidden board as well as gameOver
    randomize();
    // get a randomizer seed
    createField(board);
    // Make a board of all dashes
    printBoard(board);
    // print out the board with all dashes
    placeBombs(board2);
    // Create a second board that will hold all the bombs hidden from the player
    //printBoard(board2); // Uncomment this to print answers
    while (gameOver == 0)
    {
        gameOver = actualGame(gameOver, board, board2);
        // Make sure the game continues until winning or losing
    }
    return 0;
}