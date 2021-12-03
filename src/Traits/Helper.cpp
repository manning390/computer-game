#include "Helper.hpp"

#include "Constant.hpp"

std::vector<sf::IntRect> Helper::getTileRects(
    const uint t_cols,
    const uint t_rows,
    const uint t_tile_width,
    const uint t_tile_height,
    const uint t_margin_x = 0,
    const uint t_margin_y = 0,
    const uint t_spacing = 0) {
  std::vector<sf::IntRect> rects;

  int x, y;

  for(uint j = 0; j < t_rows; ++j) {
    for(uint i = 0; i < t_cols; ++i) {

      x = t_margin_x + i * (t_tile_width + t_spacing);
      y = t_margin_y + j * (t_tile_height + t_spacing);

      rects.push_back(sf::IntRect(x, y, t_tile_width, t_tile_height));
    }

  }

  return rects;
}

std::string Helper::stripPath(std::string t_s)  {
  return t_s.substr(t_s.find_last_of("/\\") + 1);
}

std::string Helper::stripFile(std::string t_s) {
  return t_s.substr(0, t_s.find_last_of("/\\") + 1);
}

std::vector<std::string> Helper::getFileLines(const std::string t_file_path) {
  std::vector<std::string> file_vec;
  std::ifstream file(t_file_path);

  if (file.is_open()) {
    for(std::string line; std::getline(file, line);) {
      if (line[0] == '#') continue;
      file_vec.push_back(line);
    }
    file.close();
  } else {
    LOG_ERROR("Unable to load file: {}", t_file_path);
    std::exit(1);
  }

  return file_vec;
}
