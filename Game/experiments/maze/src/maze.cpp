// Copyright 2015, Aaron Ceross

#include <string>
#include <vector>
#include "../include/maze.hpp"

Maze::Maze() {}
void Maze::ReadFile() {
  std::cout << "Starting read file." << std::endl;
  std::ifstream maze_file;
  std::string line;

  maze_file.open("assets/maze1.txt");
  maze_file >> height >> width;
  printf("Height = %d\n", height);
  printf("Width = %d\n", width);
  while (std::getline(maze_file, line)) { grid.push_back(line); }

  std::cout << "Input complete." << std::endl;
  return;
}

void Maze::Print() {
  for (std::vector<std::string>::size_type i = 0; i < grid.size(); ++i) {
    for (std::vector<std::string>::size_type j = 0; j < grid[i].size(); ++j) {
      std::cout << grid[i][j];
    }
    std::cout << std::endl;
  }
}

void Maze::Run() {
  ReadFile();
  Print();
}

Maze::~Maze() {}
