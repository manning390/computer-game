#include "ComputerGame.hpp"

ComputerGame& ComputerGame::instance(void) {
  // std::cout << "Application::instance()" << std::endl;
  static ComputerGame m_instance;
  return m_instance;
}

void ComputerGame::init(void) {
  // Is this the best place for this?
  m_default_bindings = {
    Engine::ActionBinding(InputActions::UP,     Engine::EventType::Keyboard, sf::Keyboard::F),
    Engine::ActionBinding(InputActions::LEFT,   Engine::EventType::Keyboard, sf::Keyboard::W),
    Engine::ActionBinding(InputActions::RIGHT,  Engine::EventType::Keyboard, sf::Keyboard::P),
    Engine::ActionBinding(InputActions::DOWN,   Engine::EventType::Keyboard, sf::Keyboard::S),
    Engine::ActionBinding(InputActions::A,      Engine::EventType::Keyboard, sf::Keyboard::Space,
                                                Engine::EventType::Keyboard, sf::Keyboard::A),
    Engine::ActionBinding(InputActions::B,      Engine::EventType::Keyboard, sf::Keyboard::BackSpace),
    Engine::ActionBinding(InputActions::START,  Engine::EventType::Keyboard, sf::Keyboard::Z),
    Engine::ActionBinding(InputActions::SELECT, Engine::EventType::Keyboard, sf::Keyboard::X),
  };

  Application::init();
}

void ComputerGame::createInitialState() {
  m_stack->push(std::make_shared<TestState>(m_stack));
}

