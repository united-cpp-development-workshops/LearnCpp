#include "Chapter02/quizzes/02/io.hpp"

#include <iostream>

int Quiz02::readNumber()
{
  std::cout << "Enter a number: ";
  int number{};
  std::cin >> number;
  return number;
}

void Quiz02::writeAnswer(int answer)
{
  std::cout << "The answer is: " << answer << '\n';
}
