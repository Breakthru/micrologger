/// copyright Marco Paladini (paladini.marco@gmail.com) 2020
/// This c++ library is free software, see LICENSE for details

/// This simple test program also illustrates how to use
/// the logging library

#include "micrologger.h"
#include <limits>
#include <chrono>

int log_n_messages(unsigned int counter) {
    while(counter > 0) {
        LOG << --counter; // log a decreasing counter
    }

    return 0;
}

std::chrono::milliseconds test_log_speed(unsigned int N) {
    std::chrono::high_resolution_clock chronometer;
    auto time_start = chronometer.now();
    log_n_messages(N);
    std::chrono::milliseconds duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(chronometer.now() - time_start);
    return duration_ms;
}


int main(int, char **)
{
  micrologger::start();
  std::chrono::milliseconds duration = test_log_speed(1000);
  std::cout << "console test took " << duration.count() << "ms" << std::endl;
  // now test with disk write and no console write...
  micrologger::start("test_file_write_deleteme.csv", NULL);
  std::cout << "CSV file test took " << test_log_speed(1000).count() << "ms" << std::endl;

  return 0;
}
