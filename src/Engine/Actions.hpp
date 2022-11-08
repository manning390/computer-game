#pragma once

#include <functional>

#include "Entity.hpp"
#include "EntityDef.hpp"
#include "Character.hpp"

namespace Engine {
  class Trigger;
  class Map;
};

namespace Actions {
  typedef std::function<void (std::shared_ptr<Engine::Trigger> t_trigger, std::shared_ptr<Engine::Entity> t_entity)> ActionFn;

  inline void EmptyFn(std::shared_ptr<Engine::Trigger>, std::shared_ptr<Engine::Entity>){ };
  ActionFn Teleport(Engine::Map* t_map, uint t_tile_x, uint t_tile_y, uint t_layer = 0);
  ActionFn AddNPC(Engine::Map* t_map, const Engine::CharacterDef& t_def, int t_tile_x = -1, int t_tile_y = -1, int t_layer = -1);
};
