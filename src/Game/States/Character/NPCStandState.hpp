#pragma once

#include "Engine/Map.hpp"
#include "Engine/Character.hpp"
#include "Engine/EmptyState.hpp"

class NPCStandState : public Engine::EmptyState {
  public:
    NPCStandState(Engine::Character*, Engine::Map*) {};

};
