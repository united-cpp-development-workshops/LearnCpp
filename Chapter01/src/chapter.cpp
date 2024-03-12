#include "chapter.hpp"

#include "announce.hpp"
#include "workshops/workshop01.hpp"
#include "workshops/workshop02.hpp"
#include "workshops/workshop03.hpp"
#include "quizes/quiz01.hpp"

void Chapter01::run()
{
  ANNOUNCE_CHAPTER("Chapter 01: Basics");
  Workshop01::run();
  Workshop02::run();
  Workshop03::run();
  Quiz01::run();
}
