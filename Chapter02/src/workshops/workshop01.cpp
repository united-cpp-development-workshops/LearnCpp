#include "workshops/workshop01.hpp"

#include "announce.hpp"

static int returnFive()
{
  return 5;
}

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: Basic FUnction");
  std::cout << returnFive() << '\n';
}
