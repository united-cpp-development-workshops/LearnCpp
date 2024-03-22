#pragma once

#include <cstring>
#include <iostream>
#include <string>

#ifndef ANNOUNCE_CHAPTER
  #define ANNOUNCE_CHAPTER(msg)                                                \
    std::cout << msg << '\n' << std::string(std::strlen(msg), '=') << '\n'
#endif

#ifndef ANNOUNCE_WORKSHOP
  #define ANNOUNCE_WORKSHOP(msg)                                               \
    std::cout << '\n'                                                          \
              << msg << '\n'                                                   \
              << std::string(std::strlen(msg), '-') << '\n'
#endif

#ifndef ANNOUNCE_QUIZ
  #define ANNOUNCE_QUIZ(msg)                                                   \
    std::cout << '\n'                                                          \
              << msg << '\n'                                                   \
              << std::string(std::strlen(msg), '*') << '\n'
#endif

#ifndef ANNOUNCE_PROJECT
  #define ANNOUNCE_PROJECT(msg)                                                \
    std::cout << '\n'                                                          \
              << msg << '\n'                                                   \
              << std::string(std::strlen(msg), '^') << '\n'
#endif
