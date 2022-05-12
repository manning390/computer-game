#pragma once

#include <functional>

#include "Entity.hpp"

// Don't really want to have to call Actions::ActionFn everywhere so we'll put this out here
typedef std::function<void (int* trigger, std::shared_ptr<Engine::Entity> t_entity)> ActionFn;

namespace Actions {
  inline ActionFn Teleport(std::shared_ptr<Engine::Map> t_map, uint t_tile_x, uint t_tile_y, uint t_layer = 0) {
    return [&]([[maybe_unused]] int* trigger, std::shared_ptr<Engine::Entity> t_entity) {
      t_entity->setTilePos(t_tile_x, t_tile_y, t_layer, t_map);
    };
  };

};
