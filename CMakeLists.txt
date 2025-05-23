﻿# CMakeList.txt : CMake project for LazyPy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project ("LazyPy")

# Add source to this project's executable.
add_executable (LazyPy
        "Compilers.h"
        "Compilers.c"
        "Reader.h"
        "Reader.c"
        "MainReader.c"
        "Scanner.c"
        "Scanner.h"
        "MainScanner.c"
        "Parser.h"
        "Parser.c"
        "MainParser.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LazyPy PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
