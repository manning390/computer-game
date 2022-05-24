#pragma once

#include <functional>

#include "Entity.hpp"

namespace Engine {
  class Trigger;
};

namespace Actions {
  typedef std::function<void (std::shared_ptr<Engine::Trigger> t_trigger, std::shared_ptr<Engine::Entity> t_entity)> ActionFn;

  inline void EmptyFn(std::shared_ptr<Engine::Trigger>, std::shared_ptr<Engine::Entity>){ };

  inline ActionFn Teleport(std::shared_ptr<Engine::Map> t_map, uint t_tile_x, uint t_tile_y, uint t_layer = 0) {
    return [t_map, t_tile_x, t_tile_y, t_layer]([[maybe_unused]] std::shared_ptr<Engine::Trigger> t_trigger, std::shared_ptr<Engine::Entity> t_entity) {
      // LOG_DEBUG("Actions::Teleport() to {}:{},{}", t_layer, t_tile_x, t_tile_y);
      t_entity->setTilePos(t_tile_x, t_tile_y, t_layer, t_map);
    };
  };

};
