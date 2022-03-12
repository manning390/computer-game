#pragma once

#include <memory>
#include <vector>

#include "Window.hpp"
#include "Input.hpp"
#include "IState.hpp"

namespace Engine {
  class IState;
  class StateStack {
    public:

      /**
       * @brief Construct a new StateStack object
       *
       */
      StateStack(void) = default;

      /**
       * @brief Puts a state on top of the stack and runs enter
       *
       */
      void push(std::shared_ptr<Engine::IState> t_state);

      /**
       * @brief Removes the top state on the stack, runs exit, and returns it
       *
       */
      std::shared_ptr<Engine::IState> pop(void);

      /**
       * @brief Returns the top state on the stack
       *
       */
      std::shared_ptr<Engine::IState> top(void);

      /**
       * @brief Runs the handle input function for the state on top of the stack
       *
       * @param t_event the event off the top of the event queue this frame
       */
      void handleInput(std::shared_ptr<Engine::Input> t_input);

      /**
       * @brief Runs through the stack in decending order and calls state update()
       *
       * @param t_dt the delta time between last frame
       */
      void update(float t_dt);

      /**
       * @brief Runs through the stack in decending order and calls each state render() method
       *
       * @param t_window the window reference for drawing
       */
      void render(std::shared_ptr<Engine::Window> t_window);

      /**
       * @brief Tells if there is any state in the stack or not
       *
       * @return True The stack is empty
       * @return False The stack has state running
       */
      bool isEmpty(void);

    protected:
      /**
       * @brief The data structure holding the states
       *
       */
      std::vector<std::shared_ptr<Engine::IState>> m_states;
  };
} // namespace Engine
