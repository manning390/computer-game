#pragma once

#include <functional>

#include "IState.hpp"
#include "Window.hpp"

namespace Engine {
  class StateMachine {
    public:
      // StateMachine(std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states);
      StateMachine(std::unordered_map<std::string, std::shared_ptr<Engine::IState>> t_states);

      template<class T>
      void change(std::string t_state_key, T t_enter_params);
      // Overloading because sometimes we want to pass nothing? There's probably a better way to write this
      // void change(std::string t_state_key);

      void update(float t_dt);

      void render(std::shared_ptr<Engine::Window> t_window);

    protected:
      /**
       * @brief The current running state
       */
      std::shared_ptr<Engine::IState> m_current;

      // std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> m_states;
      std::unordered_map<std::string, std::shared_ptr<Engine::IState>> m_states;
  };
}
