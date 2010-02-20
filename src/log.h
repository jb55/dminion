#ifndef _DMINION_LOG_H_
#define _DMINION_LOG_H_

#include "types.h"
#include <boost/format.hpp>

#define WARN(x) do { log::Warning((x)); } while(0)
#define WARN2(x, y) do { boost::format f(x); f % y; WARN(f.str()); } while(0)

#define ERROR(x) do { log::Error((x)); } while(0)
#define ERROR2(x, y) do { boost::format f(x); f % y; ERROR(f.str()); } while(0)

#define DEV(x) do { log::Dev((x)); } while(0)
#define DEV2(x, y) do { boost::format f(x); f % y; DEV(f.str()); } while(0)

namespace dminion {
namespace log {

enum MsgType {
  kDev,
  kWarning,
  kError
};

void Error(const string& msg);
void Dev(const string& msg);
void Warning(const string& msg);


} // namespace log
} // namespace dminion

#endif // _DMINION_LOG_H
