#include "Application.hpp"

Application& Application::instance(void) {
  // std::cout << "Application::instance()" << std::endl;
  static Application m_instance;
  return m_instance;
}

void Application::processArguments([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
  // Might do stuff here later
  // LOG_TRACE("Application::processArguments()");
}

void Application::init() {
  LOG_TRACE("Application::init()");

  // Create window
  m_window = std::make_shared<Engine::Window>();
  m_frame_time = sf::seconds(1.0f / m_window->getFps());

  // Initiate the state stack
  m_stack = std::make_shared<Engine::StateStack>();

  // Seed random?
  // Load assets
  loadTextures();
  loadTilesets();
}

void Application::quit() {
  m_running = false;
}

int Application::run() {
  // Setup anything that we need setup
  init();

  // Throw our first state on the stack
  m_stack->push(std::make_shared<TestState>(m_stack));

  // Run loop
  loop();

  return Engine::NoError;
}

void Application::loop() {
  LOG_TRACE("Application::loop()");

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
    m_stack->handleInput(m_event);

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

void Application::loadTilesets() {
 LOG_TRACE("Application::loadTilesets()");

  auto lines = Helper::getFileLines("assets/manifests/tilesets.manifest");
  for (auto it = lines.begin(); it < lines.end(); it++) {
    std::string file_path = *it;

    // Instead of the manifest key, lets use what's in the tileset
    auto tileset = std::make_shared<Engine::Tileset>(Engine::Tileset(file_path));

    LOG_INFO("Loaded tileset {} -> {}", file_path, tileset->id);

    m_tilesets[tileset->id] = tileset;
  }
}

void Application::loadTextures() {
  LOG_TRACE("Application::loadTextures()");

  auto lines = Helper::getFileLines("assets/manifests/textures.manifest");
  for (auto it = lines.begin(); it < lines.end(); it++) {
    std::istringstream iss(*it);
    std::string key, file_path;
    iss >> key >> file_path;

    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(file_path);

    LOG_INFO("Loaded texture: {} -> {}", file_path, key);

    m_textures[key] = texture;
  }
}

std::shared_ptr<sf::Texture> Application::getTexture(std::string t_key) {
  // LOG_TRACE("Application::getTexture({})", t_key);

  auto tex = m_textures.find(t_key);
  return tex != m_textures.end() ? tex->second : nullptr;
}

std::shared_ptr<Engine::Tileset> Application::getTileset(std::string t_key) {
  // LOG_TRACE("Application::getTileset({})", t_key);

  auto tileset = m_tilesets.find(t_key);
  return tileset != m_tilesets.end() ? tileset->second : nullptr;
}
