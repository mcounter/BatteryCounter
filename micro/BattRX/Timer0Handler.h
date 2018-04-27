#ifndef __TIMER0HANDLER_H_
#define __TIMER0HANDLER_H_

#include "GlobalSpace.h"

namespace Timer0Handler
{
  void init();
  void disable();
  void enable();
  bool enabled();
}

#endif

