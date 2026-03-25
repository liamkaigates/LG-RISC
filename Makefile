CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Isrc/memory

SRC = src/main.cpp \
      src/memory/main_memory.cpp \
      src/memory/cache.cpp \
      src/memory/memory_subsystem.cpp \
      src/memory/driver.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o simulator

clean:
	rm -f simulator
