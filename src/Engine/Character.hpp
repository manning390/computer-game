#pragma once

#include <cassert>

#include "Engine/EntityDef.hpp"
#include "Engine/StateMachine.hpp"
#include <SFML/System/Vector2.hpp>

namespace Engine {
  class Map;
  class Entity;
  class Character {
    public:
      Character(const Engine::CharacterDef& t_def, Engine::Map* t_map);

      const Engine::CharacterDef& m_def;
      sf::Vector2i m_direction = {0, 0};
      Engine::Map* m_map;
      std::shared_ptr<Engine::Entity> m_entity;
      std::shared_ptr<Engine::StateMachine> m_controller;
      std::unordered_map<std::string, std::shared_ptr<Engine::IState>> m_states;
      std::string m_default_state;
      std::unordered_map<std::string, std::vector<int>> m_anims;
  };
}
