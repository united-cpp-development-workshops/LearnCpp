#include "chapter.hpp"

#include "announce.hpp"
#include "workshops/workshop01.hpp"
#include "workshops/workshop02.hpp"

void Chapter00::run()
{
  ANNOUNCE_CHAPTER("Chapter 00: Introduction / Getting Started");
  Workshop01::run();
  Workshop02::run();
}
