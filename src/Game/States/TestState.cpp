#include "TestState.hpp"

TestState::TestState(std::shared_ptr<Engine::StateStack> t_stack) {
  LOG_TRACE("TestState::TestState()");

  auto app = &ComputerGame::instance();
  m_map = std::make_shared<Engine::Map>(*app, std::make_shared<Maps::TestMap>());

  // Temporary?
  std::vector<Engine::EntityDef> entities{{"monsters", 0, 0, 0, 0, 0, 0}};

  std::unordered_map<std::string, std::function<std::shared_ptr<Engine::IState> (void)>> character_states;
  character_states["wait"] = [this](){ return this->m_wait_state; };
  character_states["move"] = [this](){ return this->m_move_state; };

  m_bob = std::make_shared<Character>(
    std::make_shared<Engine::Entity>(*app, entities[0]),
    std::make_shared<Engine::StateMachine>(character_states)
  );
  m_wait_state = std::make_shared<WaitState>(m_bob, m_map);
  m_move_state = std::make_shared<MoveState>(m_bob, m_map);
  m_bob->m_controller->change("wait");
}

void TestState::teleport(std::shared_ptr<Engine::Entity> t_entity, std::shared_ptr<Engine::Map> t_map) {
  auto vec = t_map->tileToPixel(t_entity->m_tile_x, t_entity->m_tile_y);
  t_entity->m_sprite.setPosition(vec.x, vec.y);
}

bool TestState::update(float t_dt) {
  m_map->goTo((sf::Vector2i)m_bob->m_entity->m_sprite.getPosition());
  m_bob->m_controller->update(t_dt);

  return true;
}

void TestState::render(std::shared_ptr<Engine::Window> t_window) {
  m_map->render(t_window);
  m_bob->m_entity->render(t_window);
}

void TestState::handleInput(std::shared_ptr<Engine::Input> t_input) {
  m_bob->m_controller->handleInput(t_input);
  // teleport(bob, m_map);
  // LOG_DEBUG("new pos {},{}", pos.x, pos.y);
}

void TestState::enter(void) {
  LOG_TRACE("TestState::enter()");
}

void TestState::exit(void) {
  LOG_TRACE("TestState::exit()");
}
