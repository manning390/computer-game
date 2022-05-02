#include "MoveState.hpp"

void MoveState::enter() {
  // LOG_TRACE("MoveState::enter()");

  m_movement = m_character->m_direction;
  m_pixel_pos = m_entity->m_sprite.getPosition();

  auto atlas = m_map->getAtlas();
  // Check to see which direction we are moving, then get the tile width/height
  auto distance = m_movement.y == 0 ? atlas->tile_width : atlas->tile_width;
  m_tween = std::make_unique<Engine::Tween>(0, distance, m_move_speed, Tween::Linear);

  if (m_movement.x == 1) {
    m_anim->setFrames(m_character->m_anim_right);
    return;
  }
  if (m_movement.x == -1) {
    m_anim->setFrames(m_character->m_anim_left);
    return;
  }
  if (m_movement.y == -1) {
    m_anim->setFrames(m_character->m_anim_up);
    return;
  }
  if (m_movement.y == 1) {
    m_anim->setFrames(m_character->m_anim_down);
    return;
  }
};

bool MoveState::update(float t_dt) {
  m_tween->update(t_dt);
  m_anim->update(t_dt);

  auto value = m_tween->getValue();
  auto x = m_pixel_pos.x + (value * m_movement.x);
  auto y = m_pixel_pos.y + (value * m_movement.y);
  m_entity->m_x = x;
  m_entity->m_y = y;

  m_entity->m_sprite.setPosition(x, y);
  m_entity->setFrame(m_anim->frame());

  if (m_tween->isFinished()) {
    m_controller->change("wait");
  }

  return true;
};

void MoveState::exit() {
  m_entity->m_tile_x = m_entity->m_tile_x + m_movement.x;
  m_entity->m_tile_y = m_entity->m_tile_y + m_movement.y;

  // 'Teleport' cause this will be deleted later
  auto vec = m_map->tileToPixel(m_entity->m_tile_x, m_entity->m_tile_y);
  m_entity->m_sprite.setPosition(vec.x, vec.y);
};

