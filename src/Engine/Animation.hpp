#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Log.hpp"

namespace Engine {
  class Animation {
    public:
      Animation(std::vector<int> t_frames, bool t_loop = true, float t_spf = 0.12);

      ~Animation() = default;

      void update(float t_dt);
      void setFrames(std::vector<int> t_frames);
      void setFrames(int t_frames[]);
      unsigned int frame(void);
      bool isFinished(void);
    private:
      bool m_loop;
      float m_spf;
      float m_time = 0;
      unsigned int m_index = 0;
      std::vector<int> m_frames;
      unsigned int m_final_frame;

  };
}
