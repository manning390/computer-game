#pragma once

#include "Log.hpp"

#include "Engine/Character.hpp"
#include "Engine/EntityDef.hpp"
#include "Game/States/Character/WaitState.hpp"
#include "Game/States/Character/MoveState.hpp"
#include "Game/States/Character/NPCStandState.hpp"
#include "Game/States/Character/PlanStrollState.hpp"

inline const std::unordered_map<std::string, Engine::EntityDef> g_entities{
//  key      tileset    f  x  y  l  w  h
  {"hero", {"monsters", 0, 1, 1, 0, 0, 0}},
  {"npc", {"monsters",  1, 8, 9, 0, 0, 0}},
};

template<class T>
inline Engine::StateFactoryFn makeStateFactory(void) {
  return [](Engine::Character* t_char, std::shared_ptr<Engine::Map> t_map){ return std::make_shared<T>(t_char, t_map); };
};

inline const std::unordered_map<std::string, Engine::CharacterDef> g_characters{
  {"hero", {g_entities.at("hero"),
             {
               {"right", {0, 4}},
               {"down",  {1, 5}},
               {"up",    {2, 6}},
               {"left",  {3, 7}}},
             {
               {"wait", makeStateFactory<WaitState>()},
               {"move", makeStateFactory<MoveState>()}
             }}},
  {"standing_npc", {g_entities.at("npc"),
                     {},
                     {{"npc_stand", makeStateFactory<NPCStandState>()}},
                     {0, 1},
                     "npc_stand"}},
  {"strolling_npc", {g_entities.at("npc"),
                      {
                        {"right", {0, 4}},
                        {"down",  {1, 5}},
                        {"up",    {2, 6}},
                        {"left",  {3, 7}}},
                      {
                       {"plan_stroll", makeStateFactory<PlanStrollState>()},
                       {"move", makeStateFactory<MoveState>()}
                      },
                      {0, 1},
                      "plan_stroll"}}
};
