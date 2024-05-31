#ifndef __SYSGL_H__
#define __SYSGL_H__

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

#endif //__SYSGL_H__
