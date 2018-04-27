#ifndef __LCDDRIVER_H_
#define __LCDDRIVER_H_

#include "GlobalSpace.h"

#define LCD_DISPLAY_SYMBOL_SPACE                (0x20)
#define LCD_DISPLAY_SYMBOL_COLON                (':')
#define LCD_DISPLAY_SYMBOL_SLASH                ('/')
#define LCD_DISPLAY_SYMBOL_DASH                 ('-')
#define LCD_DISPLAY_SYMBOL_BLACKBLOCK           (0xFF)
#define LCD_DISPLAY_SYMBOL_SUN                  (0xEE)
#define LCD_DISPLAY_SYMBOL_UNDERSCORE           (0x5F)
#define LCD_DISPLAY_SYMBOL_ARROWUP              (0xD9)
#define LCD_DISPLAY_SYMBOL_ARROWDOWN            (0xDA)
#define LCD_DISPLAY_SYMBOL_LOW_BATTERY          (0x04)

namespace LCDDriver
{
  typedef enum
  {
    LCDDisplayMode_OFF = 0x08,
    LCDDisplayMode_NoCursor = 0x0C,
    LCDDisplayMode_UnderscoreCursor = 0x0E,
    LCDDisplayMode_BlinkCursor = 0x0D,
    LCDDisplayMode_BothCursors = 0x0F,
  } TLCDDisplayMode;

  typedef enum
  {
    LCDDisplayEntryState_ShiftCursorLeft = 0x04,
    LCDDisplayEntryState_ShiftDisplayRight = 0x05,
    LCDDisplayEntryState_ShiftCursorRight = 0x06,
    LCDDisplayEntryState_ShiftDisplayLeft = 0x07,
  } TLCDDisplayEntryState;

  typedef enum
  {
    LCDTextIdentation_Center = 0,
    LCDTextIdentation_Left = 1,
    LCDTextIdentation_Right = 2,
  } TLCDTextIdentation;

  typedef struct
  {
    TLCDDisplayMode displayMode;
    TLCDDisplayEntryState entryState;
    unsigned char cursorPosY;
    unsigned char cursorPosX;
    unsigned char line[LCD_DISPLAY_HEIGHT][LCD_DISPLAY_WIDTH];
  } TLCDDisplayState;

  extern TLCDDisplayState displayState;

  void init();
  void enable();
  void disable();
  bool enabled();
  bool ready();

  void run();

  void clearBuffer();

  void str2Buf(
    unsigned char _lineNum,
    unsigned char __generic* _str,
    TLCDTextIdentation _identation = LCDTextIdentation_Center,
    unsigned char _pos = 0);

  void num2Buf(
    unsigned char _lineNum,
    unsigned char _linePos,
    unsigned long _value,
    unsigned char _maxSize = LCD_DISPLAY_WIDTH,
    unsigned char _fillChar = 0);

  bool resetDisplay(TLCDDisplayMode _displayMode, TLCDDisplayEntryState _entryState);
  bool refreshDisplay(
    TLCDDisplayMode _displayMode = LCDDisplayMode_NoCursor,
    unsigned char _cursorPosY = 0,
    unsigned char _cursorPosX = 0,
    bool _displayLowBatterySymbol = true,
    unsigned char _lowPatterySymbolPosY = 0,
    unsigned char _lowPatterySymbolPosX = 0);
  bool setDisplayMode(TLCDDisplayMode _displayMode);
  bool setEntryState(TLCDDisplayEntryState _entryState);
}

#endif
