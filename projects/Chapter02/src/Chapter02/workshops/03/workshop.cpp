#include "Chapter02/workshops/03/workshop.hpp"

#include <Base/announce.hpp>

// Forward declarations
int  getValueFromUser();
void printAddition(int fVal, int sVal);

void Workshop03::run()
{
  ANNOUNCE_WORKSHOP("Workshop 03: Multiple Source Files");
  printAddition(getValueFromUser(), getValueFromUser());
}
