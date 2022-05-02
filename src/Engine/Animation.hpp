#pragma once

#include <vector>
#include <array>
#include <algorithm>

namespace Engine {
  class Animation {
    public:
      Animation(std::vector<int> t_frames, bool t_loop, float t_spf);

      ~Animation() = default;

      void update(float dt);
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

  };
}
