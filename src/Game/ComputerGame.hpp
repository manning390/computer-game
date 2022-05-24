#pragma once

#include <string>

#include "Engine/Input.hpp"
#include "Engine/Application.hpp"
#include "States/TestState.hpp"

#include "InputActions.hpp"

class ComputerGame : public Engine::Application {
  public:
    ~ComputerGame(void) = default;

    static ComputerGame* instance(void) {
        // std::cout << "Application::instance()" << std::endl;
        return (!s_instance) ? s_instance = new ComputerGame() : s_instance;
    }

  protected:
    ComputerGame(void) :
      Engine::Application("assets/manifests/tilesets.manifest", "assets/manifests/textures.manifest") {
        s_instance = this;
    };

    void init(void) override;

    void createInitialState(void) override;

  private:
    static ComputerGame* s_instance;
};

