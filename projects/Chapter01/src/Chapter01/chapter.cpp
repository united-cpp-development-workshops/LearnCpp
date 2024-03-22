#include "Chapter01/chapter.hpp"

#include "Chapter01/quizzes/01/quiz.hpp"
#include "Chapter01/workshops/01/workshop.hpp"
#include "Chapter01/workshops/02/workshop.hpp"
#include "Chapter01/workshops/03/workshop.hpp"

#include <Base/announce.hpp>

void Chapter01::run()
{
  ANNOUNCE_CHAPTER("Chapter 01: Basics");

  // Workshops
  Workshop01::run();
  Workshop02::run();
  Workshop03::run();

  // Quizes
  Quiz01::run();
}
