#include "settings.h"
#include "display.h"
#include "dminion.h"
#include "platform.h"
#include "SDL/SDL.h"
#include "card.h"
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
  settings->Set("window.width", globals::kScreenWidth);
  settings->Set("window.height", globals::kScreenHeight);
  settings->Set("window.depth", globals::kScreenDepth);

  display->Init();
}

void Dminion::Run() {
  bool done = false;
  SDL_Event event;

  card::LoadAll();
#ifndef NORENDER
  Init();

  display->DrawText("Dminion: Dominion Card Game", Vec2(20, 20));
  display->DrawText("Online", Vec2(20, 60));
  display->DrawCard(NULL, Vec2(20, 60));
  display->Flip();

  while (!done) {
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_KEYDOWN:
      std::cout << "The " << SDL_GetKeyName(event.key.keysym.sym)
                 << " key was pressed!" << std::endl;
      break;
    case SDL_QUIT:
      done = true;
      break;
    }
  }
#endif
  
  

}

}
