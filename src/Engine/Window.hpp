#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Log.hpp"
#include "Constant.hpp"
#include "NoCopy.hpp"
#include "NoMove.hpp"

namespace Engine {
  /**
   * @brief A light-weight wrapper around sf::RenderWindow, to handle windowing functionality
   *
   */
  class Window : public Traits::NoCopy, public Traits::NoMove {
    public:
      /**
      * @brief Construct a new Window object
      *
      */
      Window();

      /**
       * @brief Construct a new Window Object
       *
       * @param window_width Window width
       * @param window_height Window height
       * @param window_title Window title
       */
      Window(unsigned int t_window_width, unsigned int t_window_height, const std::string& t_window_title, float t_fps = 60.0);

      /**
       * @brief Destroy the Window object
       *
       */
      ~Window();

      /**
       * @brief Get the sf::RenderWindow object
       *
       */
      std::shared_ptr<sf::RenderWindow> getNativeWindow() const;

      /**
       * @brief Polls window events and responds properly
       *
       */
      void pollEvent(sf::Event& t_event);

      /**
       * @brief Passes whatever is passed into the m_window->draw() function
       *
       */
      void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default);

      void reset(void) const;

      void display(void) const;

      /**
       * @brief Returns whether the window is open and showing
       *
       * @return true
       * @return false
       */
      bool isOpen();

      void setPosition(const int t_x, const int t_y);
      void setFullscreen(bool t_fullscreen);
      void setFps(float t_fps);
      float getFps() const;

      std::unique_ptr<sf::Event> getEvent();

      sf::View calcView(const float t_window_width, const float t_window_height);

      sf::Vector2i getScreenSize();

      sf::View getView() const;

      // void move(float t_x, float t_y);
      void move(sf::Vector2i t_v);

    private:
      /**
       * @brief Window object
       *
       */
      std::shared_ptr<sf::RenderWindow> m_window;
      unsigned int m_window_width, m_window_height;
      std::string m_window_title;
      bool m_fullscreen;
      float m_fps;
      float m_initial_aspect_ratio;
  };
} // namespace Engine
