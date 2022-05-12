#pragma once

#include <memory>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Log.hpp"
#include "Helper.hpp"

#include "Engine/Actions.hpp"
#include "Engine/Entity.hpp"
#include "Engine/IState.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/StateStack.hpp"
#include "Engine/Window.hpp"

#include "Game/ComputerGame.hpp"
#include "Game/Character.hpp"
#include "Game/Maps/TestMap.hpp"
#include "Game/States/WaitState.hpp"
#include "Game/States/MoveState.hpp"

class TestState : public Engine::IState {
  public:
    TestState(std::shared_ptr<Engine::StateStack> t_stack);
    ~TestState(void) override = default;

    bool update(float t_dt) override;

    void render(std::shared_ptr<Engine::Window> t_window) override;

    void handleInput(std::shared_ptr<Engine::Input> t_input) override;

    void enter(void) override;

    void exit(void) override;


  protected:
    std::shared_ptr<Engine::Map> m_map;
    std::shared_ptr<WaitState> m_wait_state;
    std::shared_ptr<MoveState> m_move_state;
    std::shared_ptr<Character> m_bob;
    Actions::ActionFn m_teleport_up = Actions::Teleport(m_map, 2, 2, 0);
    Actions::ActionFn m_teleport_down = Actions::Teleport(m_map, 2, 12, 0);
} ;
