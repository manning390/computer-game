#include "Input.hpp"

Engine::Input::Input(std::vector<ActionBinding> t_action_bindings) : m_action_bindings(t_action_bindings) {};

void Engine::Input::update() {
  m_last_frame_keys.setMask(m_current_frame_keys);

  for (auto & i_action_binding : m_action_bindings) {
    m_current_frame_keys.setBit(i_action_binding.id, isActionBindingPressed(i_action_binding));
  }
}

bool Engine::Input::isActionBindingPressed(Engine::ActionBinding t_action_binding) {
  return isBindingPressed(t_action_binding.event_types.first, t_action_binding.bindings.first) ||
    (t_action_binding.bindings.second > -1 && isBindingPressed(t_action_binding.event_types.second, t_action_binding.bindings.second));
}

bool Engine::Input::isBindingPressed(Engine::EventType t_type, uint t_keycode) {
  switch(t_type) {
    case Engine::EventType::Keyboard:
      return sf::Keyboard::isKeyPressed((sf::Keyboard::Key) t_keycode);
    case Engine::EventType::Mouse:
      return sf::Mouse::isButtonPressed((sf::Mouse::Button) t_keycode);
    default:
      return false;
  }
}

// Is the action held down
bool Engine::Input::isActionPressed(uint t_action) {
  return m_current_frame_keys.getBit(t_action);
}

// Is this the first frame the action is held down
bool Engine::Input::isActionJustPressed(uint t_action) {
  bool last_frame = m_last_frame_keys.getBit(t_action);
  bool this_frame = m_current_frame_keys.getBit(t_action);
  return !last_frame && this_frame;
}

// Is this the first frame the action is released
bool Engine::Input::isActionJustReleased(uint t_action) {
  bool last_frame = m_last_frame_keys.getBit(t_action);
  bool this_frame = m_current_frame_keys.getBit(t_action);
  return last_frame && !this_frame;
}


std::vector<Engine::ActionBinding> Engine::Input::getActionBindings(void) {
  return m_action_bindings;
}

void Engine::Input::setActionBindings(std::vector<ActionBinding> t_action_bindings) {
  m_action_bindings = t_action_bindings;
}

Engine::ActionBinding Engine::Input::getActionBinding(uint t_action) {
  return m_action_bindings[t_action];
}

void Engine::Input::setActionBinding(ActionBinding t_action_binding) {
  m_action_bindings[t_action_binding.id] = t_action_binding;
}
