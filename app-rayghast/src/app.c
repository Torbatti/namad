/*
 * Rayghast 0.1.0
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

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <math.h>
#define PI   3.14159
#define PIH  PI / 2
#define PI2H PI
#define PI3H 3 * PI / 2
#define PI4H 2 * PI

#define STATUS_ERROR 0

//
// BASE
//
#include <stdint.h>
// VARIABLE/STATIC
#define persist_local  static
#define persist_global static
// FUNCTION
#define fn          // NOTE(AABI): do we need this?
#define fn_internal static
#define fn_external extern
// UNSIGNED INT
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
// SIGNED INT
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
// FLOAT INT
typedef float  f32;
typedef double f64;
// BOOL
typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;
// Windows UTF-16 related
#ifdef _WIN32
typedef wchar_t wchar; // wide character , used in win api
typedef int32_t rune;  // unicode codepoint
#endif                 // _WIN32
// ENUM
#define enum8(type)  u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

//
// package includes
//
#include "../../package-nile/src/nile.h"

//
//
//
//
typedef struct {
  int X;
  int Y;
  int Width;
  int Height;
} entity;

typedef struct {
  uint8_t *Memory;
  uint64_t Size;
  uint32_t Width;
  uint32_t Height;
  uint32_t Pitch;
} Buffer;

//
//
//
//
//
//
typedef struct GamePlayer {
  f64 x;
  f64 y;
  f64 dx;
  f64 dy;
  f64 a;
  u32 width;
  u32 height;
  u32 step_size;
} GamePlayer;

typedef struct GameMap {
  u16 square_column;
  u16 square_row;
  u32 square_size;
} GameMap;

typedef struct AppWindow {
  u32         x;
  u32         y;
  u32         width;
  u32         height;
  const char *name;
} AppWindow;

//
//
//
//
//
//
persist_global GamePlayer player = {
    .x         = 200.0,
    .y         = 322.0,
    .dx        = 5,
    .dy        = 0,
    .a         = 0,
    .height    = 16,
    .width     = 16,
    .step_size = 8,
};

persist_global GameMap map = {
    .square_column = 8,
    .square_row    = 8,
    .square_size   = 64,
};

persist_global u8 map_board [] = {
    1, 1, 1, 1, 1, 1, 1, 1, //
    1, 0, 1, 0, 0, 0, 0, 1, //
    1, 0, 1, 0, 0, 0, 0, 1, //
    1, 0, 1, 0, 0, 0, 0, 1, //
    1, 0, 0, 0, 0, 0, 0, 1, //
    1, 0, 0, 0, 0, 1, 0, 1, //
    1, 0, 0, 0, 0, 0, 0, 1, //
    1, 1, 1, 1, 1, 1, 1, 1, //
};

persist_global AppWindow app_window = {
    .width  = 1024,
    .height = 512,
    .x      = 0,
    .y      = 0,
    .name   = "Raycaster",
};

//
//
//
//
void
draw_pixel(
    Buffer *buffer, int32_t start_x, int32_t start_y,
    uint32_t pixel_color
)
{}

void
draw_rectangle(
    Buffer *buffer, int32_t start_x, int32_t start_y,
    int32_t rect_width, int32_t rect_height, uint32_t rect_color
)
{}

void
draw_rectangle_simd(
    Buffer *buffer, int32_t start_x, int32_t start_y,
    int32_t rect_width, int32_t rect_height, uint32_t rect_color
)
{}

void
draw_line(
    Buffer *buffer, int32_t start_x, int32_t start_y, int32_t end_x,
    int32_t end_y, uint32_t line_color
)
{}

void
draw_line_antialias(
    Buffer *buffer, int32_t start_x, int32_t start_y, int32_t end_x,
    int32_t end_y, uint32_t line_color
)
{}

void
draw_triangle()
{}

void
draw_circle(
    Buffer *buffer, int32_t start_x, int32_t start_y, int32_t radius,
    uint32_t circle_color
)
{}

//
//
//
//
//

float
Clamp(float Min, float Value, float Max)
{
  if(Value < Min)
  {
    Value = Min;
  }
  else if(Value > Max)
  {
    Value = Max;
  }
  return Value;
}

void
DrawRect(
    Buffer *buffer, int32_t X, int32_t Y, int32_t Width, int32_t Height,
    uint32_t Color
)
{
  int32_t StartX = X;
  int32_t EndX   = X + Width;
  int32_t StartY = Y;
  int32_t EndY   = Y + Height;

  StartX = Clamp(0, StartX, buffer->Width);
  EndX   = Clamp(0, EndX, buffer->Width);

  StartY = Clamp(0, StartY, buffer->Height);
  EndY   = Clamp(0, EndY, buffer->Height);

  for(int Y = StartY; Y < EndY; Y++)
  {
    for(int X = StartX; X < EndX; X++)
    {
      uint32_t *Pixel = (uint32_t *)((uint32_t *)buffer->Memory
                                     + Y * buffer->Width + X);
      *Pixel          = Color;
    }
  }
}

//
// WARN(AABIB):
// this is such an unsafe piece of function!!!
// DoRender can write outside of buffer!!!
//
void
DoRender(Buffer *buffer, GamePlayer *player)
{
  // Draw Phase: Draw Background
  DrawRect(buffer, 0, 0, buffer->Width, buffer->Height, 0xffede0d4);

  // Draw Phase: Draw Map Squares
  u8 msx, msy;
  for(msy = 0; msy < map.square_row; msy++)
  {
    for(msx = 0; msx < map.square_column; msx++)
    {
      if(map_board [msy * map.square_column + msx] == 1)
      {
        DrawRect(
            buffer, msx * map.square_size + 1,
            msy * map.square_size + 1, map.square_size - 1,
            map.square_size - 1, 0xffa68a64
        );
      }
    }
  }

  // Draw Phase: Draw Lines
  // printf("%f,%f,%f",player->a,player->dx,player->dy);

  // Draw Phase: Draw Player Rays
  DrawRect(
      buffer, player->x + player->dx * 10, player->y + player->dy * 10,
      player->width / 2, player->height / 2, 0xffc1121f
  );

  int ray, map_x, map_y, map_p, dof;
  f64 ray_x, ray_y, ray_a, xo, yo;
  ray_a = player->a;
  for(ray = 0; ray < 1; ray++)
  {
    // // Check Horizontal Line
    // dof      = 0;
    // f64 aTan = -1 / tan(ray_a);

    // if(ray_a > PI) // Looking Down
    // {
    //   ray_y = (((int)player->y >> 6) << 6) - 0.0001;
    //   ray_x = (player->y - ray_y) * aTan + player->x;
    //   yo    = -64;
    //   xo    = -yo * aTan;
    // }
    // if(ray_a < PI) // Looking Up
    // {
    //   ray_y = (((int)player->y >> 6) << 6) + 64;
    //   ray_x = (player->y - ray_y) * aTan + player->x;
    //   yo    = 64;
    //   xo    = -yo * aTan;
    // }
    // if(ray_a == 0 || ray_a == PI)  // Looking Right or Left
    // {
    //   ray_x = player->x;
    //   ray_y = player->y;
    //   dof   = 8;
    // }
    // while(dof < 8)
    // {
    //   map_x = (int)(ray_x) >> 6;
    //   map_y = (int)(ray_y) >> 6;
    //   map_p = map_y * map.square_column + map_x;
    //   if(map_p < map.square_row * map.square_column
    //      && map_board [map_p] == 1)
    //   {
    //     dof = 8;
    //   }
    //   else
    //   {
    //     ray_x += xo;
    //     ray_y += yo;
    //     dof   += 1;
    //   }
    // }
    // DrawRect(
    //     Buffer, ray_x, ray_y, player->width / 2, player->height / 2,
    //     0xfffb8500
    // );

    // Check Vertical Line
    dof      = 0;
    f64 nTan = -tan(ray_a);
    if(PIH < ray_a && PI3H > ray_a) // Looking Left
    {
      ray_x = (((int)player->x >> 6) << 6) - 0.0001;
      ray_y = (player->x - ray_x) * nTan + player->y;
      xo    = -64;
      yo    = -xo * nTan;
    }
    if(PIH > ray_a || PI3H < ray_a) // Looking Right
    {
      ray_x = (((int)player->x >> 6) << 6) + 64;
      ray_y = (player->x - ray_x) * nTan + player->y;
      xo    = 64;
      yo    = -xo * nTan;
    }
    if(ray_a == 0 || ray_a == PI) // Looking Up or Down
    {
      ray_y = player->y;
      ray_x = player->x;
      dof   = 8;
    }
    while(dof < 8)
    {
      map_x = (int)(ray_y) >> 6;
      map_y = (int)(ray_x) >> 6;
      map_p = map_y * map.square_column + map_x;
      if(map_p < map.square_row * map.square_column
         && map_board [map_p] == 1)
      {
        dof = 8;
      }
      else
      {
        ray_y += xo;
        ray_x += yo;
        dof   += 1;
      }
    }
    DrawRect(
        buffer, ray_x, ray_y, player->width / 2, player->height / 2,
        0xfffb8500
    );
  }

  // Draw Phase: Draw Player
  DrawRect(
      buffer, player->x, player->y, player->width, player->height,
      0xff656d4a
  );
}

//
//
//
//
//
//
//
#if defined(NILE_LINUX)
int
x11_main(AppWindow window, GamePlayer *player)
{
  Display *MainDisplay = XOpenDisplay(0);
  Window   RootWindow  = XDefaultRootWindow(MainDisplay);

  int DefaultScreen = DefaultScreen(MainDisplay);
  GC  Context       = XDefaultGC(MainDisplay, DefaultScreen);

  int         ScreenDepth = 24;
  XVisualInfo VisualInfo  = {};
  if(STATUS_ERROR
     == XMatchVisualInfo(
         MainDisplay, DefaultScreen, ScreenDepth, TrueColor, &VisualInfo
     ))
  {
    printf("ERROR: No matching visual info\n");
  }

  //
  //
  //
  //
  //
  // WARN(ABBIB): int to uint conversion
  //   make sure int doesnt overflow
  // max u32 = 2^32 , max int = 2^31 - 1
  //
  // WindowDepth:
  // WindowClass:
  // WindowVisual:
  //
  assert(window.x <= 32767);
  assert(window.y <= 32767);
  assert(window.width <= 32767);
  assert(window.height <= 32767);
  int     WindowX      = (int)window.x;
  int     WindowY      = (int)window.y;
  int     WindowWidth  = (int)window.width;
  int     WindowHeight = (int)window.height;
  int     BorderWidth  = 0;
  int     WindowDepth  = VisualInfo.depth;
  int     WindowClass  = InputOutput;
  Visual *WindowVisual = VisualInfo.visual;

  //
  //
  //
  int                  AttributeValueMask = CWBackPixel | CWEventMask;
  XSetWindowAttributes WindowAttributes   = {};
  WindowAttributes.background_pixel       = 0xffffccaa;
  WindowAttributes.event_mask = StructureNotifyMask | KeyPressMask
                              | KeyReleaseMask | ExposureMask;

  //
  // XCreateWindow:
  // XMapWindow:
  // XStoreName:
  //
  Window MainWindow = XCreateWindow(
      MainDisplay, RootWindow, WindowX, WindowY, WindowWidth,
      WindowHeight, BorderWidth, WindowDepth, WindowClass, WindowVisual,
      AttributeValueMask, &WindowAttributes
  );
  XMapWindow(MainDisplay, MainWindow);
  XStoreName(MainDisplay, MainWindow, window.name);

  //
  // Atom:
  // XInternAtom:
  // XSetWMProtocols:
  //
  Atom WM_DELETE_WINDOW
      = XInternAtom(MainDisplay, "WM_DELETE_WINDOW", False);
  if(!XSetWMProtocols(MainDisplay, MainWindow, &WM_DELETE_WINDOW, 1))
  {
    printf("Couldn't register WM_DELETE_WINDOW property \n");
  }

  //
  //
  //
  //
  int BitsPerPixel     = 32;
  int BytesPerPixel    = BitsPerPixel / 8;
  int WindowBufferSize = WindowWidth * WindowHeight * BytesPerPixel;

  Buffer buffer = {};
  buffer.Width  = WindowWidth;
  buffer.Height = WindowHeight;
  buffer.Pitch  = buffer.Width * BytesPerPixel;
  buffer.Size   = buffer.Pitch * buffer.Height;
  buffer.Size   = buffer.Pitch * buffer.Height;
  buffer.Memory = (uint8_t *)malloc(buffer.Size);

  int     Offset                = 0;
  int     BytesBetweenScanlines = 0;
  XImage *WindowBuffer          = XCreateImage(
      MainDisplay, VisualInfo.visual, VisualInfo.depth, ZPixmap, Offset,
      (char *)buffer.Memory, WindowWidth, WindowHeight, BitsPerPixel,
      BytesBetweenScanlines
  );

  int IsWindowOpen = 1;
  while(IsWindowOpen)
  {

    while(XPending(MainDisplay) > 0)
    {
      XEvent GeneralEvent = {};

      XNextEvent(MainDisplay, &GeneralEvent);

      switch(GeneralEvent.type)
      {
        case KeyPress :
        case KeyRelease :
          {
            XKeyPressedEvent *Event = (XKeyPressedEvent *)&GeneralEvent;
            if(Event->keycode
               == XKeysymToKeycode(MainDisplay, XK_Escape))
            {
              IsWindowOpen = 0;
            }

            if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Down))
            {
              player->x -= player->dx;
              player->y -= player->dy;
            }
            else if(Event->keycode
                    == XKeysymToKeycode(MainDisplay, XK_Up))
            {

              player->x += player->dx;
              player->y += player->dy;
            }
            else if(Event->keycode
                    == XKeysymToKeycode(MainDisplay, XK_Right))
            {
              // player->x += player->step_size;
              player->a += 0.1;
              if(player->a > 2 * PI)
              {
                player->a = 0;
              }
              player->dx = cos(player->a) * 5;
              player->dy = sin(player->a) * 5;
            }
            else if(Event->keycode
                    == XKeysymToKeycode(MainDisplay, XK_Left))
            {
              // player->x -= player->step_size;

              player->a -= 0.1;
              if(player->a < 0)
              {
                player->a = 2 * PI;
              }
              player->dx = cos(player->a) * 5;
              player->dy = sin(player->a) * 5;
            }
          }
          break;

        case ClientMessage :
          {
            XClientMessageEvent *Event
                = (XClientMessageEvent *)&GeneralEvent;
            if((Atom)Event->data.l [0] == WM_DELETE_WINDOW)
            {
              XDestroyWindow(MainDisplay, MainWindow);
              IsWindowOpen = 0;
            }
          }
          break;

        case ConfigureNotify :
          {
            XConfigureEvent *Event = (XConfigureEvent *)&GeneralEvent;
            WindowWidth            = Event->width;
            WindowHeight           = Event->height;

            // NOTE: XDestroyImage also frees Memory, so no need to free from our side
            XDestroyImage(WindowBuffer);

            buffer.Width  = WindowWidth;
            buffer.Height = WindowHeight;
            buffer.Pitch  = buffer.Width * BytesPerPixel;
            buffer.Size   = buffer.Pitch * buffer.Height;
            buffer.Memory = (uint8_t *)malloc(buffer.Size);

            WindowBuffer = XCreateImage(
                MainDisplay, VisualInfo.visual, VisualInfo.depth,
                ZPixmap, Offset, (char *)buffer.Memory, WindowWidth,
                WindowHeight, BitsPerPixel, BytesBetweenScanlines
            );
          }
          break;
      }
    }

    DoRender(&buffer, player);

    int SourceX = 0;
    int SourceY = 0;
    int DestX   = 0;
    int DestY   = 0;
    XPutImage(
        MainDisplay, MainWindow, Context, WindowBuffer, SourceX,
        SourceY, DestX, DestY, WindowWidth, WindowHeight
    );
  }
  return 0;
}
#endif // NILE_LINUX specific function

//
//
//
//
//
//
int
main()
{

#if defined(__linux__) || defined(__gnu_linux__)
  x11_main(app_window, &player);
#endif
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
  win32_main();
#endif
}
