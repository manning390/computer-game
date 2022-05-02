#include "StateMachine.hpp"

Engine::StateMachine::StateMachine(
    std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> t_states)
  : m_states(t_states) {};


void Engine::StateMachine::handleInput(std::shared_ptr<Engine::Input> t_input) {
  m_current->handleInput(t_input);
};

void Engine::StateMachine::update(float t_dt) {
  m_current->update(t_dt);
}

void Engine::StateMachine::render(std::shared_ptr<Engine::Window> t_window) {
  m_current->render(t_window);
}

