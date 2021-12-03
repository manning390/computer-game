#pragma once

#include <memory>

#include "Window.hpp"
#include "Input.hpp"

namespace Engine {
  class StateStack;
  class IState {
    public:
      virtual ~IState(void) { };
      /**
       * @brief runs on update step of each frame
       *
       * @param t_dt the delta time between last frame
       *
       * @return True continue running states after this one
       * @return False this state is blocking, abort the update step
       */
      virtual bool update(float t_dt) = 0;

      /**
       * @brief runs on the render step of each frame
       *
       * @param t_window the reference to the window
       */
      virtual void render(std::shared_ptr<Engine::Window> t_window) = 0;

      /**
       * @brief runs after the update step before the render step
       *
       */
      virtual void handleInput(std::shared_ptr<Engine::Input> t_input) = 0;

      /**
       * @brief runs when the state is entered
       */
      virtual void enter(void) = 0;

      /**
       * @brief runs when the state is exited
       */
      virtual void exit(void) = 0;

    protected:
      std::shared_ptr<Engine::StateStack> m_stack;
  };
} // Namespace Engine
