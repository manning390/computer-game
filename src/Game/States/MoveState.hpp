#pragma once

#include "Engine/Tween.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"

#include "Game/States/EmptyState.hpp"
#include "Game/Character.hpp"
#include <SFML/System/Vector2.hpp>

struct MoveStateEnterParams {
  MoveStateEnterParams(int t_x, int t_y)
    : x(t_x), y(t_y) {};

  int x;
  int y;
};

class MoveState : public Engine::IState {
  public:
    MoveState(std::shared_ptr<Character> t_char, std::shared_ptr<Engine::Map> t_map);
    ~MoveState(void) override = default;

    std::shared_ptr<Character> m_character;
    std::shared_ptr<Engine::Map> m_map;
    std::shared_ptr<Engine::Entity> m_entity;
    std::shared_ptr<Engine::StateMachine> m_controller;

    uint m_tile_width = 0;
    sf::Vector2i m_movement = {0, 0};
    sf::Vector2f m_pixel_pos = {0, 0};
    float m_move_speed = 0.3;

    bool update(float t_dt) override;
    void render(std::shared_ptr<Engine::Window>) override {};
    void handleInput(std::shared_ptr<Engine::Input>) override {};

    void enter(MoveStateEnterParams t_data);
    void enter() override {};
    void exit() override;

  protected:
    std::unique_ptr<Engine::Tween> m_tween;
};
