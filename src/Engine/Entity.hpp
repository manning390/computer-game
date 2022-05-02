#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/Map.hpp"

#include "EntityDef.hpp"
#include "Application.hpp"

namespace Engine {
  class Entity {
    public:
      Entity(Engine::Application& t_app, EntityDef &t_entity_def);

      void update(float t_delta);

      void render(std::shared_ptr<Engine::Window> t_window);

      void setFrame(uint t_frame);

      // Not fully complete, just temp
      void setTilePos(uint x, uint y, uint layer, std::shared_ptr<Engine::Map> t_map);

      sf::Sprite m_sprite;
      uint m_tile_x;
      uint m_tile_y;
      uint m_layer = 0;
      uint m_x;
      uint m_y;
      uint m_start_frame = 0;

    protected:
      // sf::Texture m_texture;
      std::shared_ptr<Engine::Tileset> m_tileset;
      uint m_width;
      uint m_height;
  };
}
