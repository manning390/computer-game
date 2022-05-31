#pragma once

#include "Engine/IState.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Map.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/Window.hpp"
#include "Engine/EmptyState.hpp"

#include "Engine/Character.hpp"

class NPCStandState : public Engine::EmptyState {
  public:
    NPCStandState(Engine::Character* t_char, std::shared_ptr<Engine::Map> t_map) :
      m_char(t_char),
      m_map(t_map) {};

    Engine::Character* m_char;
    std::shared_ptr<Engine::Map> m_map;
};
