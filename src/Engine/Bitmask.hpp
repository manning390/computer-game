#pragma once

#include "Constant.hpp"

namespace Engine {
  class Bitmask {
    public:
      Bitmask(void);

      void setMask(Bitmask& t_other);

      uint getMask(void) const;

      bool getBit(int t_pos) const;

      void setBit(int t_pos, bool t_on);

      void setBit(int t_pos);

      void clearBit(int t_pos);

      void clear(void);

    private:
      uint m_bits;
  };
}
