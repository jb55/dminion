#include "settings.h"
#include "display.h"
#include "dminion.h"
#include "platform.h"
#include "resource.h"
#include "SDL/SDL.h"
#include "card.h"
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
  game::Card* spy = resource::GetCard("custom/test");

  static const int kTop = 230;
  for (int i = 0; i < 5; ++i) {
    display->DrawCard(spy, Vec2((i+1)*100, kTop+((std::sin(i*30))*20)));
  }
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


} // namespace dminion
