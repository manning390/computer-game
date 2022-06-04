#pragma once

#include "Engine/Map.hpp"
#include "Engine/Character.hpp"
#include "Engine/EmptyState.hpp"

class PlanStrollState : public Engine::EmptyState {
  public:
    PlanStrollState(Engine::Character* t_char, Engine::Map*) :
      m_char(t_char) {};



    Engine::Character* m_char;

    void enter() override {
      m_frame_count = 0;
      m_count_down = Helper::random(1, 4);

      int frame;
      if (m_char->m_direction.x == 1) {
        frame = m_char->m_anims["right"][0];
      } else if (m_char->m_direction.x == -1) {
        frame = m_char->m_anims["left"][0];
      } else if (m_char->m_direction.y == -1) {
        frame = m_char->m_anims["up"][0];
      } else if (m_char->m_direction.y == 1) {
        frame = m_char->m_anims["down"][0];
      }
      m_char->m_entity->m_start_frame = frame;
    };

    bool update(float t_dt) override {
      m_count_down -= t_dt;
      if (m_count_down <= 0) {
        m_char->m_direction = pickRandomDirection();
        m_char->m_controller->change("move");
      }

      resetToFirstFrame(t_dt);

      return true;
    };

  private:
    float m_frame_reset_speed = 0.05f;
    float m_frame_count = 0;
    float m_count_down = Helper::random(1, 4);

    sf::Vector2i pickRandomDirection(void) const {
      switch(Helper::random(4)) {
        case 0:  return {-1,  0};
        case 1:  return { 1,  0};
        case 2:  return { 0, -1};
        default: return { 0,  1};
      }
    }

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
