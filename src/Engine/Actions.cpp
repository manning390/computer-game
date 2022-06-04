#include "Actions.hpp"
#include "Trigger.hpp"

Actions::ActionFn Actions::Teleport(Engine::Map* t_map, uint t_tile_x, uint t_tile_y, uint t_layer) {
    // LOG_TRACE("Actions::Teleport()");
  return [=](std::shared_ptr<Engine::Trigger>, std::shared_ptr<Engine::Entity> t_entity) {
    // LOG_TRACE("Actions::Teleport() Callback");
    t_entity->setTilePos(t_tile_x, t_tile_y, t_layer, t_map);
  };
};

Actions::ActionFn Actions::AddNPC(Engine::Map* t_map, const Engine::CharacterDef& t_def, int t_tile_x, int t_tile_y, int t_layer) {
  // LOG_TRACE("Actions::AddNPC()");
  return [=](std::shared_ptr<Engine::Trigger>, std::shared_ptr<Engine::Entity>) {
    // LOG_TRACE("Actions::AddNPC() Callback");
    auto character = std::make_shared<Engine::Character>(t_def, t_map);
    auto entity = character->m_entity;
    auto x = t_tile_x >= 0 ? t_tile_x : entity->m_tile_x;
    auto y = t_tile_y >= 0 ? t_tile_y : entity->m_tile_y;
    auto l = t_layer  >= 0 ? t_layer  : entity->m_layer;
    entity->setTilePos(x, y, l, t_map);

    t_map->m_npcs[t_map->coordToIndex(x, y, l)] = character;
  };
};
