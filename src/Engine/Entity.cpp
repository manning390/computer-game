#include "Entity.hpp"

Engine::Entity::Entity(Engine::Application & t_app, const EntityDef & t_entity_def) {
  m_tileset = t_app.getTileset(t_entity_def.tileset);
  m_sprite = sf::Sprite(
    *(t_app.getTexture(m_tileset->texture)),
    m_tileset->uvs[t_entity_def.start_frame]
  );
  m_width = t_entity_def.width == 0 ?
    m_tileset->tile_width : t_entity_def.width;
  m_height = t_entity_def.height == 0 ?
    m_tileset->tile_height : t_entity_def.height;
  m_start_frame = t_entity_def.start_frame;
  m_tile_x = t_entity_def.tile_x;
  m_tile_y = t_entity_def.tile_y;
  m_layer = t_entity_def.layer;
}

void Engine::Entity::render(std::shared_ptr<Engine::Window> t_window) {
  t_window->draw(m_sprite);
}

void Engine::Entity::setFrame(uint t_frame) {
  m_sprite.setTextureRect(m_tileset->uvs[t_frame]);
}

void Engine::Entity::setTilePos(uint t_x, uint t_y, uint t_layer, std::shared_ptr<Engine::Map> t_map) {
  // Remove from current tile
  // if (t_map->getEntity(m_tile_x, m_tile_y, m_layer) == this) {
    // t_map->removeEntity(this);
  // }

  // Check target tile
  // if (t_map->getEntity(t_x, t_y, t_layer) == this) {
  //   LOG_ERROR("[{}]:{},{} is not empty, cannot place entity there", t_layer, t_x, t_y);
  //   std::exit(1);
  // }

  m_tile_x = t_x;
  m_tile_y = t_y;
  m_layer = t_layer;

  // t_map->addEntity(this);

  auto vec = t_map->tileToPixel(m_tile_x, m_tile_y);
  m_sprite.setPosition(vec.x, vec.y);
  m_x = vec.x;
  m_y = vec.y;
}

sf::Vector2i Engine::Entity::getTilePos() const {
  return sf::Vector2i(m_tile_x, m_tile_y);
}
