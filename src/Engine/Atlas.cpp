#include "Atlas.hpp"

Engine::Tileset::Tileset(Engine::Application* t_app, const std::string t_file_path) {
  auto lines = Helper::getFileLines(t_file_path);

  for (auto iter = lines.begin(); iter < lines.end(); iter++) {
    std::istringstream iss(*iter);
    std::string type, texture_manifest_key;
    iss >> type;

    if (type == "id") iss >> id;
    else if (type == "texture") {
      iss >> texture_manifest_key;
      texture = t_app->getTexture(texture_manifest_key);
    }
    else if (type == "data") iss >> columns >> rows >> tile_height >> tile_width >> margin_x >> margin_y >> spacing;
  }

  uvs = Helper::getTileRects(columns, rows, tile_height, tile_width, margin_x, margin_y, spacing);
}

// Engine::Atlas::Atlas(Engine::AssetProvider& t_asset_provider, const std::string t_manifest_key)
  // : Engine::Atlas::Atlas(t_asset_provider.getAtlas(t_manifest_key)) { }

Engine::Atlas::Atlas(const std::string t_file_path) {
  m_data_file = t_file_path;

  std::vector<std::string> file_vec = Helper::getFileLines(t_file_path);

  for (auto iter = file_vec.begin(); iter < file_vec.end(); iter++) {
    std::istringstream iss(*iter);
    std::string type;
    iss >> type;

    if (type == "id") id = iss.str();
    else if (type == "name") name = iss.str();
    else if (type == "data") iss >> m_width >> m_height >> m_tile_width >> m_tile_height >> can_save;
    else if (type == "trig") {
      std::string trig_name;
      uint x, y;
      iss >> trig_name >> x >> y;
      m_triggers[coordToIndex(x, y)] = trig_name;
    // } else if (type == "ttrig") {
    //   std::string trig_name, enter, exit, use;
    //   iss >> trig_name >> enter >> exit >> use;
    //   m_triggers[coordToIndex(x, y)] = trig_name;
    } else if (type == "tileset") {
      uint first_tile;
      std::string tileset;
      iss >> first_tile >> tileset;
      m_tilesets[first_tile] = tileset;
    } else if (type == "layer") {
      Layer l;
      iss >> l.name;

      // We know the next three lines for a layer is the layer sectional data
      // So just advance the iterator and set the data
      uint val;
      iter++;
      iss = std::istringstream(*iter);
      while (iss >> val) l.base.push_back(val);

      iter++;
      iss = std::istringstream(*iter);
      while (iss >> val) l.decoration.push_back(val);

      iter++;
      iss = std::istringstream(*iter);
      while (iss >> val) l.collision.push_back(val);

      m_layers.push_back(l);
    }
  }

}

