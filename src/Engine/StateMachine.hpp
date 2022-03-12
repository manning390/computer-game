#pragma once

#include <functional>

#include "IState.hpp"
#include "Window.hpp"

namespace Engine {
  class StateMachine {
    public:
      // StateMachine(std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states);
      StateMachine(std::unordered_map<std::string, std::shared_ptr<Engine::IState>> t_states);

      template<typename T>
      void change(std::string t_state_key, T t_enter_params);
      void change(std::string t_state_key);

      void update(float t_dt);
      void render(std::shared_ptr<Engine::Window> t_window);
      void handleInput(std::shared_ptr<Engine::Input> t_input);

    protected:
      /**
       * @brief The current running state
       */
      std::shared_ptr<Engine::IState> m_current;

      // std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> m_states;
      std::unordered_map<std::string, std::shared_ptr<Engine::IState>> m_states;
  };
}
