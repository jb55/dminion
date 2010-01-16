#include "settings.h"
#include "display.h"
#include "dminion.h"

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

  while (!done) {
    done = true;
  }
}

}
