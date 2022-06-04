#include "ComputerGame.hpp"
#include "States/TestState.hpp"
#include "Game/States/Character/WaitState.hpp"
#include "Game/States/Character/MoveState.hpp"
#include "Game/States/Character/NPCStandState.hpp"
#include "Game/States/Character/PlanStrollState.hpp"

ComputerGame* ComputerGame::s_instance = nullptr;

void ComputerGame::init(void) {
  LOG_TRACE("ComputerGame::init()");

  // Is this the best place for this?
  m_default_bindings = {
    Engine::ActionBinding(InputActions::DEBUG1,  Engine::EventType::Keyboard, sf::Keyboard::Num1),
    Engine::ActionBinding(InputActions::DEBUG2,  Engine::EventType::Keyboard, sf::Keyboard::Num2),

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

  m_state_factories = {
    {"wait", Engine::makeStateFactory<WaitState>()},
    {"move", Engine::makeStateFactory<MoveState>()},
    {"npc_stand", Engine::makeStateFactory<NPCStandState>()},
    {"npc_stroll", Engine::makeStateFactory<PlanStrollState>()}
  };

  Application::init();
}

void ComputerGame::createInitialState() {
  m_stack->push(std::make_shared<TestState>(m_stack));
}

