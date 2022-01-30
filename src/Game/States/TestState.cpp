#include "TestState.hpp"

TestState::TestState(std::shared_ptr<Engine::StateStack> t_stack) {
  LOG_TRACE("TestState::TestState()");

  auto app = &ComputerGame::instance();
  m_map = std::make_shared<Engine::Map>(*app, std::make_shared<Maps::TestMap>());

  std::shared_ptr<Engine::Tileset> monsters_tileset = app->getTileset("monsters");
  bob = sf::Sprite(
    *(app->getTexture("monsters")),
    monsters_tileset->uvs[1]
  );
  jim = sf::Sprite(
    *(app->getTexture("monsters")),
    monsters_tileset->uvs[1]
  );
  bob.setPosition(m_map->tileToPixel(0, 0));
  // jim.setPosition(m_map->tileToPixel(99, 99));
  jim.setPosition(app->m_window->getView().getCenter());
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
    m_map->goTo(t_input->getMousePosition());
  }
  auto pos = bob.getPosition();
  if (t_input->isActionJustPressed(InputActions::LEFT)) {
    bob.setPosition(pos + sf::Vector2f(-5, 0));
  }
  if (t_input->isActionJustPressed(InputActions::RIGHT)) {
    bob.setPosition(pos + sf::Vector2f(5, 0));
  }
  if (t_input->isActionJustPressed(InputActions::UP)) {
    bob.setPosition(pos + sf::Vector2f(0, -5));
  }
  if (t_input->isActionJustPressed(InputActions::DOWN)) {
    bob.setPosition(pos + sf::Vector2f(0, 5));
  }
  // LOG_DEBUG("new pos {},{}", pos.x, pos.y);
}

void TestState::enter(void) {
  LOG_TRACE("TestState::enter()");
}

void TestState::exit(void) {
  LOG_TRACE("TestState::exit()");
}
