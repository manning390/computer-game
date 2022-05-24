#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Constant.hpp"
#include "Helper.hpp"
#include "NoCopy.hpp"
#include "NoMove.hpp"

#include "Atlas.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "StateStack.hpp"
#include "EntityDef.hpp"

namespace Engine {
  class Application : public Traits::NoCopy, public Traits::NoMove {
    public:
      virtual ~Application(void) = default;

      /**
      * @brief Hashmap of all the resources in the game
      *
      */
      std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;

      std::unordered_map<std::string, std::shared_ptr<Engine::Tileset>> m_tilesets;

      std::unordered_map<std::string, std::shared_ptr<Engine::EntityDef>> m_entity_defs;

      /**
      * @brief Tells the Application to start running
      *
      */
      void processArguments(int argc, const char **argv);

      /**
      * @brief Tells the Application to start running
      *
      */
      int run(void);

      /**
      * @brief Exits the Application
      *
      */
      void quit(void);

      std::shared_ptr<Engine::Tileset> getTileset(std::string t_key);
      std::shared_ptr<sf::Texture> getTexture(std::string t_key);

      /**
      * @brief Associated window
      *
      */
      std::shared_ptr<Engine::Window> m_window;

    protected:
      Application(
        std::string t_tilesets_manifest_path,
        std::string t_textures_manifest_path) :
        m_tilesets_manifest_path(t_tilesets_manifest_path),
        m_textures_manifest_path(t_textures_manifest_path) {};


      bool m_running = true;
      sf::Event m_event;
      sf::Clock m_clock;
      sf::Time m_frame_time;

      std::vector<Engine::ActionBinding> m_default_bindings;

      const std::string m_tilesets_manifest_path;
      const std::string m_textures_manifest_path;

      std::shared_ptr<Engine::Input> m_input;

      /**
      * @brief Game state stack
      *
      */
      std::shared_ptr<Engine::StateStack> m_stack;

      /**
      * @brief Sets up the Application once
      *
      */
      virtual void init(void);

      /**
      * @brief Loads the starting state of the Application
      *
      */
      virtual void createInitialState(void) = 0;

      /**
      * @brief The game loop which runs every frame, calls preFrame, onFrame, postFrame respectively
      *
      */
      void loop();

      /**
      * @brief Load all the tilesets and store them in a hasmap
      *
      */
      void loadTilesets();

      /**
      * @brief Load all the textures and store them in a hashmap because we're lazy af
      *
      */
      void loadTextures();

      /**
       * @brief Load the bindings and set m_input with them
       * if they don't exist then just use the defaults
       *
       */
      void loadBindings();
  };
}
