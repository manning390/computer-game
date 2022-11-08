#include "TestState.hpp"

TestState::TestState(std::shared_ptr<Engine::StateStack> t_stack) {
  LOG_TRACE("TestState::TestState()");

  auto& app = *ComputerGame::instance();
  m_map = std::make_shared<Engine::Map>(app, std::make_shared<Maps::TestMap>());
  // m_map->centerMapInView();
  m_hero = std::make_shared<Engine::Character>(app.getCharacter("hero"), m_map.get());
  m_hero->m_entity->setTilePos(
    m_hero->m_entity->m_tile_x,
    m_hero->m_entity->m_tile_y,
    m_hero->m_entity->m_layer,
    m_map.get());

  auto EFn = Actions::EmptyFn;
  m_map->m_triggers[m_map->coordToIndex(2,  2)] = std::make_shared<Engine::Trigger>(Actions::Teleport(m_map.get(), 2, 12));
  m_map->m_triggers[m_map->coordToIndex(2, 12)] = std::make_shared<Engine::Trigger>(Actions::Teleport(m_map.get(), 2,  2));
  m_map->m_triggers[m_map->coordToIndex(2,  9)] = std::make_shared<Engine::Trigger>(EFn, EFn, [](std::shared_ptr<Engine::Trigger>, std::shared_ptr<Engine::Entity>){
    LOG_WARN("There's a chest here!");
  });
  // m_map->goToTile(1, 1);
}


bool TestState::update(float t_dt) {
  m_hero->m_controller->update(t_dt);
  m_map->update(t_dt);
  // m_npc->m_controller->update(t_dt);
  // m_map->goTo((sf::Vector2i)m_bob->m_entity->m_sprite.getPosition());

  return true;
}

void TestState::render(std::shared_ptr<Engine::Window> t_window) {
  m_map->render(t_window, m_hero->m_entity);
}

void TestState::handleInput(std::shared_ptr<Engine::Input> t_input) {
  m_hero->m_controller->handleInput(t_input);

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
    auto facing = m_hero->m_entity->getTilePos() + m_hero->m_direction;
    auto trigger = m_map->m_triggers[m_map->coordToIndex(facing.x, facing.y, m_hero->m_entity->m_layer)];
    if (trigger) trigger->m_on_use(trigger, m_hero->m_entity);
  }
}

void TestState::enter(void) {
  LOG_TRACE("TestState::enter()");
}

void TestState::exit(void) {
  LOG_TRACE("TestState::exit()");
}
