#pragma once

#ifndef ANNOUNCE_CHAPTER
# define ANNOUNCE_CHAPTER(msg) std::cout << msg << "\n" << std::string(std::strlen(msg), '=') << "\n"
#endif

#ifndef ANNOUNCE_WORKSHOP
# define ANNOUNCE_WORKSHOP(msg) std::cout << "\n" << msg << "\n" << std::string(std::strlen(msg), '-') << "\n"
#endif
