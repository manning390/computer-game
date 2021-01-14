#include "Helper.hpp"

std::vector<sf::IntRect> Helper::getTileRects(
    const uint t_tile_width,
    const uint t_tile_height,
    const uint t_cols,
    const uint t_rows,
    const uint t_margin = 0,
    const uint t_spacing = 0) {
  std::vector<sf::IntRect> rects;

  int x, y;

  // int k = -1;
  for(uint j = 0; j < t_rows; ++j) {
    for(uint i = 0; i < t_cols; ++i) {

      x = t_margin + i * (t_tile_width + t_spacing);
      y = t_margin + j * (t_tile_height + t_spacing);

      rects.push_back(sf::IntRect(x, y, t_tile_width, t_tile_height));
      // std::cout << "k: " << ++k << " " << x << " " << y << " " << std::endl;
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
