#include "MoveState.hpp"

bool MoveState::update(float t_dt) {
  m_tween->update(t_dt);

  auto value = m_tween->getValue();
  auto x = m_pixel_pos.x + (value * m_movement.x);
  auto y = m_pixel_pos.y - (value * m_movement.y);
  m_entity->m_x = x;
  m_entity->m_y = y;
  m_entity->m_sprite.setPosition(x, y);

  if (m_tween->isFinished()) {
    m_controller->change("wait");
  }

  return false;
};

void MoveState::exit() {
  m_entity->m_tile_x = m_entity->m_tile_x + m_movement.x;
  m_entity->m_tile_y = m_entity->m_tile_y + m_movement.y;

  // 'Teleport' cause this will be deleted later
  // auto vec = m_map->tileToPixel(m_entity->m_tile_x, m_entity->m_tile_y);
  // m_entity->m_sprite.setPosition(vec.x, vec.y);
};

