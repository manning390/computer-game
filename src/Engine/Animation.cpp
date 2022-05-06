#include "Animation.hpp"

Engine::Animation::Animation(std::vector<int> t_frames, bool t_loop, float t_spf) {
  m_loop = t_loop;
  m_spf = t_spf;
  m_frames = t_frames;
  m_final_frame = t_frames.size()-1;
}

void Engine::Animation::update(float t_dt) {
  m_time += t_dt;
  if (m_time > m_spf) {
    ++m_index;
    m_time = 0;
    if (m_index >= m_frames.size()) {
      if(m_loop) {
        m_index = 0;
      } else {
        m_index = m_final_frame;
      }
    }
  }
}

void Engine::Animation::setFrames(std::vector<int> t_frames) {
  m_frames = t_frames;
  m_final_frame = t_frames.size()-1;
  m_index = std::min<unsigned int>(m_index, m_final_frame);
}

unsigned int Engine::Animation::frame(void) {
  return m_frames[m_index];
}

bool Engine::Animation::isFinished(void) {
  return (m_loop == false && m_index == m_final_frame);
}
