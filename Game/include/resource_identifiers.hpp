// Copyright 2015, Aaron Ceross

#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
}

namespace Textures {
  enum ID {
    Mario,
    Level,
    TitleScreen,
    ButtonNormal,
    ButtonSelected,
    ButtonPressed
  };
}  // namespace Textures

namespace Fonts {
  enum ID { Main, };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID>  TextureHolder;
typedef ResourceManager<sf::Font, Fonts::ID>        FontHolder;

#endif  // RESOURCE_IDENTIFIERS_HPP
