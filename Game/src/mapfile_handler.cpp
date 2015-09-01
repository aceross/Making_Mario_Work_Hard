// Copyright 2015, Aaron Ceross

#include "../include/mapfile_handler.hpp"

MapfileHandler::MapfileHandler() {}

std::string MapfileHandler::GetMapfile() {
  return mapfile_;
}

void MapfileHandler::SetMapfile(std::string mapfile) {
  mapfile_ = mapfile;
}
