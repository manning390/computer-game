#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Constant.hpp"
#include "Helper.hpp"
#include "NoCopy.hpp"
#include "NoMove.hpp"

#include "Engine/AssetProvider.hpp"
#include "Engine/Atlas.hpp"
#include "Engine/Window.hpp"
#include "Engine/StateStack.hpp"

namespace Engine {
  class Application : public Traits::NoCopy, public Traits::NoMove, public Engine::AssetProvider {
    public:
      ~Application(void) override = default;

      /**
      * @brief Hashmap of all the textures in the game
      *
      */
      std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;

      std::unordered_map<std::string, std::shared_ptr<Engine::Tileset>> m_tilesets;

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

      std::shared_ptr<Engine::Tileset> getTileset(std::string t_key) override;
      std::shared_ptr<sf::Texture> getTexture(std::string t_key) override;

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

      const std::string m_tilesets_manifest_path;
      const std::string m_textures_manifest_path;

      /**
      * @brief Game state stack
      *
      */
      std::shared_ptr<Engine::StateStack> m_stack;

      /**
      * @brief Sets up the Application once
      *
      */
      void init(void);

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
      * @breif Load allt he tilesets and store them in a hasmap
      *
      */
      void loadTilesets();

      /**
      * @brief Load all the textures and store them in a hashmap because we're lazy af
      *
      */
      void loadTextures();
  };
}
