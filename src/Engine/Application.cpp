#include "Application.hpp"

void Engine::Application::processArguments([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
  // Might do stuff here later
  // LOG_TRACE("Engine::Application::processArguments()");
}

void Engine::Application::init() {
  LOG_TRACE("Engine::Application::init()");

  // Create window
  m_window = std::make_shared<Engine::Window>();
  m_frame_time = sf::seconds(1.0 / m_window->getFps());

  // Seed random?
  // Todo setup random

  // Load assets
  loadTextures();
  loadTilesets();

  // Load input
  loadBindings();

  // Initiate the state stack
  m_stack = std::make_shared<Engine::StateStack>();
}

void Engine::Application::quit() {
  m_running = false;
}

int Engine::Application::run() {
  // Setup anything that we need setup
  init();

  // Throw our first state on the stack
  createInitialState();

  // Run loop
  loop();

  return Engine::NoError;
}

void Engine::Application::loop() {
  LOG_TRACE("Engine::Application::loop()");

  sf::Time previous = m_clock.getElapsedTime();
  sf::Time lag = sf::Time::Zero;

  while(m_running && m_window->isOpen() && !m_stack->isEmpty())
  {
    sf::Time current = m_clock.getElapsedTime();
    sf::Time elapsed = current - previous;
    previous = current;
    lag += elapsed;

    // Process Input
    m_window->pollEvent(m_event);
    m_input->update();
    m_stack->handleInput(m_input);

    while (lag >= m_frame_time) {
      m_stack->update(m_frame_time.asSeconds());
      lag -= m_frame_time;
    }

    // Reset the window
    m_window->reset();

    // Render
    m_stack->render(m_window);

    // Display the new buffer
    m_window->display();
  }
}

void Engine::Application::loadTilesets() {
 LOG_TRACE("Engine::Application::loadTilesets()");

  auto lines = Helper::getFileLines(m_tilesets_manifest_path);
  for (auto line : lines) {
    std::string file_path = line;

    // Instead of the manifest key, lets use what's in the tileset
    auto tileset = std::make_shared<Engine::Tileset>(Engine::Tileset(file_path));

    LOG_INFO("Loaded tileset {} -> {}", file_path, tileset->id);

    m_tilesets[tileset->id] = tileset;
  }
}

void Engine::Application::loadTextures() {
  LOG_TRACE("Engine::Application::loadTextures()");

  auto lines = Helper::getFileLines(m_textures_manifest_path);
  for (auto line : lines) {
    std::istringstream iss(line);
    std::string key, file_path;
    iss >> key >> file_path;

    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(file_path);

    LOG_INFO("Loaded texture: {} -> {}", file_path, key);

    m_textures[key] = texture;
  }
}

std::shared_ptr<sf::Texture> Engine::Application::getTexture(std::string t_key) {
  // LOG_TRACE("Engine::Application::getTexture({})", t_key);

  auto tex = m_textures.find(t_key);
  return tex != m_textures.end() ? tex->second : nullptr;
}

std::shared_ptr<Engine::Tileset> Engine::Application::getTileset(std::string t_key) {
  // LOG_TRACE("Engine::Application::getTileset({})", t_key);

  auto tileset = m_tilesets.find(t_key);
  return tileset != m_tilesets.end() ? tileset->second : nullptr;
}

void Engine::Application::loadBindings() {
  LOG_TRACE("Engine::Application::loadBindings()");

  m_input = std::make_shared<Engine::Input>(m_default_bindings, m_window);
  // auto lines = Helper::getFileLines(m_bindings_path);

  // // File exists? Load it
  // // File doesn't exist, use defaults
  // uint action = 0;
  // for (auto line : lines) {
    // std::istringstream iss(line);
    // std::

    // ++action;
  // }
}

