#include "keymap.h"

#include <algorithm>
#include <Windows.h>

namespace poc
{

Keymap::Keymap()
{
  mnames[Key::Num0] = VK_NUMPAD0;
  mnames[Key::Num1] = VK_NUMPAD1;
  mnames[Key::Num2] = VK_NUMPAD2;
  mnames[Key::Num3] = VK_NUMPAD3;
  mnames[Key::Num4] = VK_NUMPAD4;
  mnames[Key::Num5] = VK_NUMPAD5;
  mnames[Key::Num6] = VK_NUMPAD6;
  mnames[Key::Num7] = VK_NUMPAD7;
  mnames[Key::Num8] = VK_NUMPAD8;
  mnames[Key::Num9] = VK_NUMPAD9;

  mnames[Key::Subtract] = VK_SUBTRACT;
  mnames[Key::Add] = VK_ADD;
  mnames[Key::Divide] = VK_DIVIDE;
  mnames[Key::Multiply] = VK_MULTIPLY;
  mnames[Key::Decimal] = VK_DECIMAL;

  mnames[Key::Minus] = VK_OEM_MINUS;
  mnames[Key::Equal] = VK_OEM_PLUS;
  mnames[Key::Tilda] = VK_OEM_3;
  mnames[Key::Opened] = VK_OEM_4;
  mnames[Key::Closed] = VK_OEM_6;
  mnames[Key::Backslash] = VK_OEM_5;
  mnames[Key::Semicolon] = VK_OEM_1;
  mnames[Key::Apostrophe] = VK_OEM_7;
  mnames[Key::Comma] = VK_OEM_COMMA;
  mnames[Key::Period] = VK_OEM_PERIOD;
  mnames[Key::Slash] = VK_OEM_2;
  mnames[Key::Space] = VK_SPACE;
  mnames[Key::Tab] = VK_TAB;

  mnames[Key::Escape] = VK_ESCAPE;
  mnames[Key::Backspace] = VK_BACK;
  mnames[Key::Caps] = VK_CAPITAL;
  mnames[Key::Enter] = VK_RETURN;
  mnames[Key::Shift] = VK_SHIFT;
  mnames[Key::Ctrl] = VK_CONTROL;

  mnames[Key::Left] = VK_LEFT;
  mnames[Key::Up] = VK_UP;
  mnames[Key::Right] = VK_RIGHT;
  mnames[Key::Down] = VK_DOWN;

  mnames[Key::Delete] = VK_DELETE;
  mnames[Key::Insert] = VK_INSERT;
  mnames[Key::Home] = VK_HOME;
  mnames[Key::Pgup] = VK_PRIOR;
  mnames[Key::Pgdn] = VK_NEXT;
  mnames[Key::End] = VK_END;

  mnames[Key::F1] = VK_F1;
  mnames[Key::F2] = VK_F2;
  mnames[Key::F3] = VK_F3;
  mnames[Key::F4] = VK_F4;
  mnames[Key::F5] = VK_F5;
  mnames[Key::F6] = VK_F6;
  mnames[Key::F7] = VK_F7;
  mnames[Key::F8] = VK_F8;
  mnames[Key::F9] = VK_F9;
  mnames[Key::F10] = VK_F10;
  mnames[Key::F11] = VK_F11;
  mnames[Key::F12] = VK_F12;

  mnames[Key::Pause] = VK_PAUSE;
  mnames[Key::Print] = VK_PRINT;
  mnames[Key::Numlock] = VK_NUMLOCK;
  mnames[Key::Scroll] = VK_SCROLL;
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

  bool* end = mstate + sizeof(mstate);
  bool* pos = std::find(mstate, end, true);
  if (end == pos)
  {
    return;
  }

  static char str[30] = {0};
  *pos = false;

  int name = static_cast<int>(pos - mstate);
  if (name >= Key::K0 && name <= Key::K9 || name >= Key::A && name <= Key::Z)
  {
    sprintf_s(str, sizeof(str), "Key: %c \n", name);
    OutputDebugStringA(str);
  }
  else
  {
    uint8_t* nend = mnames + Key::special_keys_count;
    uint8_t* npos = std::find(mnames, nend, name);
    if (npos != nend)
    {
      int id = static_cast<int>(npos - mnames);
      sprintf_s(str,
        sizeof(str),
        "Key: %s \n",
        (id >= 0 && id < Key::special_keys_count) ? desc[id] : "Wrong ID!");
      OutputDebugStringA(str);
    }
  }
#endif
}

} // namespace poc
