#include "Input.hpp"

Engine::ActionBinding::ActionBinding(uint t_id, Engine::EventType t_event_type, int t_binding) {
  id = t_id;
  event_types = std::make_pair(t_event_type, Engine::EventType::Unknown);
  bindings = std::make_pair(t_binding, sf::Keyboard::Unknown);
}

Engine::ActionBinding::ActionBinding(uint t_id, Engine::EventType t_event_type_1, int t_binding_1,
                                                Engine::EventType t_event_type_2, int t_binding_2) {
  id = t_id;
  event_types = std::make_pair(t_event_type_1, t_event_type_2);
  bindings = std::make_pair(t_binding_1, t_binding_2);
}

Engine::Input::Input(std::vector<ActionBinding> t_action_bindings, std::shared_ptr<Engine::Window> t_window)
  : m_action_bindings(t_action_bindings), m_window(t_window) {};

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

bool Engine::Input::isBindingPressed(Engine::EventType t_type, int t_keycode) {
  switch(t_type) {
    case Engine::EventType::Keyboard:
      return sf::Keyboard::isKeyPressed((sf::Keyboard::Key) t_keycode);
    case Engine::EventType::Mouse:
      return sf::Mouse::isButtonPressed((sf::Mouse::Button) t_keycode);
    default:
      return false;
  }
}

sf::Vector2i Engine::Input::getMousePosition() const {
  auto window = m_window->getNativeWindow();
  auto coord  = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
  auto view   = window->getView().getSize();
  // return sf::Vector2i(coord.x - (view.x / 2.0), coord.y - (view.y / 2.0));
  return sf::Vector2i(coord.x, coord.y);
}

sf::Vector2i Engine::Input::getViewMousePosition() const {
  return sf::Mouse::getPosition(*m_window->getNativeWindow());
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

Engine::Bitmask Engine::Input::getBitmask() {
  return m_current_frame_keys;
}

std::vector<Engine::ActionBinding> Engine::Input::getBindings() {
  return m_action_bindings;
}
