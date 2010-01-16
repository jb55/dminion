#ifndef _DMINION_H_
#define _DMINION_H_

namespace dminion {

class Display;
class Settings;

class Dminion
{
  Display* display;
  Settings* settings;

  void Init();

public:
    
  Dminion();
  ~Dminion();

  void Run();

};

}

#endif // _DMINION_H_
