#ifndef __KEYBOARDDRIVER_H_
#define __KEYBOARDDRIVER_H_

namespace KeyBoardDriver
{
  void init();
  void run();

  void pushBuff(unsigned char _key, bool _repeat = false);
  unsigned char popBuff(bool _skipRepeat = false);
  void clearBuff();
  bool getKeyState(unsigned char _keyNum);
  bool getUIRequest();
}

#endif
