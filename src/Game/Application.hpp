#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>


#include <SFML/Graphics.hpp>
//#include <boost/log/trivial.hpp>

#include "Constant.hpp"
#include "Helper.hpp"
#include "NoCopy.hpp"
#include "NoMove.hpp"

#include "../Engine/AssetProvider.hpp"
#include "../Engine/Atlas.hpp"
#include "../Engine/Window.hpp"
#include "../Engine/StateStack.hpp"
#include "States/TestState.hpp"

class Application : public Traits::NoCopy, public Traits::NoMove, public Engine::AssetProvider {
  public:
    ~Application(void) override = default;
    /**
     * @brief Gets the instance of the application, if it doesn't exist instanciates it
     *
     */
    static Application& instance(void);

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

  private:
    bool m_running = true;
    sf::Event m_event;
    sf::Clock m_clock;
    sf::Time m_frame_time;

    /**
     * @brief Associated window
     *
     */
    std::shared_ptr<Engine::Window> m_window;

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

    std::shared_ptr<Engine::Tileset> getTileset(std::string t_key) override;
    std::shared_ptr<sf::Texture> getTexture(std::string t_key) override;
};
