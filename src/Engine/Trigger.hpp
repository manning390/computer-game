#pragma once

#include "Actions.hpp"

namespace Engine {
  class Trigger {
    public:
      Trigger(
        Actions::ActionFn t_enter = Actions::EmptyFn,
        Actions::ActionFn t_exit  = Actions::EmptyFn,
        Actions::ActionFn t_use   = Actions::EmptyFn)
        : m_on_enter(t_enter),
          m_on_exit(t_exit),
          m_on_use(t_use) {};
      ~Trigger() = default;

      Actions::ActionFn m_on_enter;
      Actions::ActionFn m_on_exit;
      Actions::ActionFn m_on_use;
  };
};
