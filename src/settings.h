#ifndef _DMINION_SETTINGS_H_
#define _DMINION_SETTINGS_H_

#include <map>
#include "common.h"
#include "const.h"

namespace dminion {

class Settings 
{
  std::map<string, string> settingsMap;

  template<typename T> 
  void doSet(const string& key, T val);

  template<typename T>
  T doGet(const string& key);

public:

  void Set(const string& key, int val);
  void Set(const string& key, float val);
  void Set(const string& key, const string& val);

  int GetInt(const string& key);
  float GetFloat(const string& key);
  string GetString(const string& key);
  
  ~Settings();

};

void SetSettings(Settings* settings);
Settings* GetSettings();

}

#endif // _DMINION_SETTINGS_H_
