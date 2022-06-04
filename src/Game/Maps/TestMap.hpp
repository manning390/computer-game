#pragma once

#include "Engine/Actions.hpp"
#include "Engine/Atlas.hpp"

#include "Game/ComputerGame.hpp"

namespace Maps {
  class TestMap : public Engine::Atlas {
    public:
      TestMap() : Engine::Atlas("assets/maps/dungeon.atlas") { };

      void onWake(Engine::Map* t_map) override {
        auto& app = *ComputerGame::instance();

        Actions::AddNPC(t_map, app.getCharacter("strolling_npc"), 8, 9, 0)(nullptr,nullptr);
      };
  };
}
