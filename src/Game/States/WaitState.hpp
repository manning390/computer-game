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

    float m_frame_count = 0;
    float m_frame_reset_speed = 0.05;

    bool m_held = false;
    float m_held_timer = 0;
    const float m_held_delay = 0.125;

    void handleInput(std::shared_ptr<Engine::Input> t_input) override {
      if (t_input->isActionPressed(InputActions::LEFT)) {
        m_entity->m_start_frame = m_character->m_anim_left[0];
        m_entity->setFrame(m_entity->m_start_frame);
        m_character->m_direction = {-1, 0};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::RIGHT)) {
        m_entity->m_start_frame = m_character->m_anim_right[0];
        m_entity->setFrame(m_entity->m_start_frame);
        m_character->m_direction = {1, 0};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::UP)) {
        m_entity->m_start_frame = m_character->m_anim_up[0];
        m_entity->setFrame(m_entity->m_start_frame);
        m_character->m_direction = {0, -1};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::DOWN)) {
        m_entity->m_start_frame = m_character->m_anim_down[0];
        m_entity->setFrame(m_entity->m_start_frame);
        m_character->m_direction = {0, 1};
        m_held = true;
      } else {
        m_held = false;
        m_held_timer = 0;
      }
    };

    bool update(float t_dt) override {
      if (m_frame_count != -1) {
        m_frame_count += t_dt;
        if (m_frame_count >= m_frame_reset_speed) {
          m_frame_count = -1;
          m_entity->setFrame(m_entity->m_start_frame);
        }
      }

      if (m_held) {
        m_held_timer += t_dt;
        if (m_held_timer > m_held_delay) m_controller->change("move");
      }

      return true;
    };

    void enter() override {
      m_frame_count = 0;
    };

    // void exit(void) override { LOG_TRACE("WaitState::exit()");};
};
