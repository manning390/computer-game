#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Log.hpp"
#include "Constant.hpp"

#include "Atlas.hpp"
#include "Application.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {
  class Map {
    public:
      Map(Application& t_app, std::shared_ptr<Engine::Atlas> t_atlas);
      ~Map() = default;

      void goTo(sf::Vector2i t_pos);
      void goTo(int t_x, int t_y);

      void goToTile(uint t_x, uint t_y);

      uint getTileIndex(uint t_x, uint t_y);

      sf::Vector2u getSize(void);

      void render(std::shared_ptr<Engine::Window> t_window);

      sf::Vector2f tileToPixel(uint t_x, uint t_y);
      sf::Vector2i pixelToTile(float x, float y);

      void setPosition(float t_x, float t_y);

      std::shared_ptr<Engine::Atlas> getAtlas() const;

    protected:
      float m_x = 0.0;
      float m_y = 0.0;
      sf::Vector2i m_cam;

      std::shared_ptr<Engine::Window> m_window;
      std::shared_ptr<Engine::Atlas> m_atlas;
      std::unordered_map<uint, std::shared_ptr<sf::Texture>> m_textures;
      std::unordered_map<uint, sf::IntRect> m_uvs;

      sf::Sprite m_sprite;
      Engine::Layer m_layer;

      // In tiles
      uint m_width;
      uint m_height;
      uint m_width_pixel;
      uint m_height_pixel;

      uint m_blocking_tile;

      std::vector<uint> m_tiles;
      uint m_tile_width;
      uint m_tile_height;

      void renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer t_layer);
  };
}
