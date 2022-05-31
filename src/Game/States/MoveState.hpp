#pragma once

#include "Engine/Animation.hpp"
#include "Engine/Character.hpp"
#include "Engine/EmptyState.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Trigger.hpp"
#include "Engine/Tween.hpp"
#include "Engine/Window.hpp"

#include <SFML/System/Vector2.hpp>

class MoveState : public Engine::EmptyState {
  public:
    MoveState(Engine::Character* t_char, std::shared_ptr<Engine::Map> t_map)
      : m_char(t_char),
        m_map(t_map)//,
        // m_anim(std::make_unique<Engine::Animation>(std::vector<int>(t_char->m_entity->m_start_frame)))
  {};
    ~MoveState(void) override = default;

    // Time to move 1 square in seconds
    const float m_move_speed = (1 - 0.7);

    Engine::Character* m_char;
    std::shared_ptr<Engine::Map> m_map;

    sf::Vector2i m_movement  = {0, 0};
    sf::Vector2f m_pixel_pos = {0, 0};

    bool update(float t_dt) override;

    void enter() override;
    void exit() override;

  protected:
    std::unique_ptr<Engine::Tween> m_tween;
    std::unique_ptr<Engine::Animation> m_anim;
};
