#include "Chapter02/quizzes/02/quiz.hpp"

#include "Chapter02/quizzes/02/io.hpp"

#include <Base/announce.hpp>

void Quiz02::run()
{
  ANNOUNCE_QUIZ("Quiz 02: Addition Over Different Files");
  int firstNumber{Quiz02::readNumber()};
  int secondNumber{Quiz02::readNumber()};
  Quiz02::writeAnswer(firstNumber + secondNumber);
}
