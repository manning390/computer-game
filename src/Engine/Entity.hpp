#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Application.hpp"

namespace Engine {
  /**
   * @brief Used to create actual entity classes
   *
   */
  struct EntityDef {
    std::string texture; // manifest key
    uint width;
    uint height;
    uint tile_x;
    uint tile_y;
    uint start_frame = 0;
  };

  class Entity {
    public:
      Entity(Engine::Application& t_app, EntityDef &t_entity_def);

    protected:
      sf::Sprite m_sprite;
      sf::Texture m_texture;
      uint m_width;
      uint m_height;
      uint m_tile_x;
      uint m_tile_y;
      uint m_start_frame = 0;
  };
}
