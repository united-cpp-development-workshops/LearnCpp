#include "Chapter02/workshops/04/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

#define PRINT_EMRECAN

void Workshop04::run()
{
  ANNOUNCE_WORKSHOP("Workshop 04: Basic Preprocessor Directives");
#if defined(PRINT_EMRECAN)
  std::cout << "PRINT_EMRECAN is defined!\n";
  std::cout << "Emrecan!\n";
#else
  std::cout << "PRINT_EMRECAN not defined!\n";
#endif
}
