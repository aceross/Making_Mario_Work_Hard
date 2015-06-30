// Copyright 2015, Aaron Ceross

#include "../include/maze.hpp"

Maze::Maze() {}
void Maze::ReadFile() {
  std::cout << "Starting Read file." << std::endl;
  std::ifstream maze_file;

  maze_file.open("assets/maze.txt");

  maze_file >> height >> width;
  printf("Height = %d\n", height);
  printf("Width = %d\n", width);

  for (int i = 0; i < height; ++i) {
    char ch = maze_file.get();
    int j = 0;
    while (ch != EOF && j < width) {
      layout[i][j] = ch;
      ++j;
      ch = maze_file.get();
    }
  }


  // for (int i = 0; i < height; ++i) {
  //   for (int j = 0; j < width; ++j) {
  //     maze_file >> layout[i][j];
  //   }
  // }
  std::cout << "Input complete." << std::endl;
  return;
}

void Maze::Print() {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      std::cout << layout[i][j];
    }
  }
  std::cout << std::endl;
}

void Maze::Run() {
  ReadFile();
  Print();
}

Maze::~Maze() {}
