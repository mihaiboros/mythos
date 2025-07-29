#ifndef __HERA_KEYMAP_H__
#define __HERA_KEYMAP_H__

#include <cstdint>

namespace hera
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
   * @brief Set the key state
   * @param sys_key System key id
   * @param pressed Pressed state
   */
  void set_key(uint8_t sys_key, bool pressed);

  /**
   * @brief Set the key state
   * @param key Key name
   * @param pressed Pressed state
   */
  void set_key(Key::Alnum key, bool pressed);

  /**
   * @brief Set the key state
   * @param key Key name
   * @param pressed Pressed state
   */
  void set_key(Key::Special key, bool pressed);

  /**
   * @brief Check if key is pressed
   * @param sys_key System key id
   * @return Key state
   */
  bool is_pressed(uint8_t sys_key) const;

  /**
   * @brief Check if key is pressed
   * @param key Key name
   * @return Key state
   */
  bool is_pressed(Key::Alnum key) const;

  /**
   * @brief Check if key is pressed
   * @param key Key name
   * @return Key state
   */
  bool is_pressed(Key::Special key) const;

  /**
   * @brief Release key
   * @param sys_key System key id
   */
  void release(uint8_t sys_key);

  /**
   * @brief Release key
   * @param key Key name
   */
  void release(Key::Alnum key);

  /**
   * @brief Release key
   * @param key Key name
   */
  void release(Key::Special key);

private:

  /**
   * @brief Print the last pressed key, used for debug
   */
  void print_last();

  // Keyboard state
  bool m_state[256] = {false};
  // Keboard mapping
  uint8_t m_names[Key::special_keys_count] = {0};
};



inline void Keymap::set_key(uint8_t sys_key, bool pressed)
{
  m_state[sys_key] = pressed;
}


inline void Keymap::set_key(Key::Alnum key, bool pressed)
{
  m_state[key] = pressed;
}



inline void Keymap::set_key(Key::Special key, bool pressed)
{
  m_state[m_names[key]] = pressed;
}



inline bool Keymap::is_pressed(uint8_t sys_key) const
{
  return m_state[sys_key];
}



inline bool Keymap::is_pressed(Key::Alnum key) const
{
  return m_state[key];
}



inline bool Keymap::is_pressed(Key::Special key) const
{
  return m_state[m_names[key]];
}



inline void Keymap::release(uint8_t sys_key)
{
  m_state[sys_key] = false;
}


inline void Keymap::release(Key::Alnum key)
{
  m_state[key] = false;
}



inline void Keymap::release(Key::Special key)
{
  m_state[m_names[key]] = false;
}

} // namespace hera

#endif //__HERA_KEYMAP_H__
