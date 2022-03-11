#include "MoveState.hpp"

MoveState::MoveState(std::shared_ptr<Character> t_char, std::shared_ptr<Engine::Map> t_map)
  : m_character(t_char),
    m_map(t_map),
    m_entity(t_char->m_entity),
    m_controller(t_char->m_controller) { };

bool MoveState::update(float t_dt) {
  // m_tween->update(t_dt);

  // auto value = m_tween->getValue();
  // auto x = m_pixel_pos.x + (value * m_movement.x);
  // auto y = m_pixel_pos.y - (value * m_movement.y);
  // m_entity->m_x = x;
  // m_entity->m_y = y;
  // m_entity->m_sprite.setPosition(x, y);

  // if (m_tween->isFinished()) {
    // m_controller->change("wait");
  // }

  return false;
};

void MoveState::enter(MoveStateEnterParams t_data) {
  // m_movement = {t_data.x, t_data.y};
  // m_pixel_pos = m_entity->m_sprite.getPosition();
  // m_tween = std::make_unique<Engine::Tween>(0, m_tile_width, m_move_speed, Tween::Linear);
};

void MoveState::exit() {
  // m_entity->m_tile_x = m_entity->m_tile_x + m_movement.x;
  // m_entity->m_tile_y = m_entity->m_tile_y + m_movement.y;

  // // 'Teleport' cause this will be deleted later
  // auto vec = m_map->tileToPixel(m_entity->m_tile_x, m_entity->m_tile_y);
  // m_entity->m_sprite.setPosition(vec.x, vec.y);
};

