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
  class Tileset;

  /**
   * @brief Used to create actual entity classes
   *
   */
  struct EntityDef {
      std::string id;
      std::shared_ptr<Engine::Tileset> tileset;
      uint start_frame;
      uint tile_x; // Initial position
      uint tile_y; // Initial position
      uint layer; // Initial position
      uint width;  // Uses tile size if set 0
      uint height; // uses tile size if set 0
  };

  /**
   * @brief Used for making Character States
   */
  typedef std::function<std::shared_ptr<Engine::IState> (Engine::Character* t_char, Engine::Map* t_map)> CharacterStateFactoryFn;
  template<class T>
  inline CharacterStateFactoryFn makeStateFactory(void) {
    return [](Engine::Character* t_char, Engine::Map* t_map){ return std::make_shared<T>(t_char, t_map); };
  };

  /**
   * @brief Used to create actual character classes
   *
   */
  struct CharacterDef {
    std::string id;
    Engine::EntityDef entity;
    std::unordered_map<std::string, std::vector<int>> anims;
    std::unordered_map<std::string, Engine::CharacterStateFactoryFn> states;
    sf::Vector2i initial_direction = {0, 1};
    std::string initial_state = "wait";
  };
};
