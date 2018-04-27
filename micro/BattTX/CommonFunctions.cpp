#ifndef __COMMONFUNCTIONS_CPP_
#define __COMMONFUNCTIONS_CPP_

#include "CommonFunctions.h"

namespace Functions
{
  namespace Common
  {
    unsigned char bcd2int(unsigned char _value)
    {
      return ((((_value & 0xF0) >> 4) * 10) + ( _value & 0x0F));
      //return _value - ((_value >> 4) * 6);
    }

    unsigned char int2bcd(unsigned char _value)
    {
      return ((((_value / 10) & 0x0F) << 4)+((_value % 10) & 0x0F));
      //return _value + ((_value / 10) * 6);
    }
  }
}

#endif

