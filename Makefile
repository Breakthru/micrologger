# Copyright Marco Paladini (paladini.marco@gmail.com) 2020
# This program is Free Software released under the GNU GPLv3 License
# See "LICENSE" for details

# This Makefile will build and run the test program

# The library itself is header-only, meaning there is no need to be compiled
# into object code
CXX=g++

micrologger_test: micrologger_test.cpp micrologger_header.h micrologger.h
	$(CXX) -o micrologger_test micrologger_test.cpp


micrologger_speed_test: micrologger_speed_test.cpp micrologger_header.h micrologger.h
	$(CXX) -o micrologger_speed_test micrologger_speed_test.cpp


test: micrologger_test micrologger_speed_test
	./micrologger_speed_test || ./micrologger_test

all: micrologger_speed_test micrologger_speed_test

clean:
	rm micrologger_test micrologger_speed_test test_file_write_deleteme.csv

