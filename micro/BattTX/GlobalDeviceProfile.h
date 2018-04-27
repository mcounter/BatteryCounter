#ifndef __GLOBALDEVICEPROFILE_H_
#define __GLOBALDEVICEPROFILE_H_

#include "GlobalSpace.h"

namespace GLOBAL
{
  namespace DeviceProfile
  {
    typedef enum                                        //Режимы передатчика
    {
      DeviceTransmitterMode_NoDetetion = 0,             //Для счетчика без детекции направления (экономный)
      DeviceTransmitterMode_WithDetection = 1,          //Для счетчика с детекцией направления (полная функциональность)
    } TDeviceTransmitterMode;

    typedef struct                                      //Параметры передатчика
    {
      TDeviceTransmitterMode transmitterMode;           //Режим передатчика
      unsigned short batteryCutOff;                     //Напряжение среза при котором отображается сигнал о низком уровне заряда батареи
    } TDeviceTransmitterConfig;

    typedef struct                                      //Версия передатчика
    {
      unsigned char Major;
      unsigned char Minor;
      unsigned char Release;
      unsigned short Build;
    } TApplicationVersion;

    typedef enum                                        //Действие при запуске передатчика
    {
      DeviceStartAction_Standard = 0x00,                //Обычный запуск
      DeviceStartAction_FirstStart = 0x01,              //Первый запуск после полного сброса
    } TDeviceStartAction;

    extern TApplicationVersion ApplicationVersion;
    extern TDeviceTransmitterConfig DeviceTransmitterConfig;
  }
}

#endif

