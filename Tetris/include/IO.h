#pragma once
#ifndef __IO_H_
#define __IO_H_

#include <../SDL_GfxPrimitives/SDL_gfxPrimitives.h>
#include <SDL3/SDL.h>

#include <SDL3_ttf/SDL_ttf.h>
#include <string>

enum color {
  BLACK = 0,
  RED = 1,
  GREEN = 2,
  BLUE = 3,
  CYAN = 4,
  MAGENTA = 5,
  YELLOW = 6,
  WHITE = 7,
  COLOR_MAX = 8
};

class IO {
 public:
  IO();
  ~IO();

  void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
  void ClearScreen();
  int GetScreenHeight();
  int GetScreenWidth();
  bool InitGraph();
  int Pollkey();
  int GetKey();
  int IsKeyDown(int pKey);

  void DrawText(int x, int y, const std::string& text, enum color pC,
                int size = 16);
  void DrawLargeText(int x, int y, const std::string& text, enum color pC);
  void UpdateScreen();

 private:
  SDL_Renderer* mRenderer;
  SDL_Window* mWindow;
  static const Uint32 mColors[COLOR_MAX];
  TTF_Font* mFont;
  TTF_Font* mLargeFont;
};

#endif
