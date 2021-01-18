cmake_minimum_required(VERSION 3.15)
project(corona C)

set(CMAKE_C_STANDARD 99)
#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wvla -Werror -g -lm")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(corona Person.c Meeting.c SpreaderDetector.c main.c
        Meeting.h Person.h SpreaderDetector.h Constants.h)