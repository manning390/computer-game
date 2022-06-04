#include "Character.hpp"
#include "Entity.hpp"

Engine::Character::Character(const Engine::CharacterDef& t_def, Engine::Map* t_map)
  : m_def(t_def), m_map(t_map), m_anims(t_def.anims) {

  m_entity = std::make_shared<Engine::Entity>(t_def.entity);

  m_direction = t_def.initial_direction;
  m_default_state = t_def.initial_state;

  for(auto& [k, v] : t_def.states) {
    auto state = v(this, t_map);
    assert(state);
    assert(!m_states.count(k) && "State key already in use");
    m_states[k] = state;
  }
  m_controller = std::make_shared<Engine::StateMachine>(m_states);

  assert(m_states.count(t_def.initial_state) && "Initial State not present in Character states");
  m_controller->change(t_def.initial_state);
};
