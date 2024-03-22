#include "Chapter00/chapter.hpp"

#include "Chapter00/workshops/01/workshop.hpp"
#include "Chapter00/workshops/02/workshop.hpp"

#include <Base/announce.hpp>

void Chapter00::run()
{
  ANNOUNCE_CHAPTER("Chapter 00: Introduction / Getting Started");

  // Workshops
  Workshop01::run();
  Workshop02::run();
}
