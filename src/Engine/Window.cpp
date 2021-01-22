#include "Window.hpp"

Engine::Window::Window() : Window(1024, 768, "Main Window") {}

Engine::Window::Window(unsigned int t_window_width, unsigned int t_window_height, const std::string& t_window_title, float t_fps) {
  m_window_width = t_window_width;
  m_window_height = t_window_height;
  m_window_title = t_window_title;
  m_initial_aspect_ratio = static_cast<float>(t_window_width) / static_cast<float>(t_window_height);
  m_fullscreen = false;
  setFps(t_fps);
  m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_window_width, m_window_height), m_window_title, sf::Style::Default);

  if (m_window == nullptr) {
    std::cerr << "Cannot create SFML Window. Make sure DISPLAY=:0 environment variable is set." << std::endl;
    // Engine::Window::~Window();
  }
}

Engine::Window::~Window() {
  m_window->close();
  m_window.reset();
}

std::shared_ptr<sf::RenderWindow> Engine::Window::getNativeWindow() const {
  return m_window;
}

void Engine::Window::pollEvent(sf::Event& t_event) {
  while (m_window->pollEvent(t_event)) {
    if (t_event.type == sf::Event::Closed) {
      m_window->close();
    }

    if ((t_event.type == sf::Event::KeyPressed) && (t_event.key.code == sf::Keyboard::F4)) {
      m_window->close();
    }

    if ((t_event.type == sf::Event::KeyPressed) && (t_event.key.code == sf::Keyboard::F5)) {
      setFullscreen(!m_fullscreen);
    }

    if(t_event.type == sf::Event::Resized && !m_fullscreen) {
      m_window->setView(calcView(float(t_event.size.width), float(t_event.size.height)));
    }

    if (t_event.type == sf::Event::LostFocus) {}
    if (t_event.type == sf::Event::GainedFocus) {}
  }
}

void Engine::Window::draw(const sf::Drawable &t_drawable, const sf::RenderStates &t_states) {
  m_window->draw(t_drawable, t_states);
}

bool Engine::Window::isOpen() {
  return m_window->isOpen();
}

// Probably fucked
void Engine::Window::setFullscreen(bool t_fullscreen) {
  // If not already fullscreen, and fullscreen was requested
  if (!m_fullscreen && t_fullscreen) {
    m_window->close();
    m_window_width = sf::VideoMode::getDesktopMode().width;
    m_window_height = sf::VideoMode::getDesktopMode().height;
    m_window->create(sf::VideoMode(m_window_width, m_window_height), m_window_title, sf::Style::Fullscreen);

    m_fullscreen = true;
  } else if (m_fullscreen && !t_fullscreen) {
    m_window->close();
    m_window_width = sf::VideoMode::getDesktopMode().height * uint(m_initial_aspect_ratio);
    m_window_height = sf::VideoMode::getDesktopMode().height;
    m_window->create(sf::VideoMode(m_window_width, m_window_height), m_window_title, sf::Style::Default);

    m_fullscreen = false;
  }
}

void Engine::Window::setFps(float t_fps) {
  if (t_fps > 1.0 && t_fps <= 200.0) {
    m_fps = t_fps;
  } else {
    std::cerr << "Requested fps is either too low or too high. It should be between (1.0 and 200.0]" << std::endl;
  }
}

float Engine::Window::getFps() const {
  return m_fps;
}

sf::View Engine::Window::calcView(const float t_window_width, const float t_window_height) {
  sf::FloatRect viewport(0.0f, 0.0f, 1.0f, 1.0f);

  // Find the best viewport size given the window size
  float new_ratio = t_window_width / t_window_height;
  // float scale = 1.0f;
  if (new_ratio > Engine::AspectRatio) {
    float bound_width = t_window_height * Engine::AspectRatio;
    float width_diff = t_window_width - bound_width;
    float width_perc = width_diff / t_window_width;
    viewport.left = width_perc / 2.0f;
    viewport.width = 1.0f - width_perc;

    // scale = (viewport.width * t_window_width) / bound_width;
    // scale = (bound_width - (t_window_width / floor(scale)) < (t_window_width / ceil(scale)) - bound_width) ?
      // floor(scale) :
      // ceil(scale);
  } else {
    float bound_height = t_window_width / Engine::AspectRatio;
    float height_diff = t_window_height - bound_height;
    float height_perc = height_diff / t_window_height;
    viewport.top = height_perc / 2.0f;
    viewport.height = 1.0f - height_perc;

    // scale = (viewport.height * t_window_height) / bound_height;
    // scale = (bound_height - (t_window_height / floor(scale)) < (t_window_height / ceil(scale)) - bound_height) ?
      // floor(scale) :
      // ceil(scale);
  }

  // sf::View view(sf::FloatRect(0, 0, t_window_width / scale, t_window_height / scale));
  sf::View view(sf::FloatRect(0, 0, Engine::NativeWidth, Engine::NativeHeight));
  view.setViewport(viewport);

  return view;
}

void Engine::Window::reset(void) const {
  m_window->setActive(true);
  m_window->clear(sf::Color(51, 51, 51));
}

void Engine::Window::display(void) const {
  m_window->display();
}

sf::Vector2i Engine::Window::getScreenSize() {
  return sf::Vector2i(m_window_width, m_window_height);
}


