#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "EntityDef.hpp"
#include "Application.hpp"

namespace Engine {
  class Entity : public std::enable_shared_from_this<Entity> {
    public:
      Entity(const EntityDef& t_def);

      uint m_x, m_y;
      uint m_tile_x, m_tile_y;
      uint m_layer = 0;
      uint m_start_frame = 0;
      sf::Sprite m_sprite;

      void update(float t_delta);

      void render(std::shared_ptr<Engine::Window> t_window);

      void setFrame(uint t_frame);

      // Not fully complete, just temp
      void setTilePos(uint x, uint y, uint layer, Engine::Map* t_map);
      void setTilePos(uint t_x, uint t_y, Engine::Map* t_map) {
        setTilePos(t_x, t_y, 0, t_map);
      };
      sf::Vector2i getTilePos() const;


    protected:
      // sf::Texture m_texture;
      std::shared_ptr<Engine::Tileset> m_tileset;
      uint m_width;
      uint m_height;
  };
}
