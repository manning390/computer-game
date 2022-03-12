#include "StateStack.hpp"

void Engine::StateStack::push(std::shared_ptr<Engine::IState> t_state) {
  m_states.push_back(t_state);
  t_state->enter();
}

std::shared_ptr<Engine::IState> Engine::StateStack::pop(void) {
  auto state = m_states.back();
  m_states.pop_back();
  state->exit();
  return state;
}

std::shared_ptr<Engine::IState> Engine::StateStack::top(void) {
  return m_states.back();
}

void Engine::StateStack::handleInput(std::shared_ptr<Engine::Input> t_input) {
  if (!m_states.empty()) {
    m_states.back()->handleInput(t_input);
  }
}

void Engine::StateStack::update(float t_dt) {
  // Update each state until one starts blocking
  for (auto i_state = m_states.rbegin(); i_state != m_states.rend(); ++i_state) {
    if (!((*i_state)->update(t_dt))) {
      break;
    }
  }
}

void Engine::StateStack::render(std::shared_ptr<Engine::Window> t_window) {
  for (auto i_state = m_states.rbegin(); i_state != m_states.rend(); ++i_state) {
    (*i_state)->render(t_window);
  }
}

bool Engine::StateStack::isEmpty() {
  return m_states.empty();
}
