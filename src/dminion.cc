#include "settings.h"
#include "display.h"
#include "dminion.h"
#include "platform.h"
#include "resource.h"
#include "SDL/SDL.h"
#include "card.h"
#include "const.h"
#include "log.h"
#include <cmath>
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
  Card* spy = resource::GetCard("custom/test");

  static const int kTop = 230;
  for (int i = 0; i < 5; ++i) {
    display->DrawCard(spy, Vec2((i+1)*100, kTop+((std::sin(i*30))*20)));
  }
  display->Flip();

  while (!done) {
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_KEYDOWN:
      DEV2("The %1% key was pressed!", SDL_GetKeyName(event.key.keysym.sym));
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        done = true;
        break;
      default:
        break;
      }
      break;
    case SDL_QUIT:
      done = true;
      break;
    }
  }
#endif
}


} // namespace dminion
