#ifndef __KEYBOARDDRIVER_CPP_
#define __KEYBOARDDRIVER_CPP_

#include "GlobalSpace.h"
#include "KeyBoardDriver.h"
#include "MultyThreading.h"
#include "DeviceManager.h"

#define KEYBOARD_KEYTHRESHOLD_MS                (3000)

namespace KeyBoardDriver
{
  bool isKeyProcessed = false;

  __monitor void init()
  {
    CONFIG_KEY_DIR = 0;
    CONFIG_KEY_PORT = 1;

    isKeyProcessed = false;
  }

  void run()
  {
    bool isKeyPressed = CONFIG_KEY_PIN ? false : true;

    if (isKeyPressed)
    {
      if ((!isKeyProcessed) && (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_KEYBOARD_KEYTHRESHOLD)))
      {
        DeviceManager::switchTransmitterMode();
        isKeyProcessed = true;
      }
    }
    else
    {
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_KEYBOARD_KEYTHRESHOLD, KEYBOARD_KEYTHRESHOLD_MS);
      isKeyProcessed = false;
    }
  }
}

#endif
