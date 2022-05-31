#include "Character.hpp"

Engine::Character::Character(Engine::Application& t_app, const Engine::CharacterDef& t_def, std::shared_ptr<Engine::Map> t_map)
  : m_map(t_map), m_anims(t_def.anims) {

  m_entity = std::make_shared<Engine::Entity>(t_app, t_def.entity);
  m_entity->setTilePos(t_def.entity.tile_x, t_def.entity.tile_y, t_map);

  for(auto& [k, v] : t_def.states) {
    auto state = v(this, t_map);
    assert(state);
    assert(!m_states.count(k) && "State key already in use");
    m_states[k] = state;
  }
  m_controller = std::make_shared<Engine::StateMachine>(m_states);

  assert(m_states.count(t_def.state) && "Initial State not present in Character states");
  m_controller->change(t_def.state);
  m_default_state = t_def.state;
};
