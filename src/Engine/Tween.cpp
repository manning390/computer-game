#include "Tween.hpp"

Engine::Tween::Tween(
    float t_start,
    float t_finish,
    float t_total_duration,
    std::function<float(float, float, float, float)> t_func
) :
  // m_func_is_4(true),
  m_func_4(t_func),
  m_start(t_start),
  m_total_duration(t_total_duration)
{
  m_distance = t_finish - t_start;
  m_current = t_start;
  m_time_passed = 0;
  m_is_finished = false;
}

Engine::Tween::Tween(
    float t_start,
    float t_finish,
    float t_total_duration
) :
  // m_func_is_4(true),
  m_func_4(::Tween::Linear),
  m_start(t_start),
  m_total_duration(t_total_duration)
{
  m_distance = t_finish - t_start;
  m_current = t_start;
  m_time_passed = 0;
  m_is_finished = false;
}

// Engine::Tween::Tween(
    // float t_start,
    // float t_finish,
    // float t_total_duration,
    // std::function<float(float, float, float, float, float, float)> t_func
// ) :
  // m_func_is_4(false),
  // m_func_6(t_func),
  // m_start(t_start),
  // m_total_duration(t_total_duration)
// {
  // m_distance = t_finish - t_start;
  // m_current = t_start;
  // m_time_passed = 0;
  // m_is_finished = false;
// };

bool Engine::Tween::isFinished(void) {
  return m_is_finished;
}

float Engine::Tween::getValue(void) {
  return m_current;
}

float Engine::Tween::finishValue() const {
  return m_start + m_distance;
}

void Engine::Tween::update(float t_dt) {
  m_time_passed += t_dt;
  // if (m_func_is_4)
    m_current = m_func_4(m_time_passed, m_start, m_distance, m_total_duration);
  // else
    // m_current = m_func_6();

  if (m_time_passed > m_total_duration) {
    m_current = m_start + m_distance;
    m_is_finished = true;
  }
}
