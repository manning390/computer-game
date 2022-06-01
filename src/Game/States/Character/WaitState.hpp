#pragma once

#include "Engine/IState.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"
#include "Engine/EmptyState.hpp"

#include "Engine/Character.hpp"
#include "Game/InputActions.hpp"
#include "SFML/System/Vector2.hpp"

class WaitState : public Engine::EmptyState {
  public:
    WaitState(Engine::Character* t_char, std::shared_ptr<Engine::Map> t_map) :
      m_char(t_char),
      m_map(t_map) {};

    Engine::Character* m_char;
    std::shared_ptr<Engine::Map> m_map;

    float m_frame_count = 0;
    float m_frame_reset_speed = 0.05;

    bool m_held = false;
    float m_held_timer = 0;
    const float m_held_delay = 0.125;

    void handleInput(std::shared_ptr<Engine::Input> t_input) override {
      auto& entity = m_char->m_entity;
      if (t_input->isActionPressed(InputActions::LEFT)) {
        entity->m_start_frame = m_char->m_anims["left"][0];
        entity->setFrame(entity->m_start_frame);
        m_char->m_direction = {-1, 0};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::RIGHT)) {
        entity->m_start_frame = m_char->m_anims["right"][0];
        entity->setFrame(entity->m_start_frame);
        m_char->m_direction = {1, 0};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::UP)) {
        entity->m_start_frame = m_char->m_anims["up"][0];
        entity->setFrame(entity->m_start_frame);
        m_char->m_direction = {0, -1};
        m_held = true;
      } else if (t_input->isActionPressed(InputActions::DOWN)) {
        entity->m_start_frame = m_char->m_anims["down"][0];
        entity->setFrame(entity->m_start_frame);
        m_char->m_direction = {0, 1};
        m_held = true;
      } else {
        m_held = false;
        m_held_timer = 0;
      }
    };

    bool update(float t_dt) override {
      resetToFirstFrame(t_dt);

      if (m_held) {
        m_held_timer += t_dt;
        if (m_held_timer > m_held_delay) m_char->m_controller->change("move");
      }

      return true;
    };

    void enter() override {
      m_frame_count = 0;
    };

    // void exit(void) override { LOG_TRACE("WaitState::exit()"); };

  private:
    void resetToFirstFrame(float t_dt) {
      if (m_frame_count != -1) {
        m_frame_count += t_dt;
        if (m_frame_count >= m_frame_reset_speed) {
          m_frame_count = -1;
          m_char->m_entity->setFrame(m_char->m_entity->m_start_frame);
        }
      }
    }
};
