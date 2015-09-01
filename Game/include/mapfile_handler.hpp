// Copyright 2015, Aaron Ceross

#ifndef MAPFILE_HANDLER_HPP
#define MAPFILE_HANDLER_HPP

#include <string>

class MapfileHandler {
 public:
  MapfileHandler();
  void SetMapfile(std::string mapfile);
  std::string GetMapfile();
 private:
  std::string mapfile_;
};

#endif  // MAPFILE_HANDLER_HPP
