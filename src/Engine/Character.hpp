#pragma once

#include <cassert>

#include "Engine/Application.hpp"
#include "Engine/EntityDef.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include <SFML/System/Vector2.hpp>

namespace Engine {
  class Character : public std::enable_shared_from_this<Character> {
    public:
      Character(Engine::Application& t_app, const Engine::CharacterDef& t_def, std::shared_ptr<Engine::Map> t_map);
      // Character(std::shared_ptr<Engine::Entity> t_entity, std::shared_ptr<Engine::StateMachine> t_controller)
        // : m_entity(t_entity), m_controller(t_controller) {};

      sf::Vector2i m_direction = {0, 0};
      std::shared_ptr<Engine::Map> m_map;
      std::shared_ptr<Engine::Entity> m_entity;
      std::shared_ptr<Engine::StateMachine> m_controller;
      std::unordered_map<std::string, std::shared_ptr<Engine::IState>> m_states;
      std::unordered_map<std::string, std::vector<int>> m_anims;
  };
}
