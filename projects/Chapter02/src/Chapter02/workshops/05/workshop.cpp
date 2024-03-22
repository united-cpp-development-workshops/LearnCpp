#include "Chapter02/workshops/05/workshop.hpp"

#include "Chapter02/workshops/05/functions.hpp"

#include <Base/announce.hpp>

void Workshop05::run()
{
  ANNOUNCE_WORKSHOP("Workshop 05: Using Header Files");
  printAdditionHpp(getValueFromUserHpp(), getValueFromUserHpp());
}
