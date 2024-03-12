#include "workshops/workshop01.hpp"

#include "announce.hpp"

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: Console Input/Output");
  std::cout << "Enter a number: ";
  int number{};
  std::cin >> number;
  std::cout << "You entered: " << number << '\n';
  std::cout << "Enter two numbers separated by a space: ";
  int first{};
  int second{};
  std::cin >> first >> second;
  std::cout << "You entered: " << first << " and " << second << '\n';
}
