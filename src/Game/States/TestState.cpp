#include "TestState.hpp"

TestState::TestState(std::shared_ptr<Engine::StateStack> t_stack) {
  LOG_TRACE("TestState::TestState()");

  auto app = ComputerGame::instance();
  m_map = std::make_shared<Engine::Map>(*app, std::make_shared<Maps::TestMap>());
  m_map->centerMapInView();

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
  m_bob->m_entity->setTilePos(1, 1, m_map);
  m_map->m_triggers[m_map->coordToIndex(2,  2)] = std::make_shared<Engine::Trigger>(Actions::Teleport(m_map, 2, 12));
  m_map->m_triggers[m_map->coordToIndex(2, 12)] = std::make_shared<Engine::Trigger>(Actions::Teleport(m_map, 2,  2));
  m_map->goToTile(1, 1);
}


bool TestState::update(float t_dt) {
  m_bob->m_controller->update(t_dt);
  // m_map->goTo((sf::Vector2i)m_bob->m_entity->m_sprite.getPosition());

  return true;
}

void TestState::render(std::shared_ptr<Engine::Window> t_window) {
  m_map->render(t_window);
  m_bob->m_entity->render(t_window);
}

void TestState::handleInput(std::shared_ptr<Engine::Input> t_input) {
  m_bob->m_controller->handleInput(t_input);

  // Debug to refresh atlas
  if (t_input->isActionJustPressed(InputActions::DEBUG1)) {
    m_map->setAtlas(std::make_shared<Maps::TestMap>());
    LOG_DEBUG("Refreshed Atlas");
  }

  // Debug to get mouse tile pos
  if (t_input->isActionJustPressed(InputActions::DEBUG2)) {
    auto tile_pos = m_map->pixelToTile((sf::Vector2f)t_input->getMousePosition());
    LOG_DEBUG("tile {},{} -> {}", tile_pos.x, tile_pos.y, tile_pos.y * m_map->getSizeT().x + tile_pos.x);
  }

  if (t_input->isActionJustPressed(InputActions::A)) {
    auto facing = m_bob->m_entity->getTilePos() + m_bob->m_direction;
    auto trigger = m_map->m_triggers[m_map->coordToIndex(facing.x, facing.y, m_bob->m_entity->m_layer)];
    if (trigger) trigger->m_on_use(trigger, m_bob->m_entity);
  }
}

void TestState::enter(void) {
  LOG_TRACE("TestState::enter()");
}

void TestState::exit(void) {
  LOG_TRACE("TestState::exit()");
}
