#pragma once

typedef unsigned int uint;

namespace Engine {
  const unsigned int NoError = 0;
  const float AspectRatio = 16.0f / 9.0f;
  const unsigned int NativeWidth = 512;
  const unsigned int NativeHeight = 288;
  const unsigned int TileSize = 10;
}

namespace Texture {
  const int ForestAtlas = 0;
  const int DungeonAtlas = 1;
  const int MonstersAtlas = 2;
  const int FxAtlas = 3;
}
