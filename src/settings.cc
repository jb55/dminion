#include "settings.h"
#include "log.h"
#include <iostream>
#include <sstream>

namespace dminion {
namespace { 
Settings* gpSettings;
} // anonymous namespace}

Settings::~Settings() {
  DEV("~Settings()");
}

template <typename T>
void Settings::doSet(const string& key, T val) {
  std::stringstream os;
  os << val;
  settingsMap[key] = os.str();
}

template <typename T>
T Settings::doGet(const string& key) {
  T val;
  std::stringstream os(settingsMap[key]);
  os >> val;
  return val;
}

void Settings::Set(const string& key, int val) {
  doSet<int>(key, val);
}

void Settings::Set(const string& key, float val) {
  doSet<float>(key, val);
}

void Settings::Set(const string& key, const string& val) {
  doSet<string>(key, val);
}

int Settings::GetInt(const string& key) {
  return doGet<int>(key);
}

float Settings::GetFloat(const string& key) {
  return doGet<float>(key);
}

string Settings::GetString(const string& key) {
  return doGet<string>(key);
}

void SetSettings(Settings* settings) {
  gpSettings = settings;
}

Settings* GetSettings() {
  return gpSettings;
}

}
