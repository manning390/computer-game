#pragma once

#include <functional>

namespace Engine {
  typedef std::function<void (void)> TriggerFn;
  class Trigger {
    public:
      // Trigger(TriggerDef t_def) ;

      TriggerFn m_on_enter = EmptyFn;
      TriggerFn m_on_exit = EmptyFn;
      TriggerFn m_on_use = EmptyFn;

    protected:
      const TriggerFn EmptyFn = [](){};
  };
};
