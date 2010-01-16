#ifndef _DMINION_CONTEXT_H_
#define _DMINION_CONTEXT_H_

namespace dminion {

class Display;

class DminionContext 
{
  Display* display;

public:
    
  DminionContext();
  ~DminionContext();

  void Run();

};

}

#endif // _DMINION_CONTEXT_H_
