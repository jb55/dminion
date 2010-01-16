#include "settings.h"
#include "display.h"
#include "context.h"

namespace dminion {

DminionContext::DminionContext() {
  Settings* settings = GetSettings();

  settings->Set(L"window.width", globals::kScreenWidth);
  settings->Set(L"window.height", globals::kScreenHeight);
  settings->Set(L"window.depth", globals::kScreenDepth);

  display = new Display();
  display->Init();
}

void DminionContext::Run() {
  bool done = false;
  while (!done) {
    done = true;
  }
}

}
