#pragma once

#include <string>

namespace Engine {
  /**
   * @brief Used to create actual entity classes
   *
   */
  struct EntityDef {
    std::string tileset; // manifest key
    uint start_frame;
    uint tile_x; // Initial position
    uint tile_y; // Initial position
    uint layer; // Initial position
    uint width;  // Uses tile size if set 0
    uint height; // uses tile size if set 0
  };
}
