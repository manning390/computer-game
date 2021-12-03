#include "TestState.hpp"

TestState::TestState(std::shared_ptr<Engine::StateStack> t_stack) {
  LOG_TRACE("TestState::TestState()");

  m_map = std::make_shared<Engine::Map>(ComputerGame::instance(), std::make_shared<Maps::TestMap>());
  m_map->goToTile(49, 49);

  std::shared_ptr<Engine::Tileset> monsters_tileset = ComputerGame::instance().getTileset("monsters");
  bob = sf::Sprite(
    *ComputerGame::instance().getTexture("monsters"),
    monsters_tileset->uvs[1]
  );
  jim = sf::Sprite(
    *ComputerGame::instance().getTexture("monsters"),
    monsters_tileset->uvs[1]
  );
  bob.setPosition(m_map->tileToPixel(0, 0));
  jim.setPosition(m_map->tileToPixel(99, 99));
}

bool TestState::update(float t_dt) {
  return true;
}

void TestState::render(std::shared_ptr<Engine::Window> t_window) {
  m_map->render(t_window);
  t_window->draw(bob);
  t_window->draw(jim);
}

void TestState::handleInput(std::shared_ptr<Engine::Input> t_input) {
  if (t_input->isActionJustPressed(InputActions::A)) {
    auto mouse_pos = t_input->getMousePosition();
    LOG_TRACE("YAY! {},{} i: {}", mouse_pos.x, mouse_pos.y, t_input->getBitmask().to_string());
  }
}

void TestState::enter(void) {
  LOG_TRACE("TestState::enter()");
}

void TestState::exit(void) {
  LOG_TRACE("TestState::exit()");
}
