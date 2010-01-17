#include "settings.h"
#include "display.h"
#include "dminion.h"
#include "platform.h"
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

  Init();

  display->Flip();
  while (!done) {
    util::sleep(5);
    done = true;
  }

}

}
