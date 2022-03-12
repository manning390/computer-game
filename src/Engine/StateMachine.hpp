#pragma once

#include <functional>

#include "IState.hpp"
#include "Window.hpp"
#include "EmptyState.hpp"

namespace Engine {
  class StateMachine {
    public:
      StateMachine(std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states);
      // StateMachine(std::unordered_map<std::string, std::shared_ptr<Engine::IState>> t_states);

      template<typename T>
      void change(std::string t_state_key, T t_enter_params) {
        LOG_TRACE("Engine::StateMachine::change(\"{}\", ...)", t_state_key);
        auto state = m_states.find(t_state_key);
        if (state == m_states.end()) {
          LOG_ERROR("{} is not a valid state", t_state_key);
          std::exit(1);
        }

        // LOG_DEBUG("StateMachine: change -> {}", t_state_key);

        m_current->exit();
        m_current = (state->second)();
        // m_current = state->second;
        m_current->enter<T>(t_enter_params);
      }
      void change(std::string t_state_key);

      void update(float t_dt);
      void render(std::shared_ptr<Engine::Window> t_window);
      void handleInput(std::shared_ptr<Engine::Input> t_input);

    protected:
      /**
       * @brief The current running state
       */
      std::shared_ptr<Engine::IState> m_current = std::make_shared<Engine::EmptyState>();

      std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> m_states;
  };
}
