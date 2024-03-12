#include "chapter.hpp"

#include "announce.hpp"
#include "workshops/workshop01.hpp"

void Chapter02::run()
{
  ANNOUNCE_CHAPTER("Chapter 02: Functions & Files");
  Workshop01::run();
}
