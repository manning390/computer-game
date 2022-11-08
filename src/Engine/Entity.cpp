#include "Entity.hpp"
#include "Map.hpp"

Engine::Entity::Entity(const EntityDef& t_def) {
  m_id = t_def.id;
  m_tileset = t_def.tileset;
  m_sprite = sf::Sprite(*m_tileset->texture, m_tileset->uvs[t_def.start_frame]);
  m_width = t_def.width == 0 ?
    m_tileset->tile_width : t_def.width;
  m_height = t_def.height == 0 ?
    m_tileset->tile_height : t_def.height;
  m_start_frame = t_def.start_frame;
  m_tile_x = t_def.tile_x;
  m_tile_y = t_def.tile_y;
  m_layer = t_def.layer;
}

void Engine::Entity::render(std::shared_ptr<Engine::Window> t_window) {
  t_window->draw(m_sprite);
}

void Engine::Entity::setFrame(uint t_frame) {
  m_sprite.setTextureRect(m_tileset->uvs[t_frame]);
}

void Engine::Entity::setTilePos(uint t_x, uint t_y, uint t_layer, Engine::Map* t_map) {
  // LOG_TRACE("Engine::Entity::setTilePos({}, {}, {}, t_map)", t_x, t_y, t_layer);

  auto self = shared_from_this();

  // Remove from current tile
  if (t_map->getEntity(m_tile_x, m_tile_y, m_layer) == self) {
    t_map->removeEntity(shared_from_this());
  }

  // Check target tile
  if (t_map->getEntity(t_x, t_y, t_layer) != nullptr) {
    LOG_ERROR("[{}]:{},{} is not empty, cannot place entity there", t_layer, t_x, t_y);
    assert(false);
  }

  m_tile_x = t_x;
  m_tile_y = t_y;
  m_layer = t_layer;

  t_map->addEntity(self);

  auto vec = t_map->tileToPixel(m_tile_x, m_tile_y);
  m_sprite.setPosition(vec.x, vec.y);
  m_x = vec.x;
  m_y = vec.y;
}

sf::Vector2i Engine::Entity::getTilePos() const {
  return sf::Vector2i(m_tile_x, m_tile_y);
}
