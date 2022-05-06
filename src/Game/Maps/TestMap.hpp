#pragma once

#include "Engine/Atlas.hpp"

namespace Maps {
  class TestMap : public Engine::Atlas {
    public:
      TestMap() : Engine::Atlas("assets/maps/dungeon.atlas") {};
  };
}
