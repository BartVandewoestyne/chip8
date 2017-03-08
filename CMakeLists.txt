SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --std=c++14" )
add_executable(chip8 Chip8.cpp main.cpp)
