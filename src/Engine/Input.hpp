#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Log.hpp"
#include "Constant.hpp"
#include "Bitmask.hpp"
#include "Window.hpp"

namespace Engine {
  enum class EventType {
    Unknown  = -1,
    Keyboard =  0,
    Mouse    =  1,
  };

  class ActionBinding {
    public:
      ActionBinding(uint t_id, EventType t_event_type,   int t_binding);
      ActionBinding(uint t_id, EventType t_event_type_1, int t_binding_1,
                               EventType t_event_type_2, int t_binding_2);
      uint id; // Action's id, must match vector index
      std::pair<EventType, EventType> event_types;
      std::pair<int, int> bindings;

      void debug() const {
        auto typeToString = [](EventType t_type){
          switch (t_type) {
            case EventType::Keyboard: return "Key";
            case EventType::Mouse:    return "Mouse";
            default: return "Unknown";
          }
        };

        LOG_INFO("Action Binding id: {}, type: {}, binding: {}", id, typeToString(event_types.first), bindings.first);
        if (event_types.second != Engine::EventType::Unknown)
          LOG_INFO("Action Binding id: {}, type: {}, binding: {}", id, typeToString(event_types.second), bindings.second);
      };
  };

  class Input {
    public:
      Input(std::vector<ActionBinding> t_action_bindings, std::shared_ptr<Engine::Window> t_window);

      bool isActionPressed(uint t_action);
      bool isActionJustPressed(uint t_action);
      bool isActionJustReleased(uint t_action);

      std::vector<ActionBinding> getActionBindings(void);
      void setActionBindings(std::vector<ActionBinding> t_action_bindings);

      ActionBinding getActionBinding(uint t_action);
      void setActionBinding(ActionBinding t_action_binding);

      void update();

      sf::Vector2i getMousePosition() const; // World
      sf::Vector2i getViewMousePosition() const; // View

      Engine::Bitmask getBitmask();

      std::vector<ActionBinding> getBindings();

    protected:
      std::shared_ptr<Engine::Window> m_window;
      Engine::Bitmask m_current_frame_keys;
      Engine::Bitmask m_last_frame_keys;
      std::vector<ActionBinding> m_action_bindings;

      bool isActionBindingPressed(Engine::ActionBinding t_action_binding);
      bool isBindingPressed(EventType t_event_type, int t_binding);
  };
}
