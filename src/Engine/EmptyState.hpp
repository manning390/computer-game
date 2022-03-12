#pragma once

#include "Entity.hpp"
#include "IState.hpp"
#include "Input.hpp"
#include "Map.hpp"
#include "StateMachine.hpp"
#include "Window.hpp"

namespace Engine {
  class EmptyState : public IState {
    public:
      EmptyState(void) = default;
      ~EmptyState(void) override = default;

      bool update(float) override { return true; };
      void render(std::shared_ptr<Engine::Window>) override {};
      void handleInput(std::shared_ptr<Engine::Input>) override {};

      template<typename T>
      void enter(T) {}

      void enter(void) override {};
      void exit(void) override {};
  };
}
