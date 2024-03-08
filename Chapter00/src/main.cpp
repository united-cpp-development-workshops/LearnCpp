#include "announce.hpp"
#include "workshops/workshop01.hpp"
#include "workshops/workshop02.hpp"

int main()
{
  ANNOUNCE_CHAPTER("Chapter 00: Introduction / Getting Started");
  Workshop01::run();
  Workshop02::run();
  return 0;
}
