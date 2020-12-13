/// copyright Marco Paladini (paladini.marco@gmail.com) 2020
/// This c++ library is free software, see LICENSE for details

/// This simple test program also illustrates how to use
/// the logging library


#include "micrologger.h"

int main(int, char **)
{
  micrologger::start();
  LOG << "this is a text message";
  LOG << "example data" << 1;
  LOG << "example data"
      << "my string";
  LOG << "error code" << errno;
  try
  {
    THROW("exception logged...");
  }
  catch (const std::exception &)
  {
    LOG << "exception caught";
  }
  THROW("I'll crash after logging this" << 42 << errno << 3.2 << "my string");
  LOG << "cannot log this message because of the exception thrown above";
}
