#pragma once

#include "Engine/IState.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"
#include "Engine/EmptyState.hpp"

#include "Game/Character.hpp"
#include "Game/InputActions.hpp"
#include "Game/States/MoveState.hpp"
#include "SFML/System/Vector2.hpp"

class WaitState : public Engine::EmptyState {
  public:
    WaitState(std::shared_ptr<Character> t_char, std::shared_ptr<Engine::Map> t_map) :
      m_character(t_char),
      m_map(t_map),
      m_entity(t_char->m_entity),
      m_controller(t_char->m_controller) {};

    std::shared_ptr<Character> m_character;
    std::shared_ptr<Engine::Map> m_map;
    std::shared_ptr<Engine::Entity> m_entity;
    std::shared_ptr<Engine::StateMachine> m_controller;

    void handleInput(std::shared_ptr<Engine::Input> t_input) override {
      if (t_input->isActionPressed(InputActions::LEFT)) {
        m_character->m_direction = {-1, 0};
        m_controller->change("move");
        return;
      }
      if (t_input->isActionPressed(InputActions::RIGHT)) {
        m_character->m_direction =  {1, 0};
        m_controller->change("move");
        return;
      }
      if (t_input->isActionPressed(InputActions::UP)) {
        m_character->m_direction = {0, -1};
        m_controller->change("move");
        return;
      }
      if (t_input->isActionPressed(InputActions::DOWN)) {
        m_character->m_direction =  {0, 1};
        m_controller->change("move");
        return;
      }
    };

    // void exit(void) override { LOG_TRACE("WaitState::exit()");};
};