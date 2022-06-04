#include "Map.hpp"
#include "Entity.hpp"
#include "Log.hpp"

Engine::Map::Map(Application& t_app, std::shared_ptr<Engine::Atlas> t_atlas) :
  m_window(t_app.m_window),
  m_atlas(t_atlas),
  m_width(t_atlas->width),
  m_height(t_atlas->height),
  m_tile_width(t_atlas->tile_width),
  m_tile_height(t_atlas->tile_height)
{
  LOG_TRACE("Engine::Map::Map()");

  // Map size in pixels
  m_width_pixel = m_width * m_tile_width;
  m_height_pixel = m_height * m_tile_height;
  // Set map offset
  m_x = 0.0;
  m_y = 0.0;

  auto view = m_window->getNativeWindow()->getView();
  m_cam = (sf::Vector2i)view.getCenter();

  // Get the blocking tile by searching for the collision tileset
  for (auto tileset_iter = t_atlas->tilesets.begin(); tileset_iter != t_atlas->tilesets.end(); tileset_iter++) {
    auto tileset = t_app.getTileset(tileset_iter->second);

    uint tile_id_iter = tileset_iter->first;
    for (auto uv_iter = tileset->uvs.begin(); uv_iter < tileset->uvs.end(); uv_iter++, ++tile_id_iter) {
      m_uvs[tile_id_iter] = *uv_iter;
      m_textures[tile_id_iter] = tileset->texture;
    }

    if (tileset_iter->second == "collision") {
      m_blocking_tile = tileset_iter->first;
    }
  }
  LOG_INFO("Blocking tile is: {}", m_blocking_tile);
  m_atlas->onWake(this);
}

sf::Vector2i Engine::Map::pixelToTile(float t_x, float t_y, bool t_no_offset) const {
  return pixelToTile(sf::Vector2f(t_x, t_y), t_no_offset);
}

sf::Vector2i Engine::Map::pixelToTile(sf::Vector2f t_vec, bool t_no_offset) const {
  // Remove the offset to get the pixel within the map
  if (!t_no_offset) t_vec = t_vec - getPosition();

  // Clamp to bounds of map
  float x = std::clamp<float>(t_vec.x, 0, m_width_pixel - 1);
  float y = std::clamp<float>(t_vec.y, 0, m_height_pixel - 1);

  // Map from the bounded point to a tile
  const int tile_x = x / m_tile_width;
  const int tile_y = y / m_tile_height;

  return sf::Vector2i(tile_x, tile_y);
}

sf::Vector2f Engine::Map::tileToPixel(uint t_tx, uint t_ty) const {
  const int x_tile = std::clamp<uint>(t_tx, 0, m_width);
  const int y_tile = std::clamp<uint>(t_ty, 0, m_height);

  return sf::Vector2f(m_x + (x_tile * m_tile_width), m_y + (y_tile * m_tile_height));
}

void Engine::Map::setPosition(float t_x, float t_y) {
  // LOG_TRACE("Engine::Map::setPosition({},{})", t_x, t_y);
  m_x = t_x;
  m_y = t_y;
}

sf::Vector2f Engine::Map::getPosition() const {
  return sf::Vector2f(m_x, m_y);
}

void Engine::Map::centerMapInView() {
  LOG_TRACE("Engine::Map::centerMapInView()");
  LOG_WARN("This is iterating over every entity and also updating their sprite position... This is probably bad.");
  auto center = m_window->getNativeWindow()->getView().getCenter();
  // LOG_DEBUG("{}, {}", center.x, center.y);
  m_x = center.x - (m_width_pixel / 2.0);
  m_y = center.y - (m_height_pixel / 2.0);
  // LOG_DEBUG("{}, {}", m_x, m_y);
}

void Engine::Map::goTo(sf::Vector2i t_v) {
  // LOG_TRACE("Engine::Map::goTo(sf::Vector2i({},{}))", t_v.x, t_v.y);
  // LOG_DEBUG("m_cam {},{}", m_cam.x, m_cam.y);
  m_window->move(t_v - m_cam);
  m_cam = t_v;
}

void Engine::Map::goTo(int t_x, int t_y) {
  goTo(sf::Vector2i(t_x, t_y));
}

void Engine::Map::goToTile(uint t_x, uint t_y) {
  goTo(
    (t_x * m_tile_width) + m_tile_width / 2.0,
    (t_y * m_tile_height) + m_tile_height / 2.0
  );
}

sf::Vector2u Engine::Map::getSizeP(void) const {
  return sf::Vector2u(m_width_pixel, m_height_pixel);
}

sf::Vector2u Engine::Map::getSizeT(void) const {
  return sf::Vector2u(m_width, m_height);
}

std::vector<uint>& Engine::Map::getLayer(uint t_layer_index) const {
  auto& atlas_layer = m_atlas->layers[t_layer_index / 3];
  auto index = t_layer_index % 3;

  if (index == 0) return atlas_layer.base;
  if (index == 1) return atlas_layer.decoration;
  return atlas_layer.collision;
}

uint Engine::Map::coordToIndex(uint t_x, uint t_y, uint t_layer) const {
  return (t_layer * m_width * m_height) + t_x + (t_y * m_width);
}

uint Engine::Map::getTileId(uint t_tx, uint t_ty, uint t_layer_index) const {
  return getLayer(t_layer_index)[t_tx + (t_ty * m_width)];
}

bool Engine::Map::isBlocked(uint t_layer, uint t_tx, uint t_ty) const {
  auto tile = getTileId(t_tx, t_ty, t_layer + 2);
  auto entity = getEntity(t_tx, t_ty, t_layer);
  return tile == m_blocking_tile || entity != nullptr;
}

void Engine::Map::setAtlas(std::shared_ptr<Engine::Atlas> t_atlas) {
  m_atlas = t_atlas;
}

std::shared_ptr<Engine::Atlas> Engine::Map::getAtlas() const {
  return m_atlas;
}

std::shared_ptr<Engine::Trigger> Engine::Map::getTrigger(uint t_x, uint t_y, uint t_layer) {
  auto index = coordToIndex(t_x, t_y, t_layer);
  return m_triggers[index];
}

bool Engine::Map::update(float t_dt) {
  for(auto& [k, npc] : m_npcs) npc->m_controller->update(t_dt);

  return true;
};

void Engine::Map::render(std::shared_ptr<Engine::Window> t_window, std::shared_ptr<Engine::Entity> t_hero) {
  // LOG_TRACE("Engine::Map::render()");
  // Render a black background that's the size of the map, it doesn't move lets us see the edge of the map via camera
  sf::RectangleShape map_bg(sf::Vector2f(m_width_pixel, m_height_pixel));
  map_bg.setFillColor(sf::Color::Black);
  map_bg.setPosition(m_x, m_y);
  t_window->draw(map_bg);

  auto i = 0;
  for (auto& layer: m_atlas->layers) {
    renderLayer(t_window, layer);
    renderEntities(t_window, i, t_hero);
    ++i;
  }
}

void Engine::Map::renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer& t_layer) {
  // LOG_TRACE("Engine::Map::renderLayer()");
  std::shared_ptr<sf::Texture> cached_texture = nullptr;

  // Choose what layers we render
  auto layers = {t_layer.base, t_layer.decoration};
  // auto layers = {t_layer.base, t_layer.decoration, t_layer.collision};

  uint i;
  for (auto layer_data : layers) {
    i = 0;
    for (auto tile : layer_data) {
      // We don't render 0
      if (tile < 1) {
        ++i;
        continue;
      }

      int k = i % m_width;
      int n = i / m_width;

      // Don't change the texture of the sprite unless we need to
      if (m_textures[tile] != cached_texture) {
        m_sprite.setTexture(*m_textures[tile]);
        cached_texture = m_textures[tile];
      }
      m_sprite.setTextureRect(m_uvs[tile]);
      m_sprite.setPosition(m_x + (k * m_tile_width), m_y + (n * m_tile_height));

      t_window->draw(m_sprite);
      ++i;
    }
  }
}

void Engine::Map::renderEntities(std::shared_ptr<Engine::Window> t_window, uint t_layer, std::shared_ptr<Engine::Entity> t_hero) {
  // LOG_TRACE("Engine::Map::renderEntities()");
  auto layerOffset = m_width * m_height;
  std::map<uint, std::shared_ptr<Engine::Entity>> drawList(m_entities);

  if(t_hero != nullptr) drawList[coordToIndex(t_hero->m_tile_x, t_hero->m_tile_y, t_hero->m_layer)] = t_hero;
  for(auto& [i, entity] : drawList) {
    if(i < layerOffset * t_layer) continue; // Skip any entity below our layer offset range
    if (i > layerOffset * (t_layer + 1)) break; // Stop looping once we're past our layer offset range
    entity->render(t_window);
  }
};

std::shared_ptr<Engine::Entity> Engine::Map::getEntity(uint t_x, uint t_y, uint t_layer) const {
  // LOG_TRACE("Engine::Map::getEntity()");
  auto index = coordToIndex(t_x, t_y, t_layer);
  auto iter = m_entities.find(index);
  return iter == m_entities.end() ? nullptr : iter->second;
};

void Engine::Map::addEntity(std::shared_ptr<Engine::Entity> t_entity) {
  // LOG_TRACE("Engine::Map::addEntity()");
  auto index = coordToIndex(t_entity->m_tile_x, t_entity->m_tile_y, t_entity->m_layer);
  auto check = m_entities.find(index);
  assert(check == m_entities.end() && "Entity cannot be added to this map index, it is occupied.");
  m_entities[index] = t_entity;
};

void Engine::Map::removeEntity(std::shared_ptr<Engine::Entity> t_entity) {
  // LOG_TRACE("Engine::Map::removeEntity()");
  auto index = coordToIndex(t_entity->m_tile_x, t_entity->m_tile_y, t_entity->m_layer);
  assert(m_entities.find(index)->second == t_entity && "Trying to remove entity that does not exist at index");
  m_entities.erase(index);
};

