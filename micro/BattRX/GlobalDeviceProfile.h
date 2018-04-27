#ifndef __GLOBALDEVICEPROFILE_H_
#define __GLOBALDEVICEPROFILE_H_

#include "GlobalSpace.h"

#define DEVICE_SERIAL_NUMBER_STR_LNG      (16)

namespace GLOBAL
{
  namespace DeviceProfile
  {
    typedef enum
    {
      CounterDetectDirectionType_NoDetection = 0,
      CounterDetectDirectionType_NoDetectionDiv2 = 1,
      CounterDetectDirectionType_Simulation = 2,
      CounterDetectDirectionType_StrongDetection = 3,
      CounterDetectDirectionType_SoftDetection = 4,
    }TCounterDetectDirectionType;

    typedef struct                                      //Параметры счетчика посетителей
    {
      TCounterDetectDirectionType detectDirection;      //Детектировать или нет направление движения
      bool invertCounting;                              //Инвертировать счет (применимо только для детекции направления)
      unsigned char bodyDetectionLevel;                 //Минимальное количество периодов необходимые для детекции объекта
    } TDeviceCounterConfig;

    typedef struct                      //Серийный номер счетчика
    {
      unsigned char corporationId0;
      unsigned char corporationId1;
      unsigned char corporationId2;
      unsigned char corporationId3;
      unsigned char corporationId4;

      unsigned short deviceId;
      unsigned char serialNumStr[DEVICE_SERIAL_NUMBER_STR_LNG + 1];
    } TDeviceSerialNumber;

    typedef struct                      //Версия счетчика
    {
      unsigned char Major;
      unsigned char Minor;
      unsigned char Release;
      unsigned short Build;
    } TApplicationVersion;

    typedef enum                                      //Режим работы устройства
    {
      DeviceStatusCode_Initialization = 0x00,         //Инициализация
      DeviceStatusCode_NormalMode = 0x01,             //Нормальный режим подсчета
    } TDeviceStatusCode;

    typedef enum                                      //Действие при запуске счетчика
    {
      DeviceStartAction_Standard = 0x00,              //Обычный запуск
      DeviceStartAction_FirstStart = 0x01,            //Первый запуск после полного сброса
    } TDeviceStartAction;

    typedef enum                                      //Тип заставки
    {
      UserMenuScreenSaverType_None = 0,               //Не отображается
      UserMenuScreenSaverType_Default = 1,            //Стандартный текст
    } TUserMenuScreenSaverType;

    typedef struct                                    //Конфигурация заставки
    {
      TUserMenuScreenSaverType screenSaverType;       //Тип
      unsigned char defaultLine0[LCD_DISPLAY_WIDTH];  //Стандартный текст (линия 1)
      unsigned char defaultLine1[LCD_DISPLAY_WIDTH];  //Стандартный текст (линия 2)
    } TUserMenuScreenSaverSetup;

    typedef enum                                      //Тип информационного блока
    {
      UserMenuInfoblockType_None = 0,                 //Не отображается
      UserMenuInfoblockType_DateTimeFull2Cnt = 1,     //Полная дата/время + 2 счетчика (до 6 знаков)
      UserMenuInfoblockType_DateTimeShort2Cnt = 2,    //Сокращенная дата/время + 2 счетчика (до 8 знаков с кратким названием)
      UserMenuInfoblockType_DateTimeShort1Cnt = 3,    //Сокращенная дата/время + 1 счетчик (до 16 знаков с названием)
      UserMenuInfoblockType_Counter2 = 4,             //2 счетчика (до 16 знаков с названием)
    } TUserMenuInfoblockType;

    typedef enum                                      //Тип счетчика в информационном блоке
    {
      UserMenuInfoblockCounterType_None = 0,            //Не отображается
      UserMenuInfoblockCounterType_VisitorsHour = 1,    //Посетителей за час
      UserMenuInfoblockCounterType_VisitorsDay = 2,     //Посетителей за день
      UserMenuInfoblockCounterType_VisitorsWeek = 3,    //Посетителей за неделю
      UserMenuInfoblockCounterType_VisitorsMonth = 4,   //Посетителей за месяц
      UserMenuInfoblockCounterType_VisitorsTotal = 5,   //Общее количество посетителей
      UserMenuInfoblockCounterType_NoSensorHour = 6,    //Перекрытий за час
      UserMenuInfoblockCounterType_NoSensorDay = 7,     //Перекрытий за день
    } TUserMenuInfoblockCounterType;

    typedef enum
    {
      UserMenuInfoblockCounterDirType_In = 0,
      UserMenuInfoblockCounterDirType_Out = 1,
      UserMenuInfoblockCounterDirType_Avg = 2,
      UserMenuInfoblockCounterDirType_Max = 3,
      UserMenuInfoblockCounterDirType_Min = 4,
    } TUserMenuInfoblockCounterDirType;

    typedef struct                                    //Конфигурация счетчика в инфоблоке
    {
      TUserMenuInfoblockCounterType counterType;      //Тип
      TUserMenuInfoblockCounterDirType counterDir;    //Направление счетчика (для счетчиков посетителей)
      unsigned char counterShift;                     //Смещение час/день/месяц (например, для даты: 0 - сегодня, 1 - вчера и т.д.)
    } TUserMenuInfoblockCounterSetup;

    typedef struct                                    //Конфигурация инфоблока
    {
      TUserMenuInfoblockType infoblockType;           //Тип инфоблока
      TUserMenuInfoblockCounterSetup counter1;        //Конфигурация 1-го счетчика
      TUserMenuInfoblockCounterSetup counter2;        //Конфигурация 2-го счетчика
    } TUserMenuInfoblockSetup;

    typedef enum                                      //Структура рабочего дня
    {
      WorkDayShiftStructure_WholeDay = 0,             //Целый день
      WorkDayShiftStructure_Shift1 = 1,               //Одна смена
      WorkDayShiftStructure_Shift2 = 2,               //Две смены
      WorkDayShiftStructure_Shift1Lunch = 3,          //Одна смена с перерывом на обед
    } TWorkDayShiftStructure;

    typedef enum                                      //Режим экономии батареи (2 раздельные опции - отключать экран и отключать подсчет когда в интерфейсе)
    {
      DeviceBatterySaveMode_Min = 0,                  //Минимум (все выключено)
      DeviceBatterySaveMode_NoCount = 1,              //Отключать подсчет
      DeviceBatterySaveMode_NoScreen = 2,             //Отключать экран
      DeviceBatterySaveMode_Max = 3,                  //Максимум (все включено)
    } TDeviceBatterySaveMode;

    typedef struct                                    //Расширенные настройки устройства
    {
      TDeviceBatterySaveMode batterySaveMode;         //Отключать экран при возврате из меню на заставку/инфоблок отключается экран (иначе экран отключается только по расписанию в нерабочее время)
      bool backlight;                                 //Подсветка в меню
      unsigned char inactivityTime;                   //Время бездействия (в секундах), после которого происходит выход из меню на начальный экран,
                                                      //или отключение экрана (в режиме экономии батареи)
                                                      //0-5 == 5
      unsigned char workWeekMask;                     //Маска рабочей недели (1 - рабочий день, 0 - выходной, 0x80 - означает работаем сегодня, стирается на следующий день автоматически.
      TWorkDayShiftStructure workDayStruct;           //Структура рабочего дня
      unsigned short shiftStart1;                     //Начало смены 1
      unsigned short shiftEnd1;                       //Конец смены 1
      unsigned short shiftStart2;                     //Начало смены 2 (или обеда)
      unsigned short shiftEnd2;                       //Конец смены 2 (или обеда)
                                                      //Структура рабочей недели позволяет экономить батарею приемника (подсчет в этом режиме отключен, экран тоже).
                                                      //Кроме того, есть возможность вести статистику более точно, отключая счетчик в нерабочее время.
      unsigned short batteryCutOff;                   //Напряжение среза при котором отображается сигнал о низком уровне заряда батареи
    } TDeviceAdvancedSetup;

    typedef enum
    {
      UserInterfaceLanguage_RUS = 0,
    } TUserInterfaceLanguage;

    typedef struct                                    //Конфигурация пользовательского интерфейса
    {
      TUserInterfaceLanguage language;
      TUserMenuScreenSaverSetup screenSaverSetup;     //Заставка
      TUserMenuInfoblockSetup infoblockMain;          //Основной инфоблок
      TUserMenuInfoblockSetup infoblockLeft;          //Инфоблок, вызываемый при нажатии кнопки <-
      TUserMenuInfoblockSetup infoblockRight;         //Инфоблок, вызываемый при нажатии кнопки ->
    } TUserInterfaceSetup;

    extern TApplicationVersion ApplicationVersion;
    extern TDeviceSerialNumber DeviceSerialNumber;
    extern TDeviceCounterConfig DeviceCounterConfig;
    extern TDeviceAdvancedSetup DeviceAdvancedSetup;
    extern TUserInterfaceSetup UserInterfaceSetup;

    extern TDeviceStatusCode DeviceStatusCode;

    extern unsigned char MemorySecureTemplate[EXT_MEMORY_SEGMENTSIZE];
  }
}

#endif

