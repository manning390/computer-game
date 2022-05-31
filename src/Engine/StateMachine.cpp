#include "StateMachine.hpp"

Engine::StateMachine::StateMachine(
    std::unordered_map<std::string, std::shared_ptr<Engine::IState>>& t_states)
  : m_states(t_states) {};

void Engine::StateMachine::change(std::string t_state_key) {
  // LOG_TRACE("Engine::StateMachine::change(\"{}\")", t_state_key);

  auto state = m_states.find(t_state_key);
  if (state == m_states.end()) {
    LOG_ERROR("{} is not a valid state", t_state_key);
    std::exit(1);
  }

  m_current->exit();
  m_current = state->second;
  m_current->enter();
};

void Engine::StateMachine::handleInput(std::shared_ptr<Engine::Input> t_input) {
  m_current->handleInput(t_input);
};

void Engine::StateMachine::update(float t_dt) {
  m_current->update(t_dt);
}

void Engine::StateMachine::render(std::shared_ptr<Engine::Window> t_window) {
  m_current->render(t_window);
}

