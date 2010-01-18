#include "settings.h"
#include "display.h"
#include "dminion.h"
#include "platform.h"
#include "SDL/SDL.h"
#include <iostream>

namespace dminion {

Dminion::Dminion() {
  settings = new Settings();
  display = new Display();

  SetSettings(settings);
}

Dminion::~Dminion() {
  delete display;
  delete settings;
}

void Dminion::Init() {
  settings->Set(L"window.width", globals::kScreenWidth);
  settings->Set(L"window.height", globals::kScreenHeight);
  settings->Set(L"window.depth", globals::kScreenDepth);

  display->Init();
}

void Dminion::Run() {
  bool done = false;
  SDL_Event event;

  Init();

  display->DrawText(L"Dminion: Dominion Card Game", Vec2(20, 20));
  display->DrawText(L"Online", Vec2(20, 60));

  display->Flip();

  while (!done) {
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_KEYDOWN:
      std::wcout << L"The " << SDL_GetKeyName(event.key.keysym.sym)
                 << L" key was pressed!" << std::endl;
      break;
    case SDL_QUIT:
      done = true;
      break;
    }
  }

}

}
