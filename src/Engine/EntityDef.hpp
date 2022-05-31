#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

#include "IState.hpp"


namespace Engine {
  class Map;
  class Character;

  /**
   * @brief Used to create actual entity classes
   *
   */
  struct EntityDef {
    std::string tileset; // manifest key
    uint start_frame;
    uint tile_x; // Initial position
    uint tile_y; // Initial position
    uint layer; // Initial position
    uint width;  // Uses tile size if set 0
    uint height; // uses tile size if set 0
  };

  typedef std::function<std::shared_ptr<Engine::IState> (Engine::Character* t_char, std::shared_ptr<Engine::Map> t_map)> StateFactoryFn;

  /**
   * @brief Used to create actual character classes
   *
   */
  struct CharacterDef {
    Engine::EntityDef entity;
    std::unordered_map<std::string, std::vector<int>> anims;
    std::unordered_map<std::string, Engine::StateFactoryFn> states;
    sf::Vector2i initial_direction = {1, 0};
    std::string initial_state = "wait";
  };
};
