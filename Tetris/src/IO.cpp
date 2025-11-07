#include "IO.h"

#include <cstdio>
#include <cstdlib>

const Uint32 IO::mColors[COLOR_MAX] = {0x000000ff,  // Colors
                                       0xff0000ff, 0x00ff00ff, 0x0000ffff,
                                       0x00ffffff, 0xff00ffff, 0xffff00ff,
                                       0xffffffff};

/*
======================================
Init
======================================
*/
IO::IO() : mRenderer(nullptr), mWindow(nullptr) {}

IO::~IO() {
  if (mRenderer) {
    SDL_DestroyRenderer(mRenderer);
  }
  if (mWindow) {
    SDL_DestroyWindow(mWindow);
  }
  if (mFont) TTF_CloseFont(mFont);
  if (mLargeFont) TTF_CloseFont(mLargeFont);
  TTF_Quit();
}

/*
======================================
Clear the screen to black
======================================
*/
void IO::ClearScreen() {
  // boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  SDL_RenderClear(mRenderer);
}

/*
======================================
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
======================================
*/
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC) {
  // boxColor(mScreen, pX1, pY1, pX2, pY2 - 1, mColors[pC]);
  Uint32 color = mColors[pC];
  Uint8 r = (color >> 24) & 0xff;
  Uint8 g = (color >> 16) & 0xff;
  Uint8 b = (color >> 8) & 0xff;
  Uint8 a = color & 0xff;
  SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
  SDL_FRect rect = {static_cast<float>(pX1), static_cast<float>(pY1),
                    static_cast<float>(pX2 - pX1),
                    static_cast<float>(pY2 - pY1)};
  SDL_RenderFillRect(mRenderer, &rect);
}

/*
======================================
Return the screen height
======================================
*/
int IO::GetScreenHeight() {
  int heigeht = 0;
  SDL_GetWindowSize(mWindow, NULL, &heigeht);
  return heigeht;
}

/*
======================================
Update screen
======================================
*/
void IO::UpdateScreen() { SDL_RenderPresent(mRenderer); }

/*
======================================
Keyboard Input
======================================
*/
int IO::Pollkey() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_KEY_DOWN:
        return event.key.key;
      case SDL_EVENT_QUIT:
        exit(3);
    }
  }
  return -1;
}

/*
======================================
Keyboard Input
======================================
*/
int IO::GetKey() {
  SDL_Event event;
  while (true) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_EVENT_KEY_DOWN) {
      break;
    }
    if (event.type == SDL_EVENT_QUIT) {
      exit(3);
    }
  };
  return event.key.key;
}

/*
======================================
Keyboard Input
======================================
*/
int IO::IsKeyDown(int pKey) {
  const bool* state = SDL_GetKeyboardState(NULL);
  if (!state) {
    return false;
  }

  SDL_Scancode scancode = SDL_GetScancodeFromKey(pKey, NULL);
  return state[scancode] != 0;
}

/*
======================================
SDL Graphical Initialization
======================================
*/
bool IO::InitGraph() {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  mWindow = SDL_CreateWindow("Tetris", 1600, 1280, 0);
  if (!mWindow) {
    fprintf(stderr, "Couldn`t creat Window: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  mRenderer = SDL_CreateRenderer(mWindow, NULL);
  if (!mRenderer) {
    fprintf(stderr, "Couldn`t creat Renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    return false;
  }

  if (TTF_Init() < 0) {
    fprintf(stderr, "Couldn't initialize TTF\n");
    return false;
  }

  // 加载字体
  mFont = TTF_OpenFont("simsun.ttc", 32);
  mLargeFont = TTF_OpenFont("simsun.ttc", 64);

  if (!mFont || !mLargeFont) {
    fprintf(stderr, "Couldn't load font\n");
    // 可以继续运行，只是没有文本显示
  }

  return true;
}

int IO::GetScreenWidth() {
  int width;
  SDL_GetWindowSize(mWindow, &width, NULL);
  return width;
}


void IO::DrawText(int x, int y, const std::string& text, enum color pC,
                  int size) {
  if (!mFont) return;

  Uint32 colorValue = mColors[pC];
  Uint8 r = (colorValue >> 24) & 0xFF;
  Uint8 g = (colorValue >> 16) & 0xFF;
  Uint8 b = (colorValue >> 8) & 0xFF;

  SDL_Color color = {r, g, b, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(mFont, text.c_str(), text.length(),color);
  if (surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FRect dstRect = {static_cast<float>(x), static_cast<float>(y),
                         static_cast<float>(surface->w),
                         static_cast<float>(surface->h)};
    SDL_RenderTexture(mRenderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
  }
}

void IO::DrawLargeText(int x, int y, const std::string& text, enum color pC) {
  if (!mLargeFont) return;

  Uint32 colorValue = mColors[pC];
  Uint8 r = (colorValue >> 24) & 0xFF;
  Uint8 g = (colorValue >> 16) & 0xFF;
  Uint8 b = (colorValue >> 8) & 0xFF;

  SDL_Color color = {r, g, b, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(mLargeFont, text.c_str(),text.length(), color);
  if (surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FRect dstRect = {static_cast<float>(x), static_cast<float>(y),
                         static_cast<float>(surface->w),
                         static_cast<float>(surface->h)};
    SDL_RenderTexture(mRenderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
  }
}