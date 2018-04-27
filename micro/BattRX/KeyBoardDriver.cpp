#ifndef __KEYBOARDDRIVER_CPP_
#define __KEYBOARDDRIVER_CPP_

#include "GlobalSpace.h"
#include "KeyBoardDriver.h"
#include "MultyThreading.h"

#define KEYBOARD_BUFFER_SIZE                    (16)
#define KEYBOARD_KEYREP_TIMEOUT1_MS             (2000)
#define KEYBOARD_KEYREP_TIMEOUT2_MS             (250)
#define KEYBOARD_KEYREP_KEYCHANGE_TIMEOUT_MS    (10)

namespace KeyBoardDriver
{
  unsigned char keyboardBuffer[KEYBOARD_BUFFER_SIZE];
  unsigned char keyBuffHead = 0;
  unsigned char keyBuffTail = 0;
  unsigned char lastKeyState = 0;
  bool uiRequest = false;

  #pragma vector=PCINT0_vect,PCINT2_vect
  __interrupt void irqPinChange()
  {
    unsigned char curKeyState =
      (MENU_KEY1_PIN ? 0x00 : 0x01) +
      (MENU_KEY2_PIN ? 0x00 : 0x02) +
      (MENU_KEY3_PIN ? 0x00 : 0x04) +
      (MENU_KEY4_PIN ? 0x00 : 0x08);

    __delay_cycles(10);

    curKeyState &=
      (MENU_KEY1_PIN ? 0x00 : 0x01) +
      (MENU_KEY2_PIN ? 0x00 : 0x02) +
      (MENU_KEY3_PIN ? 0x00 : 0x04) +
      (MENU_KEY4_PIN ? 0x00 : 0x08);

    unsigned char curStateDiff = lastKeyState ^ curKeyState;
    lastKeyState = curKeyState;
    for (unsigned char i = 1; i <= 4; i++)
    {
      if ((curStateDiff & 0x01) && (curKeyState & 0x01))
      {
        pushBuff(i);

        if (i == 4)
        {
          uiRequest = true;
        }
      }

      curStateDiff >>= 1;
      curKeyState >>= 1;
    }

    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_KEYBOARD_KEYREP, KEYBOARD_KEYREP_TIMEOUT1_MS);
  }

  __monitor void repeatKey()
  {
    switch (lastKeyState)
    {
      case 0x02:
        pushBuff(2, true);
        break;

      case 0x04:
        pushBuff(3, true);
        break;
    }

    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_KEYBOARD_KEYREP, KEYBOARD_KEYREP_TIMEOUT2_MS);
  }

  __monitor void pushBuff(unsigned char _key, bool _repeat)
  {
    keyboardBuffer[keyBuffHead] = (_key & 0x7F) + (_repeat ? 0x80 : 0x00);

    keyBuffHead = (keyBuffHead + 1) % KEYBOARD_BUFFER_SIZE;
    if (keyBuffHead == keyBuffTail)
    {
      keyBuffTail = (keyBuffTail + 1) % KEYBOARD_BUFFER_SIZE;
    }
  }

  __monitor unsigned char popBuff(bool _skipRepeat)
  {
    while (keyBuffHead != keyBuffTail)
    {
      unsigned char curKey = keyboardBuffer[keyBuffTail];

      keyBuffTail = (keyBuffTail + 1) % KEYBOARD_BUFFER_SIZE;

      if ((!_skipRepeat) || (!(curKey & 0x80)))
      {
        return curKey & 0x7F;
      }
    }

    return 0;
  }

  __monitor bool getKeyState(unsigned char _keyNum)
  {
    switch (_keyNum)
    {
      case 1: return (lastKeyState & 0x01) ? true : false;
      case 2: return (lastKeyState & 0x02) ? true : false;
      case 3: return (lastKeyState & 0x04) ? true : false;
      case 4: return (lastKeyState & 0x08) ? true : false;
    }

    return false;
  }

  __monitor bool getUIRequest()
  {
    bool curValue = uiRequest;
    uiRequest = false;

    return curValue;
  }

  __monitor void clearBuff()
  {
    keyBuffHead = 0;
    keyBuffTail = 0;
  }

  __monitor void init()
  {
    MENU_KEY1_DIR = 0;
    MENU_KEY1_PORT = 1;

    MENU_KEY2_DIR = 0;
    MENU_KEY2_PORT = 1;

    MENU_KEY3_DIR = 0;
    MENU_KEY3_PORT = 1;

    MENU_KEY4_DIR = 0;
    MENU_KEY4_PORT = 1;

    lastKeyState = 0;
    uiRequest = false;
    clearBuff();

    PCMSK0 = (1<<MENU_KEY1_INT);
    PCMSK1 = 0x00;
    PCMSK2 = (1<<MENU_KEY2_INT) | (1<<MENU_KEY3_INT) | (1<<MENU_KEY4_INT);
    PCICR = (1<<PCIE0) | (1<<PCIE2);
  }

  void run()
  {
    if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_KEYBOARD_KEYREP))
    {
      uiRequest = false;

      if (lastKeyState)
      {
        repeatKey();
      }
    }
  }
}

#endif
