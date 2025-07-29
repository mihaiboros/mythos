#ifndef __WINGL_H__
#define __WINGL_H__

// Windows defines
#ifndef WINGDIAPI
#define WINGDIAPI __declspec(dllimport)
#endif

#ifndef APIENTRY
#define APIENTRY __stdcall
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

// TODO extensions

#endif //__WINGL_H__
