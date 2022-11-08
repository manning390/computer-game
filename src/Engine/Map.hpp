#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Log.hpp"
#include "Constant.hpp"

#include "Atlas.hpp"
#include "Entity.hpp"
#include "Application.hpp"
#include "Actions.hpp"

namespace Engine {
  // Predefine trigger
  class Trigger;

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
      uint getTileId(uint t_x, uint t_y, uint t_layer_index = 0) const;

      // Check collision at coordinate
      bool isBlocked(uint t_tx, uint t_ty, uint t_layer) const;

      // Converts coordinate to single dimension index
      uint coordToIndex(uint t_x, uint t_y, uint t_layer = 0) const;

      // Converts tile coord to pixel cord
      sf::Vector2f tileToPixel(uint t_tx, uint t_ty) const;
      // Converts pixel coord to tile cord
      sf::Vector2i pixelToTile(float t_x, float t_y, bool t_no_offset = false) const;
      sf::Vector2i pixelToTile(sf::Vector2f t_vec, bool t_no_offset = false) const;

      // Get map size in pixels
      sf::Vector2u getSizeP(void) const;

      // Get map size in tiles
      sf::Vector2u getSizeT(void) const;

      // Sets the map offset
      void setPosition(float t_x, float t_y);
      sf::Vector2f getPosition() const;
      // Places the map via offset to the center of the view
      void centerMapInView();

      void setAtlas(std::shared_ptr<Engine::Atlas>);
      std::shared_ptr<Engine::Atlas> getAtlas() const;

      std::shared_ptr<Engine::Trigger> getTrigger(uint t_x, uint t_y, uint t_layer = 0);

      // Run all character controllers
      bool update(float t_dt);

      // Renders the map
      void render(std::shared_ptr<Engine::Window> t_window, std::shared_ptr<Engine::Entity> t_hero = nullptr);

      std::shared_ptr<Engine::Entity> getEntity(uint t_x, uint t_y, uint t_layer = 0) const;
      void addEntity(std::shared_ptr<Engine::Entity> t_entity);
      void removeEntity(std::shared_ptr<Engine::Entity> t_entity);

      // Will be protected soon
      std::unordered_map<uint, std::shared_ptr<Engine::Trigger>> m_triggers;

      std::map<uint, std::shared_ptr<Engine::Entity>> m_entities;
      std::map<uint, std::shared_ptr<Engine::Character>> m_npcs;

    protected:
      float m_x = 0.0;
      float m_y = 0.0;
      sf::Vector2i m_cam;

      std::shared_ptr<Engine::Window> m_window;
      std::shared_ptr<Engine::Atlas> m_atlas;
      std::unordered_map<uint, std::shared_ptr<sf::Texture>> m_textures;
      std::unordered_map<uint, sf::IntRect> m_uvs;
      // Index stacked with layers (layer + 1) * (width * height) + tile index

      sf::Sprite m_sprite;

      // In tiles
      const uint m_width;
      const uint m_height;

      uint m_width_pixel;
      uint m_height_pixel;

      uint m_blocking_tile;

      uint m_tile_width;
      uint m_tile_height;

      std::vector<uint>& getLayer(uint t_layer_index = 0) const;
      void renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer& t_layer);
      void renderEntities(std::shared_ptr<Engine::Window> t_window, uint t_layer, std::shared_ptr<Engine::Entity> t_hero = nullptr);
  };
}
