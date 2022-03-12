#pragma once

#include "Engine/Entity.hpp"
#include "Engine/IState.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"

#include "Game/Character.hpp"

class EmptyState : public Engine::IState {
  public:
    EmptyState(void) = default;
    ~EmptyState(void) override = default;

    bool update(float) override { return true; };
    void render(std::shared_ptr<Engine::Window>) override {};
    void handleInput(std::shared_ptr<Engine::Input>) override {};

    void enter(void) override {};
    void exit(void) override {};
};
