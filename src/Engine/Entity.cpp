#include "Entity.hpp"

Engine::Entity::Entity(Engine::Application & t_app, EntityDef & t_entity_def) {
  m_sprite = sf::Sprite();
  bob = sf::Sprite(
    *(t_app.getTexture("monsters")),
    monsters_tileset->uvs[1]
  );
}

