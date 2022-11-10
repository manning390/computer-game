#include "Application.hpp"
#include "Atlas.hpp"

void Engine::Application::processArguments(int argc, const char **argv) {
  LOG_TRACE("Engine::Application::processArguments()");

  if (argc < 2) return; // Don't process if there isn't any (./game always present)

  // Setting a seed with second arg
  std::istringstream reader(argv[1]);
  reader >> m_seed;
}

void Engine::Application::init() {
  LOG_TRACE("Engine::Application::init()");

  // Create window
  m_window = std::make_shared<Engine::Window>();
  m_frame_time = sf::seconds(1.0 / m_window->getFps());

  // Seed random
  seedRandom();

  // Load assets
  loadTextures();
  loadTilesets();

  // Load input
  loadBindings();

  // Load defs
  loadEntityDefs();
  loadCharacterDefs();

  // Initiate the state stack
  m_stack = std::make_shared<Engine::StateStack>();
}

void Engine::Application::seedRandom() {
  LOG_TRACE("Engine::Application::seedRand()");

  // If no seed has been set 
  if (m_seed == 0) m_seed = time(0);

  LOG_INFO("Seeded with {}", m_seed);
  srand(m_seed);
}

void Engine::Application::quit() {
  m_running = false;
}

int Engine::Application::run() {
  // Setup anything that we need setup
  init();

  // Throw our first state on the stack
  createInitialState();

  // Run loop
  loop();

  return Engine::NoError;
}

void Engine::Application::loop() {
  LOG_TRACE("Engine::Application::loop()");

  sf::Time previous = m_clock.getElapsedTime();
  sf::Time lag = sf::Time::Zero;

  while(m_running && m_window->isOpen() && !m_stack->isEmpty()) {
    sf::Time current = m_clock.getElapsedTime();
    sf::Time elapsed = current - previous;
    previous = current;
    lag += elapsed;

    // Process Input
    m_window->pollEvent(m_event);
    // Don't capture input if the window is not active
    if(m_window->isActive()) {
      m_input->update();
      m_stack->handleInput(m_input);
    }

    while (lag >= m_frame_time) {
      m_stack->update(m_frame_time.asSeconds());
      lag -= m_frame_time;
    }

    // Reset the window
    m_window->reset();

    // Render
    m_stack->render(m_window);

    // Display the new buffer
    m_window->display();
  }
}

void Engine::Application::loadTilesets() {
 LOG_TRACE("Engine::Application::loadTilesets()");

  auto lines = Helper::getFileLines(m_tilesets_manifest_path);
  for (auto line : lines) {
    std::string file_path = line;

    // Instead of the manifest key, lets use what's in the tileset
    auto tileset = std::make_shared<Engine::Tileset>(Engine::Tileset(this, file_path));

    m_tilesets[tileset->id] = tileset;
    LOG_INFO("Loaded tileset {} -> {}", file_path, tileset->id);
  }
}

void Engine::Application::loadTextures() {
  LOG_TRACE("Engine::Application::loadTextures()");

  auto lines = Helper::getFileLines(m_textures_manifest_path);
  for (auto line : lines) {
    std::istringstream iss(line);
    std::string key, file_path;
    iss >> key >> file_path;

    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(file_path);

    m_textures[key] = texture;
    LOG_INFO("Loaded texture: {} -> {}", file_path, key);
  }
}

std::shared_ptr<sf::Texture> Engine::Application::getTexture(std::string t_key) const {
  // LOG_TRACE("Engine::Application::getTexture({})", t_key);

  auto tex = m_textures.find(t_key);
  assert(tex != m_textures.end() && "Texture not defined on fetch");
  return tex->second;
}

std::shared_ptr<Engine::Tileset> Engine::Application::getTileset(std::string t_key) const {
  // LOG_TRACE("Engine::Application::getTileset({})", t_key);

  auto tileset = m_tilesets.find(t_key);
  assert(tileset != m_tilesets.end() && "Tileset not defined on fetch");
  return tileset->second;
}

Engine::EntityDef Engine::Application::getEntity(std::string t_key) const {
  // LOG_TRACE("Engine::Application::getEntity({})", t_key);

  auto def = m_entity_defs.find(t_key);
  assert(def != m_entity_defs.end() && "EntityDef not defined on fetch");
  return def->second;
}

Engine::CharacterDef Engine::Application::getCharacter(std::string t_key) const {
  // LOG_TRACE("Engine::Application::getCharacter({})", t_key);

  auto def = m_character_defs.find(t_key);
  assert(def != m_character_defs.end() && "CharacterDef not defined on fetch");
  return def->second;
}

void Engine::Application::loadBindings() {
  LOG_TRACE("Engine::Application::loadBindings()");

  m_input = std::make_shared<Engine::Input>(m_default_bindings, m_window);
  // auto lines = Helper::getFileLines(m_bindings_path);

  // // File exists? Load it
  // // File doesn't exist, use defaults
  // uint action = 0;
  // for (auto line : lines) {
    // std::istringstream iss(line);
    // std::

    // ++action;
  // }

  for (auto action : m_input->getBindings()) action.debug();
}

void Engine::Application::loadEntityDefs() {
  LOG_TRACE("Engine::Application::loadEntityDefs()");

  auto lines = Helper::getFileLines(m_entity_defs_path);
  for (auto line : lines) {
    if (line[0] == '#' || line == "") continue;
    std::istringstream iss(line);
    std::string id, tileset;
    uint sf, tx, ty, l, w, h;
    iss >> id >> tileset >> sf >> tx >> ty >> l >> w >> h;

    m_entity_defs[id] = (Engine::EntityDef){id, m_tilesets.at(tileset), sf, tx, ty, l, w, h};
    LOG_INFO("Loaded entity: {}", id);
  }

}

void Engine::Application::loadCharacterDefs() {
  LOG_TRACE("Engine::Application::loadCharacterDefs()");

  auto lines = Helper::getFileLines(m_character_defs_path);
  for (auto iter = lines.begin(); iter < lines.end(); iter++) {
    if ((*iter)[0] == '#' || (*iter) == "") continue;
    Engine::CharacterDef char_def;

    std::istringstream iss(*iter);
    std::string entity_key, sanity_check;
    std::vector<std::string> states;
    int anim_count, dir_x = 0, dir_y = 1;

    // Load the first initial data of a character
    iss >> char_def.id >> entity_key >> anim_count >> char_def.initial_state;
    char_def.entity = m_entity_defs[entity_key];

    // Check if dir is there, if not, we have defaults
    if (!iss.eof()) iss >> dir_x >> dir_y;
    char_def.initial_direction = {dir_x, dir_y};

    // States
    iter++;
    iss = std::istringstream(*iter);
    iss >> sanity_check;
    assert(sanity_check == "states" && "Character Def data was not in expected format: states");
    std::string state_key;
    while(iss >> state_key) {
      assert(m_state_factories.find(state_key) != m_state_factories.end() && "Character Def state data was not found in state factories");
      char_def.states[state_key] = m_state_factories[state_key];
    }

    // Anims
    for (int i = 0; i < anim_count; ++i) {
      iter++;
      iss = std::istringstream(*iter);
      iss >> sanity_check;
      assert(sanity_check == "anim" && "Character Def data was not in expected format: anim");
      std::string anim_name;
      std::vector<int> frame_data;
      int frame;
      iss >> anim_name;
      while(iss >> frame) frame_data.push_back(frame);
      char_def.anims[anim_name] = frame_data;
    }

    m_character_defs[char_def.id] = char_def;
    LOG_INFO("Loaded character: {}", char_def.id);
  }

}

