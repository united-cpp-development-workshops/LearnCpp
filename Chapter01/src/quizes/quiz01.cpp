#include "quizes/quiz01.hpp"

#include "announce.hpp"

void Quiz01::run()
{
  ANNOUNCE_QUIZ("Quiz01: Add/Subtract Input Numbers");
  int a{};
  int b{};
  std::cout << "Enter two numbers: ";
  std::cin >> a >> b;
  std::cout << "The sum of " << a << " and " << b << " is " << a + b << ".\n";
  std::cout << "The difference of " << a << " and " << b << " is " << a - b << ".\n";
}
