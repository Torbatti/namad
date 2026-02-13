/*
 * NILE 0.1.0
 *
 * Copyright (c) 2026 Arya Bakhtiari
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#if defined(__EMSCRIPTEN__)
# define NILE_WASM
# error "Platform Not implemented Yet!"
#endif

#if defined(__linux__) || defined(__gnu_linux__)
# define NILE_LINUX
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
# define NILE_WINDOWS
#endif

#if defined(__ANDROID__)
# define NILE_ANDROID
# error "Platform Not implemented Yet!"
#endif

#if !defined(NILE_ASSERT)
# include <assert.h>
# define NILE_ASSERT assert
#endif

#if defined(NILE_LINUX)
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

# if !defined(NILE_GFX_OPENGL) || !defined(NILE_GFX_VULKAN)
#  define NILE_GFX_OPENGL
# endif

#endif

#if defined(NILE_WINDOWS)
// @brief(AABI):
//   WIN32_LEAN_AND_MEAN:
//   defining it will speed up the build process,
//   it reduces the size of the Win32 header files by excluding some of the less used APIs
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <xinput.h>

# if !defined(NILE_GFX_OPENGL) || !defined(NILE_GFX_VULKAN) \
     || !defined(NILE_GFX_DIRECTX)
#  define NILE_GFX_OPENGL
# endif

#endif

#if defined(NILE_GFX_OPENGL)
# define GLAD_GL_IMPLEMENTATION // Enables Glad Gl

// # include "../../vendor-glad/v2.0.8/gl10.h" // Glad GL Core V1.0 Headers/Utils/Loaders
// # include "../../vendor-glad/v2.0.8/gl11.h" // Glad GL Core V1.1 Headers/Utils/Loaders
# include "../../vendor-glad/v2.0.8/gl21.h" // Glad GL Core V2.1 Headers/Utils/Loaders
// #include "../../vendor-glad/v2.0.8/gl33.h" // Glad GL Core V3.3 Headers/Utils/Loaders

# if defined(NILE_LINUX)
#  define GLAD_GLX_IMPLEMENTATION             // Enables Glad GLX
#  include "../../vendor-glad/v2.0.8/glx14.h" // Glad GLX Headers/Utils/Loaders
# endif

# if defined(NILE_WINDOWS)
#  define GLAD_WGL_IMPLEMENTATION             // Enables Glad WGL
#  include "../../vendor-glad/v2.0.8/wgl10.h" // Glad WGL Headers/Utils/Loaders
# endif

#endif

#if defined(__cplusplus) && !defined(__EMSCRIPTEN__)
extern "C"
{
#endif

#if defined(__cplusplus) && !defined(__EMSCRIPTEN__)
}
#endif
