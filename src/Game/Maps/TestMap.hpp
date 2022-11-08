#pragma once

#include "Engine/Actions.hpp"
#include "Engine/Atlas.hpp"
#include "Engine/Actions.hpp"
#include "Engine/Trigger.hpp"

#include "Game/ComputerGame.hpp"

namespace Maps {
  class TestMap : public Engine::Atlas {
    public:
      TestMap() : Engine::Atlas("assets/maps/dungeon.atlas") {

        auto E = Actions::EmptyFn;
        m_action_map = {
          {"tele_south", [](Engine::Map* t_map){return Actions::Teleport(t_map, 2, 12); }},
          {"tele_north", [](Engine::Map* t_map){return Actions::Teleport(t_map, 2,  2); }}
        };
        m_trigger_types = {
          {"north_stair_trigger", Engine::Trigger(E, E, E)},
          {"south_stair_trigger", Engine::Trigger(E, E, E)}
        };
        // m_triggers = {
        //   {coordToIndex(2,  2), "north_stair_trigger"},
        //   {coordToIndex(2, 12), "south_stair_trigger"},
        //   {coordToIndex(2,  9), "south_stair_trigger"}
        // };
      };

      void onWake(Engine::Map* t_map) override {
        auto& app = *ComputerGame::instance();

        Actions::AddNPC(t_map, app.getCharacter("strolling_npc"), 8, 9, 0)(nullptr,nullptr);
        // Actions::AddNPC(t_map, app.getCharacter("standing_npc"), 8, 9, 0)(nullptr,nullptr);
      };
  };
}
