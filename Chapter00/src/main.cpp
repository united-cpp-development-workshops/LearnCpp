#include <iostream>

#include "announce.hpp"
#include "workshops/workshop01.hpp"

int main()
{
  ANNOUNCE_CHAPTER("Chapter 00: Introduction / Getting Started");
  Workshop01::run();
  return 0;
}
