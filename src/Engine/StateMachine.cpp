#include "StateMachine.hpp"

// Engine::StateMachine::StateMachine(
    // std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states)
  // : m_states(t_states) {};
Engine::StateMachine::StateMachine(
    std::unordered_map<std::string, std::shared_ptr<Engine::IState>> t_states)
  : m_states(t_states) {};

template<typename T>
void Engine::StateMachine::change(std::string t_state_key, T t_enter_params) {
  auto state = m_states.find(t_state_key);
  if (state == m_states.end()) {
    LOG_ERROR("{} is not a valid state", t_state_key);
    std::exit(1);
  }

  LOG_DEBUG("StateMachine: change -> {}", t_state_key);
  if (m_current != nullptr)
    m_current->exit();
  // m_current = (state->second)();
  m_current = state->second;
  m_current->enter(t_enter_params);
}

// void Engine::StateMachine::change(std::string t_state_key) {
  // auto state = m_states.find(t_state_key);
  // if (state == m_states.end()) {
    // LOG_ERROR("{} is not a valid state", t_state_key);
    // std::exit(1);
  // }

  // LOG_DEBUG("StateMachine: change -> {}", t_state_key);
  // if (m_current != nullptr)
    // m_current->exit();
  // // m_current = (state->second)();
  // m_current = state->second;
  // m_current->enter();
// }

void Engine::StateMachine::update(float t_dt) {
  m_current->update(t_dt);
}

void Engine::StateMachine::render(std::shared_ptr<Engine::Window> t_window) {
  m_current->render(t_window);
}

