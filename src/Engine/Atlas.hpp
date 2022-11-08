#pragma once

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Log.hpp"
#include "Constant.hpp"
#include "Helper.hpp"
#include "EntityDef.hpp"
#include "Application.hpp"
#include "Actions.hpp"
#include "Trigger.hpp"

namespace Engine {
  class Map;

  struct Layer {
    std::string name;
    std::vector<uint> base;
    std::vector<uint> decoration;
    std::vector<uint> collision;
  };

  class Tileset {
    public:
      Tileset(Engine::Application* t_app, const std::string t_file_path);

      std::string id;
      uint columns;
      uint rows;
      uint tile_width;
      uint tile_height;
      uint margin_x;
      uint margin_y;
      uint spacing;
      std::shared_ptr<sf::Texture> texture;
      std::vector<sf::IntRect> uvs;
  };

  struct TriggerPos {
    std::string key;
    uint x;
    uint y;
  };

  class Atlas {
    public:
      Atlas(const std::string t_file_path);
      // Atlas(Engine::Application& t_application, std::string t_manifest_key);

      std::string m_data_file;

      std::string id;
      std::string name;
      bool can_save;

      uint m_width;
      uint m_height;
      uint m_tile_width;
      uint m_tile_height;
      // The first_tile_id, and the manifest key to the tileset
      std::unordered_map<uint, std::string> m_tilesets;
      std::vector<Layer> m_layers;

      std::unordered_map<std::string, std::function<Actions::ActionFn (Engine::Map* t_map)>> m_action_map; // Key to action functions called on trigger events
      std::unordered_map<std::string, Trigger> m_trigger_types; // The trigger, which contains several event types, calls actions
      std::unordered_map<uint, std::string> m_triggers; // Locations that fire a trigger

      virtual void onWake(Engine::Map* t_map) {};
      uint coordToIndex(uint t_x, uint t_y, uint t_l = 0) const {
        return Helper::coordToIndex(m_width, m_height, t_x ,t_y, t_l);
      };
  };
}
