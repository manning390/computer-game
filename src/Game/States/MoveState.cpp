#include "MoveState.hpp"

void MoveState::enter() {
  // LOG_TRACE("MoveState::enter()");

  m_movement = m_character->m_direction;
  m_pixel_pos = m_entity->m_sprite.getPosition();

  if (m_movement.x == 1) {
    m_anim->setFrames(m_character->m_anim_right);
  } else if (m_movement.x == -1) {
    m_anim->setFrames(m_character->m_anim_left);
  } else if (m_movement.y == -1) {
    m_anim->setFrames(m_character->m_anim_up);
  } else if (m_movement.y == 1) {
    m_anim->setFrames(m_character->m_anim_down);
  }

  auto target_x = m_movement.x + m_entity->m_tile_x;
  auto target_y = m_movement.y + m_entity->m_tile_y;
  if (m_map->isBlocked(0, target_x, target_y)) {
    m_movement.x = 0;
    m_movement.y = 0;
    m_entity->setFrame(m_anim->frame());
    m_controller->change("wait");
    return;
  }

  // Check to see which direction we are moving, then get the tile width/height
  auto atlas = m_map->getAtlas();
  auto distance = m_movement.y == 0 ? atlas->tile_width : atlas->tile_width;
  m_tween = std::make_unique<Engine::Tween>(0, distance, m_move_speed, Tween::Linear);
};

bool MoveState::update(float t_dt) {
  m_tween->update(t_dt);
  m_anim->update(t_dt);

  auto value = m_tween->getValue();
  m_entity->m_x = m_pixel_pos.x + (value * m_movement.x);
  m_entity->m_y = m_pixel_pos.y + (value * m_movement.y);

  m_entity->m_sprite.setPosition(m_entity->m_x, m_entity->m_y);
  m_entity->setFrame(m_anim->frame());

  if (m_tween->isFinished()) {
    m_controller->change("wait");
  }

  return true;
};

void MoveState::exit() {
  if (m_movement.x != 0 || m_movement.y != 0) {
    auto trigger = m_map->getTrigger(m_entity->m_tile_x, m_entity->m_tile_y, m_entity->m_layer);
    if (trigger) trigger->m_on_exit(trigger, m_entity);
  }

  m_entity->m_tile_x = m_entity->m_tile_x + m_movement.x;
  m_entity->m_tile_y = m_entity->m_tile_y + m_movement.y;

  // 'Teleport' cause this will be deleted later
  auto vec = m_map->tileToPixel(m_entity->m_tile_x, m_entity->m_tile_y);
  m_entity->m_sprite.setPosition(vec.x, vec.y);

  auto trigger = m_map->getTrigger(m_entity->m_tile_x, m_entity->m_tile_y, m_entity->m_layer);
  if (trigger) trigger->m_on_enter(trigger, m_entity);
};

