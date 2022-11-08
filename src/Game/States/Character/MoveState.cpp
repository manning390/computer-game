#include "MoveState.hpp"

void MoveState::enter() {
  // LOG_TRACE("MoveState::enter()");
  auto entity = m_char->m_entity;
  m_anim = std::make_unique<Engine::Animation>(std::vector<int>(entity->m_start_frame));

  m_movement = m_char->m_direction;
  m_pixel_pos = entity->m_sprite.getPosition();

  if (m_movement.x == 1) {
    m_anim->setFrames(m_char->m_anims["right"]);
  } else if (m_movement.x == -1) {
    m_anim->setFrames(m_char->m_anims["left"]);
  } else if (m_movement.y == -1) {
    m_anim->setFrames(m_char->m_anims["up"]);
  } else if (m_movement.y == 1) {
    m_anim->setFrames(m_char->m_anims["down"]);
  }

  auto target_x = m_movement.x + entity->m_tile_x;
  auto target_y = m_movement.y + entity->m_tile_y;
  // LOG_DEBUG("move {}, {} -> {}, {}", entity->m_tile_x, entity->m_tile_y, target_x, target_y);
  if (m_map->isBlocked(target_x, target_y, 0)) {
    m_movement.x = 0;
    m_movement.y = 0;
    entity->setFrame(m_anim->frame());
    m_char->m_controller->change(m_char->m_default_state);
    return;
  }

  if (m_movement.x != 0 || m_movement.y != 0) {
    auto trigger = m_map->getTrigger(entity->m_tile_x, entity->m_tile_y, entity->m_layer);
    if (trigger) trigger->m_on_exit(trigger, entity);
  }

  entity->setTilePos(entity->m_tile_x + m_movement.x, entity->m_tile_y + m_movement.y, entity->m_layer, m_map);
  entity->m_sprite.setPosition(m_pixel_pos);


  // Check to see which direction we are moving, then get the tile width/height
  auto atlas = m_map->getAtlas();
  auto distance = m_movement.y == 0 ? atlas->m_tile_width : atlas->m_tile_width;
  m_tween = std::make_unique<Engine::Tween>(0, distance, m_move_speed, Tween::Linear);
};

bool MoveState::update(float t_dt) {
  auto entity = m_char->m_entity;
  m_tween->update(t_dt);
  m_anim->update(t_dt);

  auto value = m_tween->getValue();
  entity->m_x = m_pixel_pos.x + (value * m_movement.x);
  entity->m_y = m_pixel_pos.y + (value * m_movement.y);

  entity->m_sprite.setPosition(entity->m_x, entity->m_y);
  entity->setFrame(m_anim->frame());

  if (m_tween->isFinished()) {
    m_char->m_controller->change(m_char->m_default_state);
  }

  return true;
};

void MoveState::exit() {
  // LOG_TRACE("MoveState::exit()");
  auto entity = m_char->m_entity;
  auto trigger = m_map->getTrigger(entity->m_tile_x, entity->m_tile_y, entity->m_layer);
  if (trigger) trigger->m_on_enter(trigger, entity);
};

