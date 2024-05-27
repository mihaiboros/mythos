#include "window.h"

#include <gl/GL.h>
#include <gl/GLU.h>

constexpr const char* class_name = "OpenGL";
static Window* window = nullptr;

Window* Window::create_once(
  const char* title, int width, int height, uint8_t bits, bool is_fullscreen)
{
  if (!window)
  {
    window = new Window;
    if (!window->create(title, width, height, bits, is_fullscreen))
    {
      delete window;
      window = nullptr;
    }
  }
  return window;
}



LRESULT CALLBACK Window::wndproc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if (!window)
  {
    return 0;
  }

  bool is_handled = true;
  switch (msg)
  {
    case WM_ACTIVATE:
      window->m_is_minimized = HIWORD(wparam);
      break;

    case WM_SYSCOMMAND:
      is_handled = SC_SCREENSAVE == wparam || SC_MONITORPOWER == wparam;
      break;

    case WM_CLOSE:
      PostQuitMessage(0);
      break;

    case WM_KEYDOWN:
      // todo
      break;

    case WM_KEYUP:
      // todo
      break;

    case WM_SIZE:
      window->resize(LOWORD(lparam), HIWORD(lparam));
      break;

    default:
      is_handled = false;
      break;
  }

  return is_handled ? 0 : DefWindowProc(wnd, msg, wparam, lparam);
}



Window::~Window()
{
  if (m_rc)
  {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_rc);
  }

  if (m_dc)
  {
    ReleaseDC(m_wnd, m_dc);
  }

  if (m_wnd)
  {
    DestroyWindow(m_wnd);
  }

  if (m_inst)
  {
    UnregisterClass(class_name, m_inst);
  }

  window = nullptr;
}



void Window::resize(int width, int height)
{
  glViewport(0, 0, width, height > 0 ? height : 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, static_cast<double>(width) / height, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void Window::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  SwapBuffers(m_dc);
}



bool Window::is_minimized() const
{
  return m_is_minimized;
}



bool Window::create(const char* title, int width, int height, uint8_t bits, bool is_fullscreen)
{
  uint32_t pixel_format = 0;
  WNDCLASS wc;
  DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD style = WS_OVERLAPPEDWINDOW;

  RECT rect{.left = 0, .top = 0, .right = width, .bottom = height};
  m_is_fullscreen = is_fullscreen;

  m_inst = GetModuleHandle(nullptr);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = wndproc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = m_inst;
  wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = nullptr;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = class_name;

  if (!RegisterClass(&wc))
  {
    return false;
  }

  if (m_is_fullscreen)
  {
    DEVMODE screen_settings;
    memset(&screen_settings, 0, sizeof(screen_settings));
    screen_settings.dmSize = sizeof(screen_settings);
    screen_settings.dmPelsWidth = width;
    screen_settings.dmPelsHeight = height;
    screen_settings.dmBitsPerPel = bits;
    screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&screen_settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      return false;
    }

    ex_style = WS_EX_APPWINDOW;
    style = WS_POPUP;
    ShowCursor(FALSE);
  }
  else
  {
    AdjustWindowRectEx(&rect, style, FALSE, ex_style);
  }

  m_wnd = CreateWindowEx(ex_style,
    class_name,
    title,
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
    0,
    0,
    rect.right - rect.left,
    rect.bottom - rect.top,
    nullptr,
    nullptr,
    m_inst,
    nullptr);

  if (!m_wnd)
  {
    return false;
  }

  static PIXELFORMATDESCRIPTOR pfd{.nSize = sizeof(PIXELFORMATDESCRIPTOR),
    .nVersion = 1,
    .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = bits,
    .cRedBits = 0,
    .cRedShift = 0,
    .cGreenBits = 0,
    .cGreenShift = 0,
    .cBlueBits = 0,
    .cBlueShift = 0,
    .cAlphaBits = 0,
    .cAlphaShift = 0,
    .cAccumBits = 0,
    .cAccumRedBits = 0,
    .cAccumGreenBits = 0,
    .cAccumBlueBits = 0,
    .cAccumAlphaBits = 0,
    .cDepthBits = 16,
    .cStencilBits = 0,
    .cAuxBuffers = 0,
    .iLayerType = PFD_MAIN_PLANE,
    .bReserved = 0,
    .dwLayerMask = 0,
    .dwVisibleMask = 0,
    .dwDamageMask = 0};

  m_dc = GetDC(m_wnd);
  if (!m_dc)
  {
    return false;
  }

  pixel_format = ChoosePixelFormat(m_dc, &pfd);
  if (0 == pixel_format)
  {
    return false;
  }

  if (!SetPixelFormat(m_dc, pixel_format, &pfd))
  {
    return false;
  }

  m_rc = wglCreateContext(m_dc);
  if (!m_rc)
  {
    return false;
  }

  if (!wglMakeCurrent(m_dc, m_rc))
  {
    return false;
  }

  ShowWindow(m_wnd, SW_SHOW);
  SetForegroundWindow(m_wnd);
  SetFocus(m_wnd);
  resize(width, height);

  return init();
}



bool Window::init()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0);
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_EQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  return true;
}
