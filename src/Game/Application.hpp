#pragma once

#include <map>
#include <iostream>
#include <memory>

#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>

#include <Traits/Constant.hpp>
#include <Traits/NoCopy.hpp>
#include <Traits/NoMove.hpp>
#include <Engine/Window.hpp>

#include "StateStack.hpp"
#include "States/TempState.hpp"

using json = nlohmann::json;

class Application : public Traits::NoCopy, public Traits::NoMove {
  public:
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

    void processArguments(int argc, const char **argv);
    int run(void);

  private:
    sf::Event m_event;
    sf::Clock m_clock;
    sf::Time m_frame_time;
    json m_manifest;

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
     * @brief Load all the textures and store them in a hashmap because we're lazy af
     *
     */
    void loadTextures();

    std::shared_ptr<sf::Texture> getTexture(std::string t_key);
};
