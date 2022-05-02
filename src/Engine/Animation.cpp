#include "Animation.hpp"

Engine::Animation::Animation(std::vector<int> t_frames, bool t_loop = true, float t_spf = 0.12) {
  m_loop = t_loop;
  m_spf = t_spf;
  m_frames = t_frames;
}

void Engine::Animation::update(float dt) {
  m_time += dt;
  if (m_time > m_spf) {
    ++m_index;
    m_time = 0;
    if (m_index > m_frames.size()) {
      if(m_loop) {
        m_index = 0;
      } else {
        m_index = m_frames.size();
      }
    }
  }
}

void Engine::Animation::setFrames(std::vector<int> t_frames) {
  m_frames = t_frames;
  m_index = std::min<unsigned int>(m_index, m_frames.size());
}


// void Engine::Animation::setFrames(int t_frames[]) {
  // m_frames = std::vector<int>(std::begin(t_frames), std::end(t_frames));
  // m_index = std::min<unsigned int>(m_index, m_frames.size());
// }

unsigned int Engine::Animation::frame(void) {
  return m_frames[m_index];
}

bool Engine::Animation::isFinished(void) {
  return (m_loop == false && m_index == m_frames.size());
}
