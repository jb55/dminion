#include "settings.h"
#include <iostream>
#include <sstream>

namespace dminion {

static Settings* gpSettings;

Settings::~Settings() {
  std::cout << "~Settings()" << std::endl;
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
