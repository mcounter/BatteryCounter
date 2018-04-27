#ifndef __USERINTERFACE_SCREENSAVER_CPP_
#define __USERINTERFACE_SCREENSAVER_CPP_

#include "UserInterface_Ref.h"

namespace UserInterface
{
  void functionScreenSaver()
  {
    if (UserInterfaceSetup.screenSaverSetup.screenSaverType == UserMenuScreenSaverType_None)
    {
      updateMenuStack(menuStackPos, USER_FUNCTION_WIDGET);
      isTransition = true;
      return;
    }

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          return;

        case 4:
          transitionUp(USER_FUNCTION_WIDGET);
          return;
      }

      getNextTransitionKey();
    }

    switch (UserInterfaceSetup.screenSaverSetup.screenSaverType)
    {
      case UserMenuScreenSaverType_Default:
        memcpy_G(LCDDriver::displayState.line[0], UserInterfaceSetup.screenSaverSetup.defaultLine0, LCD_DISPLAY_WIDTH);
        memcpy_G(LCDDriver::displayState.line[1], UserInterfaceSetup.screenSaverSetup.defaultLine1, LCD_DISPLAY_WIDTH);
        break;
    }

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void functionScreenSaverMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_SCREENSAVER + UserInterfaceSetup.screenSaverSetup.screenSaverType;
    }

    functionMenu();
  }

  void functionScreenSaverSetup()
  {
    UserInterfaceSetup.screenSaverSetup.screenSaverType = (TUserMenuScreenSaverType)menuStack[menuStackPos].funcState;
    DeviceManager::saveUserInterfaceSetup();
    processMenuOptionChanged();
  }
}

#endif
