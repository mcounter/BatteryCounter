#ifndef __USERINTERFACE_REF_H_
#define __USERINTERFACE_REF_H_

#include "UserInterface.h"
#include "UserInterfaceLang.h"
#include "UserInterfaceMenuBuilder.h"

#include "GlobalSpace.h"
#include "LCDDriver.h"
#include "MultyThreading.h"
#include "GlobalRTC.h"
#include "GlobalADC.h"
#include "PhotoSensor.h"
#include "KeyBoardDriver.h"
#include "GlobalCounter.h"
#include "MemAT25Driver.h"
#include "DeviceManager.h"
#include "MainThread.h"

#define USER_INTERFACE_REFRESH_TIMEOUT_MS       (5000)
#define USER_INTERFACE_MESSAGE_TIMEOUT_MS       (2000)
#define USER_INTERFACE_KEY_ITERATOR_MAX         (16)

#define USER_MENU_STACK_SIZE                    (10)
#define USER_MENU_ACTIVE_PARM_SPACE_SIZE        (48)

using namespace GLOBAL::DeviceProfile;

namespace UserInterface
{
  typedef struct
  {
    unsigned char menuFunction;
    TMenuFunctionReference menuReference;
    unsigned char funcState;
  } TMenuStackRecord;

  typedef enum
  {
    MenuAuthLevel_None = 0,
    MenuAuthLevel_Reports = 1,
    MenuAuthLevel_Master = 2,
  } TMenuAuthLevel;

  extern TMenuStackRecord menuStack[USER_MENU_STACK_SIZE];
  extern unsigned char menuStackPos;
  extern unsigned char activeFunction;
  extern bool activeFunctionChanged;
  extern unsigned char activeParmSpace[USER_MENU_ACTIVE_PARM_SPACE_SIZE];

  extern bool isEnabled;
  extern bool isTimeOutEnabled;
  extern bool isMenuActive;
  extern bool isPhotoActive;
  extern TMenuAuthLevel menuAuthLevel;
  extern bool isTransition;
  extern unsigned char transitionKey;
  extern bool transitionDownOnRefresh;
  extern unsigned char keyIterator;

  extern GLOBAL::Counter::TCounterStatisticRecord curStatisticRecord;

  void setInactivityTimeTimeout();
  void setRefreshTimeout();
  void initTransitionDownOnRefresh();
  void updateMenuStack(unsigned char _menuStackPos, unsigned char _menuFunction);
  void transitionUp(unsigned char _menuFunction);
  void enterInterface();
  void getNextTransitionKey();
  bool checkDeviceSwitchOff();
  void transitionDown();
  void displayDoneMessage();
  void displayErrorMessage();
  void processMenuOptionChanged();
  void functionIncorrectFunction();
}

#endif
