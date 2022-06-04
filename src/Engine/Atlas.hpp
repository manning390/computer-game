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

  // struct TriggerPos {
    // std::string key;
    // uint x;
    // uint y;
  // };

  class Atlas {
    public:
      Atlas(const std::string t_file_path);
      // Atlas(Engine::Application& t_application, std::string t_manifest_key);

      std::string id;
      std::string name;
      bool can_save;

      uint width;
      uint height;
      uint tile_width;
      uint tile_height;
      // The first_tile_id, and the manifest key to the tileset
      std::unordered_map<uint, std::string> tilesets;
      std::vector<Layer> layers;

      virtual void onWake(Engine::Map* t_map) {};

      // std::unordered_map<std::string, TriggerPos> triggers;
      // std::unordered_map<std::string, Trigger> trigger_types;
  };
}
