#pragma once

#include "Tazel/Events/Event.hpp"

#include <sstream>

namespace Tazel {

  class KeyEvent : public Event
  {
  public:
    inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:

    KeyEvent(int scancode, int keycode) : m_ScanCode(scancode), m_KeyCode(keycode) {}

    int m_ScanCode;
    int m_KeyCode;
  };

  class KeyPressedEvent : public KeyEvent
  {
  public:
    KeyPressedEvent(int scancode, int keycode, int repeatCount)
      : KeyEvent(scancode, keycode), m_RepeatCount(repeatCount) {}

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override
    {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_KeyCode << " keycode, " << m_ScanCode << " scancode" << " (" << m_RepeatCount << " repeats)";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
    private:
    int m_RepeatCount;
  };

  class KeyReleasedEvent : public KeyEvent
  {
  public:
    KeyReleasedEvent(int scancode, int keycode)
      : KeyEvent(scancode, keycode) {}

    std::string ToString() const override
    {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << m_KeyCode << " keycode, " << m_ScanCode << " scancode";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };
}
