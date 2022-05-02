#pragma once

#include "Engine/Tween.hpp"
#include "Engine/Animation.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"
#include "Engine/EmptyState.hpp"

#include "Game/Character.hpp"

#include <SFML/System/Vector2.hpp>

#define MOVE_STATE_PARAM_ID 1

class MoveState : public Engine::EmptyState {
  public:
    MoveState(std::shared_ptr<Character> t_char, std::shared_ptr<Engine::Map> t_map)
      : m_character(t_char),
        m_map(t_map),
        m_entity(t_char->m_entity),
        m_controller(t_char->m_controller) {
          m_anim = std::make_unique<Engine::Animation>(std::vector<int>(t_char->m_entity->m_start_frame));
        };
    ~MoveState(void) override = default;

    // Time to move 1 square in seconds
    const float m_move_speed = (1 - 0.7);

    std::shared_ptr<Character> m_character;
    std::shared_ptr<Engine::Map> m_map;
    std::shared_ptr<Engine::Entity> m_entity;
    std::shared_ptr<Engine::StateMachine> m_controller;

    sf::Vector2i m_movement = {0, 0};
    sf::Vector2f m_pixel_pos = {0, 0};

    bool update(float t_dt) override;

    void enter() override;
    void exit() override;

  protected:
    std::unique_ptr<Engine::Tween> m_tween;
    std::unique_ptr<Engine::Animation> m_anim;
};
