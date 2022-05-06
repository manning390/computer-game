#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Log.hpp"
#include "Constant.hpp"

#include "Atlas.hpp"
#include "Application.hpp"

namespace Engine {
  class Map {
    public:
      Map(Application& t_app, std::shared_ptr<Engine::Atlas> t_atlas);
      ~Map() = default;

      // Move the camera to pixel
      void goTo(sf::Vector2i t_pos);
      void goTo(int t_x, int t_y);

      // Move the camera to tile
      void goToTile(uint t_x, uint t_y);

      // Get the tile id from the coordinate and layer
      uint getTileIndex(uint t_x, uint t_y, uint t_layer_index = 0) const;

      // Check collision at coordinate
      bool isBlocked(uint t_layer, uint t_tx, uint t_ty) const;

      // Converts tile coord to pixel cord
      sf::Vector2f tileToPixel(uint t_x, uint t_y) const;
      // Converts pixel coord to tile cord
      sf::Vector2i pixelToTile(float x, float y) const;

      // Get map size in pixels
      sf::Vector2u getSize(void) const;

      // Sets the map offset
      void setPosition(float t_x, float t_y);
      sf::Vector2u getPosition() const;
      // Places the map via offset to the center of the view
      void centerMapInView();

      void setAtlas(std::shared_ptr<Engine::Atlas>);
      std::shared_ptr<Engine::Atlas> getAtlas() const;


      // Renders the map
      void render(std::shared_ptr<Engine::Window> t_window);

    protected:
      float m_x = 0.0;
      float m_y = 0.0;
      sf::Vector2i m_cam;

      std::shared_ptr<Engine::Window> m_window;
      std::shared_ptr<Engine::Atlas> m_atlas;
      std::unordered_map<uint, std::shared_ptr<sf::Texture>> m_textures;
      std::unordered_map<uint, sf::IntRect> m_uvs;

      sf::Sprite m_sprite;

      // In tiles
      uint m_width;
      uint m_height;
      uint m_width_pixel;
      uint m_height_pixel;

      uint m_blocking_tile;

      uint m_tile_width;
      uint m_tile_height;

      std::vector<uint>& getLayer(uint t_layer_index = 0) const;
      void renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer& t_layer);
  };
}
