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
    EmptyState();
    bool update() { return false; };
    void render() {};
    void handleInput() {};

    void enter(void) override {};
    void exit(void) override {};
};
