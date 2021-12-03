#include "Bitmask.hpp"

Engine::Bitmask::Bitmask() : m_bits(0) {}

void Engine::Bitmask::setMask(Bitmask& t_other) {
  m_bits = t_other.getMask();
}

uint Engine::Bitmask::getMask() const {
  return m_bits;
}

bool Engine::Bitmask::getBit(int t_pos) const {
  return (m_bits & (1 << t_pos)) != 0;
}

void Engine::Bitmask::setBit(int t_pos, bool t_on) {
  if (t_on) {
    setBit(t_pos);
  } else {
    clearBit(t_pos);
  }
}

void Engine::Bitmask::setBit(int t_pos) {
  m_bits = m_bits | 1 << t_pos;
}

void Engine::Bitmask::clearBit(int t_pos) {
  m_bits = m_bits & ~(1 << t_pos);
}

void Engine::Bitmask::clear() {
  m_bits = 0;
}

std::string Engine::Bitmask::to_string() {
  return std::to_string(m_bits);
}

