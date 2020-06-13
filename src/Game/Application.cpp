#include "Application.hpp"

Application& Application::instance(void) {
  // std::cout << "Application::instance()" << std::endl;
  static Application m_instance;
  return m_instance;
}

void Application::processArguments([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
  // Might do stuff here later
}

void Application::init() {
  // std::cout << "Application::init()" << std::endl;
  // Load configs & manifest
  m_manifest = *Helper::loadJson("assets/manifest.json");

  // Create window
  m_window = std::make_shared<Engine::Window>();
  m_frame_time = sf::seconds(1.0 / m_window->getFps());

  // Initiate the state stack
  m_stack = std::make_shared<Engine::StateStack>();

  // Seed random?
  // Load assets
  loadTextures();
}

int Application::run() {
  // Setup anything that we need setup
  init();

  // Throw our first state on the stack
  m_stack->push(std::make_shared<TempState>(m_stack));

  // Run loop
  loop();

  return Engine::NoError;
}

void Application::loop() {
  // std::cout << "Application::loop()" << std::endl;

  sf::Time previous = m_clock.getElapsedTime();
  sf::Time lag = sf::Time::Zero;

  while(m_window->isOpen() && !m_stack->isEmpty())
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

void Application::loadTextures() {
  // std::cout << "Application::loadTextures()" << std::endl;
  int i = 0;
  for (auto& el: m_manifest["textures"].items()) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(el.value());

    m_textures[i++] = texture;
  }
}