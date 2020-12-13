/// copyright Marco Paladini (paladini.marco@gmail.com) 2020
/// This c++ library is free software, see LICENSE for details

#pragma once
/// macros and classes definitions
#include "micrologger_header.h"

namespace micrologger
{
/// static log file object, for disk writing
std::ofstream Writer::log_file;
/// static console writer pointer, defaults to stdout
std::ostream *Writer::console = &std::cout;

/// add a line with a human-readeable timestamp to the log file
void log_current_timestamp()
{
  std::time_t now = std::time(nullptr);
  char datetime_string[200];
  if (std::strftime(datetime_string, sizeof(datetime_string), "%c %Z",
                    std::gmtime(&now)))
  {
    micrologger::Writer(__FILE__, __LINE__) << datetime_string;
  }
}

} // end namespace micrologger
