#pragma once

#include "Constant.hpp"

/**
 * It's an enum, I swear. It's just also a uint.
 * It's fine.
 *
 * We're doing this in the first place to avoid converting to uints
 * everytime we make a call to the input class.
 */
namespace InputActions {
  const uint UP     = 1;
  const uint LEFT   = 2;
  const uint RIGHT  = 3;
  const uint DOWN   = 4;
  const uint A      = 5;
  const uint B      = 6;
  const uint START  = 7;
  const uint SELECT = 8;
};
