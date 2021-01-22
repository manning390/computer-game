#include "Map.hpp"

Engine::Map::Map(AssetProvider& t_asset_provider, std::shared_ptr<Engine::Atlas> t_atlas) {
  LOG_TRACE("Engine::Map::Map()");
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

  // Get the blocking tile by searching for the collision tileset
  for (auto tileset_iter = t_atlas->tilesets.begin(); tileset_iter != t_atlas->tilesets.end(); tileset_iter++) {
    auto tileset = t_asset_provider.getTileset(tileset_iter->second);

    uint tile_id_iter = tileset_iter->first;
    for (auto uv_iter = tileset->uvs.begin(); uv_iter < tileset->uvs.end(); uv_iter++, ++tile_id_iter) {
      m_uvs[tile_id_iter] = *uv_iter;
      m_textures[tile_id_iter] = t_asset_provider.getTexture(tileset->texture_src);
    }

    if (tileset_iter->second == "collision") {
      m_blocking_tile = tileset_iter->first;
    }
  }
  LOG_INFO("Blocking tile is: {}", m_blocking_tile);
}

sf::Vector2i Engine::Map::pixelToTile(int t_x, int t_y) {
  // Clamp to bounds of map
  int x = std::max<int>(m_x, t_x);
  int y = std::max<int>(m_y, t_y);
  x = std::min<int>(m_x + m_width_pixel - 1, x);
  y = std::min<int>(m_y + m_height_pixel - 1, y);

  // Map from the bounded point to a tile
  const int tileX = (m_x + x) / m_tile_width;
  const int tileY = (m_y + y) / m_tile_height;

  return sf::Vector2i(tileX, tileY);
}

void Engine::Map::goTo(uint t_x, uint t_y) {

}

uint Engine::Map::getTile(uint t_x, uint t_y) {
  auto calc = t_x + (t_y * m_width);
  auto out = m_tiles[calc];
  return out;
}

void Engine::Map::render(std::shared_ptr<Engine::Window> t_window) {
  // LOG_TRACE("Engine::Map::render()");
  renderLayer(t_window, m_layer);
}

void Engine::Map::renderLayer(std::shared_ptr<Engine::Window> t_window, Engine::Layer t_layer) {
  // LOG_TRACE("Engine::Map::renderLayer()");
  auto screenSize = t_window->getScreenSize();
  auto top_left_coord = pixelToTile(
      m_cam_x - (screenSize.x / 2),
      m_cam_y - (screenSize.y / 2));
  auto bottom_right_coord  = pixelToTile(
      m_cam_x + (screenSize.x / 2),
      m_cam_y + (screenSize.y / 2));

  std::shared_ptr<sf::Texture> cached_texture = nullptr;
  for (uint j = top_left_coord.y, y_mx = bottom_right_coord.y + 1; j < y_mx; ++j) {
    for (uint i = top_left_coord.x, x_mx = bottom_right_coord.x; i <  x_mx + 1; ++i) {
      uint tile = getTile(i, j);
      if (tile < 1) continue; // We don't render 0

      // Don't change the texture of the sprite unless we need to
      if (m_textures[tile] != cached_texture) {
        m_sprite.setTexture(*m_textures[tile]);
        cached_texture = m_textures[tile];
      }
      m_sprite.setTextureRect(m_uvs[tile]);
      m_sprite.setPosition(m_x + i * float(m_tile_width), m_y + j * float(m_tile_height));

      t_window->draw(m_sprite);
    }
  }
}
