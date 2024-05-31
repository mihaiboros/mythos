#ifndef __POC_KEYMAP_H__
#define __POC_KEYMAP_H__

#include <cstdint>

namespace poc
{

struct Key
{
  enum Alnum
  {
    K0 = 0x30,
    K1,
    K2,
    K3,
    K4,
    K5,
    K6,
    K7,
    K8,
    K9,
    A = 0x41,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
  };

  enum Special
  {
    Num0 = 0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,

    Subtract,
    Add,
    Divide,
    Multiply,
    Decimal,

    Minus,
    Equal,
    Tilda,
    Opened,
    Closed,
    Backslash,
    Semicolon,
    Apostrophe,
    Comma,
    Period,
    Slash,
    Space,
    Tab,

    Escape,
    Backspace,
    Caps,
    Enter,
    Shift,
    Ctrl,

    Left,
    Up,
    Right,
    Down,

    Delete,
    Insert,
    Home,
    Pgup,
    Pgdn,
    End,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    Pause,
    Print,
    Numlock,
    Scroll,

    special_keys_count // keep last always, don't use as key
  };
};

class Keymap
{
public:

  /**
   * @brief Construct a new object
   */
  Keymap();

  /**
   * @brief Indexer operator to get key state
   * @param sys_key System key id to get
   * @return bool& Key state
   */
  bool& operator[](uint8_t sys_key);

  /**
   * @brief Indexer operator to get key state
   * @param key Name of the key to get
   * @return bool& Key state
   */
  bool& operator[](Key::Special key);

  /**
   * @brief Indexer operator to get key state
   * @param key Name of the key to get
   * @return bool& Key state
   */
  bool operator[](Key::Special key) const;

private:

  /**
   * @brief Print the last pressed key, used for debug
   */
  void print_last();

  // Keyboard state
  bool mstate[256] = {false};
  // Keboard mapping
  uint8_t mnames[Key::special_keys_count] = {0};
};



inline bool& Keymap::operator[](uint8_t sys_key)
{
  return mstate[sys_key];
}



inline bool& Keymap::operator[](Key::Special key)
{
  return mstate[mnames[key]];
}



inline bool Keymap::operator[](Key::Special key) const
{
  return mstate[mnames[key]];
}

} // namespace poc

#endif //__POC_KEYMAP_H__
