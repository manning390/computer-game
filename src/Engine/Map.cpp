#include "Map.hpp"
#include "SFML/System/Vector2.hpp"

Engine::Map::Map(Application& t_app, std::shared_ptr<Engine::Atlas> t_atlas) {
  LOG_TRACE("Engine::Map::Map()");

  m_window = t_app.m_window;
  m_atlas = t_atlas;

  m_layer = t_atlas->layers[0];
  m_tiles = m_layer.base;

  // Map size in tiles
  m_width = t_atlas->width;
  m_height = t_atlas->height;
  // Tile size
  m_tile_width = t_atlas->tile_width;
  m_tile_height = t_atlas->tile_height;
  // Map size in pixels
  m_width_pixel = m_width * m_tile_width;
  m_height_pixel = m_height * m_tile_height;
  // Set map offset
  m_x = 0.0;
  m_y = 0.0;

  auto view = m_window->getView();
  m_cam = (sf::Vector2i)view.getCenter();

  // Get the blocking tile by searching for the collision tileset
  for (auto tileset_iter = t_atlas->tilesets.begin(); tileset_iter != t_atlas->tilesets.end(); tileset_iter++) {
    auto tileset = t_app.getTileset(tileset_iter->second);

    uint tile_id_iter = tileset_iter->first;
    for (auto uv_iter = tileset->uvs.begin(); uv_iter < tileset->uvs.end(); uv_iter++, ++tile_id_iter) {
      m_uvs[tile_id_iter] = *uv_iter;
      m_textures[tile_id_iter] = t_app.getTexture(tileset->texture);
    }

    if (tileset_iter->second == "collision") {
      m_blocking_tile = tileset_iter->first;
    }
  }
  LOG_INFO("Blocking tile is: {}", m_blocking_tile);
}

sf::Vector2i Engine::Map::pixelToTile(float t_x, float t_y) {
  // Clamp to bounds of map
  float x = std::clamp<float>(t_x, m_x, m_x + m_width_pixel - 1);
  float y = std::clamp<float>(t_y, m_y, m_y + m_height_pixel - 1);

  // Map from the bounded point to a tile
  const int tileX = x / m_tile_width;
  const int tileY = y / m_tile_height;

  return sf::Vector2i(tileX, tileY);
}

sf::Vector2f Engine::Map::tileToPixel(uint t_x, uint t_y) {
  const int x_tile = std::clamp<uint>(t_x, 0, m_width);
  const int y_tile = std::clamp<uint>(t_y, 0, m_height);

  return sf::Vector2f(m_x + (x_tile * m_tile_width), m_y + (y_tile * m_tile_height));
}

void Engine::Map::setPosition(float t_x, float t_y) {
  // LOG_TRACE("Engine::Map::setPosition({},{})", t_x, t_y);
  m_x = t_x;
  m_y = t_y;
}

void Engine::Map::goTo(sf::Vector2i t_v) {
  LOG_TRACE("Engine::Map::goTo(sf::Vector2i({},{}))", t_v.x, t_v.y);
  LOG_DEBUG("m_cam {},{}", m_cam.x, m_cam.y);
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

sf::Vector2u Engine::Map::getSize(void) {
  return sf::Vector2u(m_width_pixel, m_height_pixel);
}

uint Engine::Map::getTileIndex(uint t_tx, uint t_ty) {
  return m_tiles[t_tx + (t_ty * m_width)];
}

void Engine::Map::render(std::shared_ptr<Engine::Window> t_window) {
  // LOG_TRACE("Engine::Map::render()");
  // Render a black background that's the size of the map, it doesn't move lets us see the edge of the map via camera
  sf::RectangleShape map_bg(sf::Vector2f(m_width_pixel, m_height_pixel));
  map_bg.setFillColor(sf::Color::Black);
  map_bg.setPosition(0, 0);
  t_window->draw(map_bg);

  renderLayer(t_window, m_layer);
}

void Engine::Map::renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer t_layer) {
  // LOG_TRACE("Engine::Map::renderLayer()");
  std::shared_ptr<sf::Texture> cached_texture = nullptr;
  uint i = 0;
  for (auto tile : m_tiles) {
    if (tile < 1) continue; // We don't render 0

    int k = i % m_width;
    int n = i / m_height;

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
