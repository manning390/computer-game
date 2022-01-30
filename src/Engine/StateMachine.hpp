#pragma once

#include <functional>

#include "IState.hpp"
#include "Window.hpp"

namespace Engine {
  class StateMachine {
    public:
      StateMachine(std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states);

      template<class T>
      void change(std::string t_state_key, T t_enter_params);

      void update(float t_dt);

      void render(std::shared_ptr<Engine::Window> t_window);

    protected:
      /**
       * @brief A 'hash map' containing lamda functions that create the state
       *
       */
      std::shared_ptr<Engine::IState> m_current;
      std::unordered_map<std::string, std::function<Engine::IState (void)>> m_states;
  };
}
