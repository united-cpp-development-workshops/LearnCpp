#include "Chapter02/quizzes/01/quiz.hpp"

#include <Base/announce.hpp>

static int readNumber()
{
  std::cout << "Enter a number: ";
  int number{};
  std::cin >> number;
  return number;
}

static void writeAnswer(int answer)
{
  std::cout << "The answer is: " << answer << '\n';
}

void Quiz01::run()
{
  ANNOUNCE_QUIZ("Quiz 01: Addition On Same File");
  int firstNumber{readNumber()};
  int secondNumber{readNumber()};
  writeAnswer(firstNumber + secondNumber);
}
