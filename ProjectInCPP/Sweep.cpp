#include <cstdlib>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

#define SIZE 10

class bomb {
  std::pair<int, int> pos;
  void placeBomb();
  bool operator==(std::pair<int, int> other){
    return pos == other;
  }
  bool contains(std::vector<bomb> List);
  public:
    bomb(){
      placeBomb();
    }
    ~bomb() = default;
  friend class board;
};

class board{
  int bombs = 10;
  int tiles = SIZE*SIZE - bombs;
  char gameBoard[SIZE][SIZE];
  std::vector<bomb> bombList;
  std::vector<bomb> makeBombList();
  void placeBombs();
  void initBoard();
  char checkAround(std::pair<int, int> pair);
  bool isOOB(int x, int y);
  public:
    bool moreTiles();
    board(){
      initBoard();
      makeBombList();
      placeBombs();
    }
    bool updateBoard(std::pair<int, int> pair);
    void print();
    void hiddenPrint();
};

bool board::moreTiles(){
  if (tiles){
    return true;
  }
  return false;
}

bool board::isOOB(int x, int y){
  if (x > SIZE || x < 0 || y > SIZE || y < 0){
    return true;
  }
  return false;
}

char board::checkAround(std::pair<int, int> pair){
  int count = '0';
  for(int i = -1; i <= 1; i++){ 
    for(int j = -1; j <= 1; j++){
      if (isOOB(pair.first + i, pair.second + j)){
        continue;
      }
      if (gameBoard[pair.second + i][pair.first+ j] == 'X'){;
        ++count;
      }
    }
  }
  return count;
}

bool board::updateBoard(std::pair<int, int> pair){
  if (isOOB(pair.first, pair.second)){
    std::cout << "Input Out Of Bounds" << std::endl;
    return false;
  }

  if (gameBoard[pair.second][pair.first] == 'X'){
    return true;
  }
  gameBoard[pair.second][pair.first] = checkAround(pair);
  this->tiles--;
  return false;
}

void board::initBoard(){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      gameBoard[i][j] = '#';
    }
  }
  return;
}

void bomb::placeBomb(){
  pos.first = rand() % SIZE;
  pos.second = rand() % SIZE;
  return;
}


bool bomb::contains(std::vector<bomb> List){
  for (bomb cur : List){
    if (*this == cur.pos){
      return true;
    }
  }
  return false;
}

void board::print(){
  std::cout << "  ";
  for (int i = 0; i < SIZE; i++){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < SIZE; i++){
    std::cout << i << " ";
    for (int j = 0; j < SIZE; j++){
      std::cout << gameBoard[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return;
}

void board::hiddenPrint(){
  std::cout << "  ";
  for (int i = 0; i < SIZE; i++){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < SIZE; i++){
    std::cout << i << " ";
    for (int j = 0; j < SIZE; j++){
      if (gameBoard[i][j] == 'X'){
        std::cout << '#' << " ";
        continue;
      }
      std::cout << gameBoard[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return;
}

std::vector<bomb> board::makeBombList(){
  while (this->bombList.size()< bombs){
    bomb pos;
    if (pos.contains(this->bombList)){
      continue;
    }
    this->bombList.push_back(pos);
  }
  return bombList;
}

void board::placeBombs(){
  for (bomb cur : this->bombList){
    gameBoard[cur.pos.first][cur.pos.second] = 'X';
  }
  return;
}

class game{
  public:
    std::pair<int, int> takeInput();
    bool gameOver = false;
};

std::pair<int, int> game::takeInput(){
  std::pair<int, int> input;
  std::cout << "Enter x and y coordinates separated by space: ";
  std::cin >> input.first >> input.second;
  return input;
}

int main(){
  srand(time(NULL));
  board board;
  game game;
  while (!game.gameOver && board.moreTiles()) {
    board.hiddenPrint();
    game.gameOver = board.updateBoard(game.takeInput());
  }
  if (game.gameOver){
    std::cout << "LOSE" << std::endl;
    return 0;
  }

  std::cout << "WIN" << std::endl;
}
