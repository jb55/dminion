#include "platform.h" 
#ifdef linux
  #include <unistd.h>
#endif
#ifdef WIN32
  #include <windows.h>
#endif

namespace dminion {
namespace util {

void sleep(int seconds) {
#ifdef linux
  usleep(seconds*1000000);
#endif
#ifdef WIN32
  Sleep(seconds);
#endif
}

}
}
