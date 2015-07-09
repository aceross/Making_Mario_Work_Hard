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
    Eagle,
    Raptor,
    Desert,
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
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>  TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>      FontHolder;

#endif  // RESOURCE_IDENTIFIERS_HPP
