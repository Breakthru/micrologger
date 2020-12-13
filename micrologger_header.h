/// copyright Marco Paladini (paladini.marco@gmail.com) 2020
/// This c++ library is free software, see LICENSE for details

#pragma once
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#ifndef LOG
#define LOG micrologger::Writer(__FILE__, __LINE__)
#else
#pragma message("micrologger cannot define LOG")
#endif

#ifndef THROW
#define THROW(message)                                                         \
  do                                                                           \
  {                                                                            \
    micrologger::Writer writer(__FILE__, __LINE__);                            \
    writer << message;                                                         \
    writer << std::exception();                                                \
  } while (0)
#else
#pragma message("micrologger cannot define THROW")
#endif

namespace micrologger
{

/// print header and current time, useful at program start
/// returns non-zero if file could not be opened for writing
int start(std::string log_file = "", std::ostream *console = &std::cout);
/// insert a log line with a human readeable timestamp
void log_current_timestamp();

class Writer
{
  std::stringstream message; // a single CSV line for output
  bool has_thrown_exception; // true if the LOG macro is catching an exception
  static std::ofstream log_file; // write CSV log to this std::ofstream file
  // optionally write the CSV log to this std::ostream console
  // if NULL, then there is no console output
  static std::ostream *console;

public:
  static void write_message(const std::string &msg)
  {
    if (console)
    {
      (*console) << msg << std::endl;
    }
    if (log_file && log_file.good())
    {
      log_file << msg << std::endl;
    }
  }

  // constructor must be called explicitly, but the library user is only
  // expected to call the friend function:
  // int start(std::string log_file, std::ostream *console)
  // at some point in their code before starting logging
  explicit Writer(std::string file, int line) : has_thrown_exception(false)
  {
    std::string basename = file.substr(file.rfind("/") + 1);
    message << 1000 * clock() / CLOCKS_PER_SEC << "," << basename << ":"
            << line;
  }

  template <typename T> Writer &operator<<(const T &data)
  {
    message << "," << data;
    return *this;
  }

  // specialisation for std::string to enclose it in quotes
  Writer &operator<<(const std::string &data)
  {
    message << ",\"" << data << "\"";
    return *this;
  }

  // specialisation for const char * to enclose it in quotes
  Writer &operator<<(const char *data)
  {
    message << ",\"" << data << "\"";
    return *this;
  }

  // specialisation for floats to print 6 digits past the decimal point
  Writer &operator<<(float value)
  {
    message << "," << std::fixed << std::setprecision(6) << value;
    return *this;
  }

  // specialisation for double to print 6 digits past the decimal point
  Writer &operator<<(double value)
  {
    message << "," << std::fixed << std::setprecision(6) << value;
    return *this;
  }

  // specialisation for throwing exceptions
  Writer &operator<<(const std::exception&)
  {
    message << ",ERROR";
    Writer::write_message(message.str());
    has_thrown_exception = true;
    throw std::runtime_error(message.str());
  }

  ~Writer()
  {
    if (!has_thrown_exception)
    {
      Writer::write_message(message.str());
    }
  }

/// initialise the log file and console
/// append to file specified by `log_file` if not empty
/// also write messages to `console` if not null
/// returns zero on success
friend int start(std::string log_file, std::ostream *console)
{
  Writer::console = console;

  if (!Writer::log_file.is_open() && !log_file.empty())
  {
    Writer::log_file.open(log_file, std::ios_base::app);
  }

  Writer::write_message("CLOCK(ms),FILE:LINE,DATA");
  log_current_timestamp();

  return !Writer::log_file.good();
}

};
} // end namespace micrologger
