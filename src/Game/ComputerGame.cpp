#include "ComputerGame.hpp"

ComputerGame& ComputerGame::instance(void) {
  // std::cout << "Application::instance()" << std::endl;
  static ComputerGame m_instance;
  return m_instance;
}

void ComputerGame::init(void) {
  // Is this the best place for this?
  m_default_bindings = {
    Engine::ActionBinding(InputActions::UP,     Engine::EventType::Keyboard, (uint)sf::Keyboard::W),
    Engine::ActionBinding(InputActions::LEFT,   Engine::EventType::Keyboard, (uint)sf::Keyboard::A),
    Engine::ActionBinding(InputActions::RIGHT,  Engine::EventType::Keyboard, (uint)sf::Keyboard::S),
    Engine::ActionBinding(InputActions::DOWN,   Engine::EventType::Keyboard, (uint)sf::Keyboard::D),
    Engine::ActionBinding(InputActions::A,      Engine::EventType::Keyboard, (uint)sf::Keyboard::Space),
    Engine::ActionBinding(InputActions::B,      Engine::EventType::Keyboard, (uint)sf::Keyboard::BackSpace),
    Engine::ActionBinding(InputActions::START,  Engine::EventType::Keyboard, (uint)sf::Keyboard::Z),
    Engine::ActionBinding(InputActions::SELECT, Engine::EventType::Keyboard, (uint)sf::Keyboard::X),
  };

  Application::init();
}

void ComputerGame::createInitialState() {
  m_stack->push(std::make_shared<TestState>(m_stack));
}

