#ifndef __USERINTERFACELANG_CPP_
#define __USERINTERFACELANG_CPP_

#include "UserInterfaceLang.h"
#include "UserInterfaceLang_RUS.h"

#include "GlobalSpace.h"

namespace UserInterface
{
  unsigned char __generic* getString(unsigned short _strId)
  {
    switch (GLOBAL::DeviceProfile::UserInterfaceSetup.language)
    {
      case GLOBAL::DeviceProfile::UserInterfaceLanguage_RUS:
        return (unsigned char __generic*)(textStrings_RUS + textReference_RUS[_strId]);

    }

    return 0;
  }
}

#endif
