#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Constant.hpp"
#include "Bitmask.hpp"

namespace Engine {
  enum class EventType {
    Keyboard = 0,
    Mouse = 1
  };

  struct ActionBinding {
    uint id;
    std::pair<EventType, EventType> event_types;
    std::pair<uint, uint> bindings;
  };

  class Input {
    public:
      Input(std::vector<ActionBinding> t_action_bindings);

      bool isActionPressed(uint t_action);
      bool isActionJustPressed(uint t_action);
      bool isActionJustReleased(uint t_action);

      std::vector<ActionBinding> getActionBindings(void);
      void setActionBindings(std::vector<ActionBinding> t_action_bindings);

      ActionBinding getActionBinding(uint t_action);
      void setActionBinding(ActionBinding t_action_binding);

      void update();

    protected:
      Engine::Bitmask m_current_frame_keys;
      Engine::Bitmask m_last_frame_keys;
      std::vector<ActionBinding> m_action_bindings;

      bool isActionBindingPressed(Engine::ActionBinding t_action_binding);
      bool isBindingPressed(EventType t_event_type, uint t_binding);
  };
}
