#include "../keymap.h"

#include <algorithm>
#include <Windows.h>

namespace hera
{

Keymap::Keymap()
{
  m_names[Key::Num0] = VK_NUMPAD0;
  m_names[Key::Num1] = VK_NUMPAD1;
  m_names[Key::Num2] = VK_NUMPAD2;
  m_names[Key::Num3] = VK_NUMPAD3;
  m_names[Key::Num4] = VK_NUMPAD4;
  m_names[Key::Num5] = VK_NUMPAD5;
  m_names[Key::Num6] = VK_NUMPAD6;
  m_names[Key::Num7] = VK_NUMPAD7;
  m_names[Key::Num8] = VK_NUMPAD8;
  m_names[Key::Num9] = VK_NUMPAD9;

  m_names[Key::Subtract] = VK_SUBTRACT;
  m_names[Key::Add] = VK_ADD;
  m_names[Key::Divide] = VK_DIVIDE;
  m_names[Key::Multiply] = VK_MULTIPLY;
  m_names[Key::Decimal] = VK_DECIMAL;

  m_names[Key::Minus] = VK_OEM_MINUS;
  m_names[Key::Equal] = VK_OEM_PLUS;
  m_names[Key::Tilda] = VK_OEM_3;
  m_names[Key::Opened] = VK_OEM_4;
  m_names[Key::Closed] = VK_OEM_6;
  m_names[Key::Backslash] = VK_OEM_5;
  m_names[Key::Semicolon] = VK_OEM_1;
  m_names[Key::Apostrophe] = VK_OEM_7;
  m_names[Key::Comma] = VK_OEM_COMMA;
  m_names[Key::Period] = VK_OEM_PERIOD;
  m_names[Key::Slash] = VK_OEM_2;
  m_names[Key::Space] = VK_SPACE;
  m_names[Key::Tab] = VK_TAB;

  m_names[Key::Escape] = VK_ESCAPE;
  m_names[Key::Backspace] = VK_BACK;
  m_names[Key::Caps] = VK_CAPITAL;
  m_names[Key::Enter] = VK_RETURN;
  m_names[Key::Shift] = VK_SHIFT;
  m_names[Key::Ctrl] = VK_CONTROL;

  m_names[Key::Left] = VK_LEFT;
  m_names[Key::Up] = VK_UP;
  m_names[Key::Right] = VK_RIGHT;
  m_names[Key::Down] = VK_DOWN;

  m_names[Key::Delete] = VK_DELETE;
  m_names[Key::Insert] = VK_INSERT;
  m_names[Key::Home] = VK_HOME;
  m_names[Key::Pgup] = VK_PRIOR;
  m_names[Key::Pgdn] = VK_NEXT;
  m_names[Key::End] = VK_END;

  m_names[Key::F1] = VK_F1;
  m_names[Key::F2] = VK_F2;
  m_names[Key::F3] = VK_F3;
  m_names[Key::F4] = VK_F4;
  m_names[Key::F5] = VK_F5;
  m_names[Key::F6] = VK_F6;
  m_names[Key::F7] = VK_F7;
  m_names[Key::F8] = VK_F8;
  m_names[Key::F9] = VK_F9;
  m_names[Key::F10] = VK_F10;
  m_names[Key::F11] = VK_F11;
  m_names[Key::F12] = VK_F12;

  m_names[Key::Pause] = VK_PAUSE;
  m_names[Key::Print] = VK_PRINT;
  m_names[Key::Numlock] = VK_NUMLOCK;
  m_names[Key::Scroll] = VK_SCROLL;
}



void Keymap::print_last()
{
#if 0
  static const char* desc[Key::special_keys_count] = {nullptr};
  if (!desc[0])
  {
    desc[Key::Num0] = "NUMPAD0";
    desc[Key::Num1] = "NUMPAD1";
    desc[Key::Num2] = "NUMPAD2";
    desc[Key::Num3] = "NUMPAD3";
    desc[Key::Num4] = "NUMPAD4";
    desc[Key::Num5] = "NUMPAD5";
    desc[Key::Num6] = "NUMPAD6";
    desc[Key::Num7] = "NUMPAD7";
    desc[Key::Num8] = "NUMPAD8";
    desc[Key::Num9] = "NUMPAD9";

    desc[Key::Subtract] = "SUBTRACT";
    desc[Key::Add] = "ADD";
    desc[Key::Divide] = "DIVIDE";
    desc[Key::Multiply] = "MULTIPLY";
    desc[Key::Decimal] = "DECIMAL";

    desc[Key::Minus] = "Minus";
    desc[Key::Equal] = "Equal";
    desc[Key::Tilda] = "Tilda";
    desc[Key::Opened] = "Opened";
    desc[Key::Closed] = "Closed";
    desc[Key::Backslash] = "Backslash";
    desc[Key::Semicolon] = "Semicolon";
    desc[Key::Apostrophe] = "Apostrophe";
    desc[Key::Comma] = "Comma";
    desc[Key::Period] = "Period";
    desc[Key::Slash] = "Slash";
    desc[Key::Space] = "SPACE";
    desc[Key::Tab] = "TAB";

    desc[Key::Escape] = "ESCAPE";
    desc[Key::Backspace] = "Backspace";
    desc[Key::Caps] = "Caps";
    desc[Key::Enter] = "Enter";
    desc[Key::Shift] = "SHIFT";
    desc[Key::Ctrl] = "CONTROL";

    desc[Key::Left] = "LEFT";
    desc[Key::Up] = "UP";
    desc[Key::Right] = "RIGHT";
    desc[Key::Down] = "DOWN";

    desc[Key::Delete] = "DELETE";
    desc[Key::Insert] = "INSERT";
    desc[Key::Home] = "HOME";
    desc[Key::Pgup] = "Pgup";
    desc[Key::Pgdn] = "Pgdn";
    desc[Key::End] = "END";

    desc[Key::F1] = "F1";
    desc[Key::F2] = "F2";
    desc[Key::F3] = "F3";
    desc[Key::F4] = "F4";
    desc[Key::F5] = "F5";
    desc[Key::F6] = "F6";
    desc[Key::F7] = "F7";
    desc[Key::F8] = "F8";
    desc[Key::F9] = "F9";
    desc[Key::F10] = "F10";
    desc[Key::F11] = "F11";
    desc[Key::F12] = "F12";

    desc[Key::Pause] = "PAUSE";
    desc[Key::Print] = "PRINT";
    desc[Key::Numlock] = "NUMLOCK";
    desc[Key::Scroll] = "SCROLL";
  }

  bool* end = m_state + sizeof(m_state);
  bool* pos = std::find(m_state, end, true);
  if (end == pos)
  {
    return;
  }

  static char str[30] = {0};
  *pos = false;

  int name = static_cast<int>(pos - m_state);
  if (name >= Key::K0 && name <= Key::K9 || name >= Key::A && name <= Key::Z)
  {
    sprintf_s(str, sizeof(str), "Key: %c \n", name);
    OutputDebugStringA(str);
  }
  else
  {
    uint8_t* nend = m_names + Key::special_keys_count;
    uint8_t* npos = std::find(m_names, nend, name);
    if (npos != nend)
    {
      int id = static_cast<int>(npos - m_names);
      sprintf_s(str,
        sizeof(str),
        "Key: %s \n",
        (id >= 0 && id < Key::special_keys_count) ? desc[id] : "Wrong ID!");
      OutputDebugStringA(str);
    }
  }
#endif
}

} // namespace hera
