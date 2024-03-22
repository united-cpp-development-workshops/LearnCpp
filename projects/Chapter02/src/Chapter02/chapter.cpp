#include "Chapter02/chapter.hpp"

#include "Chapter02/projects/01/project.hpp"
#include "Chapter02/quizzes/01/quiz.hpp"
#include "Chapter02/quizzes/02/quiz.hpp"
#include "Chapter02/workshops/01/workshop.hpp"
#include "Chapter02/workshops/02/workshop.hpp"
#include "Chapter02/workshops/03/workshop.hpp"
#include "Chapter02/workshops/04/workshop.hpp"
#include "Chapter02/workshops/05/workshop.hpp"

#include <Base/announce.hpp>

void Chapter02::run()
{
  ANNOUNCE_CHAPTER("Chapter 02: Functions & Files");

  // Workshops
  Workshop01::run();
  Workshop02::run();
  Workshop03::run();
  Workshop04::run();
  Workshop05::run();

  // Quizzes
  Quiz01::run();
  Quiz02::run();

  // Projects
  Project01::run();
}
