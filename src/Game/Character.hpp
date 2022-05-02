#pragma once

#include "Engine/Entity.hpp"
#include "Engine/StateMachine.hpp"
#include <SFML/System/Vector2.hpp>

struct Character {
  Character(std::shared_ptr<Engine::Entity> t_entity, std::shared_ptr<Engine::StateMachine> t_controller)
    : m_entity(t_entity), m_controller(t_controller) {};

  sf::Vector2i m_direction = {0, 0};
  std::shared_ptr<Engine::Entity> m_entity;
  std::shared_ptr<Engine::StateMachine> m_controller;

  std::vector<int> m_anim_right = {0, 4};
  std::vector<int> m_anim_down  = {1, 5};
  std::vector<int> m_anim_up    = {2, 6};
  std::vector<int> m_anim_left  = {3, 7};

};

