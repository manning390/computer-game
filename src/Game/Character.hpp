#pragma once

#include "Engine/Entity.hpp"
#include "Engine/StateMachine.hpp"

struct Character {
  Character(std::shared_ptr<Engine::Entity> t_entity, std::shared_ptr<Engine::StateMachine> t_controller)
    : m_entity(t_entity), m_controller(t_controller) {};

  std::shared_ptr<Engine::Entity> m_entity;
  std::shared_ptr<Engine::StateMachine> m_controller;
};

