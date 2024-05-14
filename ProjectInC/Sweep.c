#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10
#define bombs 15

int isOOB(int xPos, int yPos){
  return yPos < 0 || yPos > size-1 || xPos < 0 || xPos > size-1 ? 1 : 0;
}

void createField(char board1[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      board1[i][j] = '-'; 
    }
  }
}

void placeBombs(char board1[size][size]) {
  createField(board1);
  int bombsNearSpot = 0, xPos, yPos;
  while (bombsNearSpot < bombs) {
    xPos = rand() % 10;
    yPos = rand() % 10;
    if (board1[yPos][xPos] != 'X') {
      board1[yPos][xPos] = 'X';
      bombsNearSpot++;
    }
  }
}

void countAdjacentBombs(char board2[size][size], char board1[size][size], int xPos, int yPos) {
  int bombCount = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (isOOB(xPos + j, yPos + 1)) {continue;}
      if (board2[yPos + i][xPos + j] == 'X') {
        bombCount++; 
      }
    }
  }
  board1[yPos][xPos] = bombCount + '0';
  board2[yPos][xPos] = bombCount + '0';
  return; 
}

void printBoard(char board1[size][size]) {
  printf("  %d ", 0);
  for (int i = 1; i < size; i++) {
      printf("%d ", i);
  }
  puts("");
  for (int i = 0; i < size; i++) {
    printf("%d ", i); 
    for (int j = 0; j < size; j++) {
      printf("%c ", board1[i][j]); 
    }
    puts("");
  }
}

void actualGame(char board1[size][size], char board2[size][size]) {
  int xPos, yPos, remainingCells = ((size * size) - bombs); 
  while (1) {
    if (!remainingCells) {
      printf("\n\n\n\n YOU WIN\n");
      printBoard(board2);
      return;
    }
    printf("Enter integer coordinates (x y): ");
    int choice = scanf("%d %d", &xPos, &yPos), c; 
    while ((c = getchar()) != '\n' && c != EOF){}
    if (choice != 2 || isOOB(xPos, yPos)) {
      printf("not enough inputs or outside of range\n");
      continue;
    }
    if (board2[yPos][xPos] == 'X'){break;}
    if (board1[yPos][xPos] != '-' ){
      printf("Input Already Done\n");
      continue; 
    }
    countAdjacentBombs(board2, board1, xPos, yPos);
    printBoard(board1);
    remainingCells--;
  }
  printBoard(board2);
  printf("\nLOSE\n");
}

int main() {
  srand(time(NULL));
  char board1[size][size], board2[size][size];
  createField(board1);
  printBoard(board1);  
  placeBombs(board2); 
  printBoard(board2);  
  actualGame(board1, board2);    
}
