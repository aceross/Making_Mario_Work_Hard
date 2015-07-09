// Copyright 2015, Aaron Ceross

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceManager {
 public:
  void Load(Identifier id, const std::string& filename);

  template <typename Parameter>
  void Load(Identifier id, const std::string& filename, const Parameter& secondParam);

  Resource&       Get(Identifier id);
  const Resource& Get(Identifier id) const;

 private:
  void  InsertResource(Identifier id, std::unique_ptr<Resource> resource);

 private:
  std::map<Identifier, std::unique_ptr<Resource>> resource_map_;
};

#include "resource_manager.inl"
#endif  // RESOURCE_MANAGER_HPP
