#include "log.h"
#include <iostream>
#include <sstream>
#include <ostream>

namespace dminion {
namespace log {
namespace {

void Log(const string& msg, MsgType type) {
  std::stringstream ss;
  std::ostream* stream;

  switch (type) {
  case kDev:
    ss << "Dev";
    stream = &std::cout;
    break;
  case kWarning:
    ss << "Warning";
    stream = &std::cout;
    break;
  case kError:
    ss << "Error";
    stream = &std::cerr;
    break;
  }

  std::ostream& s = *stream;
  ss << " | " << msg << std::endl;
  s << ss.str();
}
  
} // anonymous namespace

void Error(const string& msg) {
  Log(msg, kError);
}

void Warning(const string& msg) {
  Log(msg, kWarning);
}

void Dev(const string& msg) {
  Log(msg, kDev);
}


} // namespace log
} // namespace dminion
