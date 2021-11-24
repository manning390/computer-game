#pragma once

#include <memory>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Log.hpp"
#include "Helper.hpp"

#include "Engine/StateStack.hpp"
#include "Engine/IState.hpp"
#include "Engine/Window.hpp"
#include "Engine/Map.hpp"

#include "Game/ComputerGame.hpp"
#include "Game/Maps/TestMap.hpp"

class TestState : public Engine::IState {
  public:
    TestState(std::shared_ptr<Engine::StateStack> t_stack);
    ~TestState(void) override = default;

    bool update(float t_dt) override;

    void render(std::shared_ptr<Engine::Window> t_window) override;

    void handleInput(sf::Event t_event) override;

    void enter(void) override;

    void exit(void) override;

  protected:
    bool m_mouse_lock = false;
    std::shared_ptr<Engine::Map> m_map;
    sf::Sprite bob;
    sf::Sprite jim;
};
