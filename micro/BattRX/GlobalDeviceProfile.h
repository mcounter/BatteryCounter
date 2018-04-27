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

    typedef struct                                      //��������� �������� �����������
    {
      TCounterDetectDirectionType detectDirection;      //������������� ��� ��� ����������� ��������
      bool invertCounting;                              //������������� ���� (��������� ������ ��� �������� �����������)
      unsigned char bodyDetectionLevel;                 //����������� ���������� �������� ����������� ��� �������� �������
    } TDeviceCounterConfig;

    typedef struct                      //�������� ����� ��������
    {
      unsigned char corporationId0;
      unsigned char corporationId1;
      unsigned char corporationId2;
      unsigned char corporationId3;
      unsigned char corporationId4;

      unsigned short deviceId;
      unsigned char serialNumStr[DEVICE_SERIAL_NUMBER_STR_LNG + 1];
    } TDeviceSerialNumber;

    typedef struct                      //������ ��������
    {
      unsigned char Major;
      unsigned char Minor;
      unsigned char Release;
      unsigned short Build;
    } TApplicationVersion;

    typedef enum                                      //����� ������ ����������
    {
      DeviceStatusCode_Initialization = 0x00,         //�������������
      DeviceStatusCode_NormalMode = 0x01,             //���������� ����� ��������
    } TDeviceStatusCode;

    typedef enum                                      //�������� ��� ������� ��������
    {
      DeviceStartAction_Standard = 0x00,              //������� ������
      DeviceStartAction_FirstStart = 0x01,            //������ ������ ����� ������� ������
    } TDeviceStartAction;

    typedef enum                                      //��� ��������
    {
      UserMenuScreenSaverType_None = 0,               //�� ������������
      UserMenuScreenSaverType_Default = 1,            //����������� �����
    } TUserMenuScreenSaverType;

    typedef struct                                    //������������ ��������
    {
      TUserMenuScreenSaverType screenSaverType;       //���
      unsigned char defaultLine0[LCD_DISPLAY_WIDTH];  //����������� ����� (����� 1)
      unsigned char defaultLine1[LCD_DISPLAY_WIDTH];  //����������� ����� (����� 2)
    } TUserMenuScreenSaverSetup;

    typedef enum                                      //��� ��������������� �����
    {
      UserMenuInfoblockType_None = 0,                 //�� ������������
      UserMenuInfoblockType_DateTimeFull2Cnt = 1,     //������ ����/����� + 2 �������� (�� 6 ������)
      UserMenuInfoblockType_DateTimeShort2Cnt = 2,    //����������� ����/����� + 2 �������� (�� 8 ������ � ������� ���������)
      UserMenuInfoblockType_DateTimeShort1Cnt = 3,    //����������� ����/����� + 1 ������� (�� 16 ������ � ���������)
      UserMenuInfoblockType_Counter2 = 4,             //2 �������� (�� 16 ������ � ���������)
    } TUserMenuInfoblockType;

    typedef enum                                      //��� �������� � �������������� �����
    {
      UserMenuInfoblockCounterType_None = 0,            //�� ������������
      UserMenuInfoblockCounterType_VisitorsHour = 1,    //����������� �� ���
      UserMenuInfoblockCounterType_VisitorsDay = 2,     //����������� �� ����
      UserMenuInfoblockCounterType_VisitorsWeek = 3,    //����������� �� ������
      UserMenuInfoblockCounterType_VisitorsMonth = 4,   //����������� �� �����
      UserMenuInfoblockCounterType_VisitorsTotal = 5,   //����� ���������� �����������
      UserMenuInfoblockCounterType_NoSensorHour = 6,    //���������� �� ���
      UserMenuInfoblockCounterType_NoSensorDay = 7,     //���������� �� ����
    } TUserMenuInfoblockCounterType;

    typedef enum
    {
      UserMenuInfoblockCounterDirType_In = 0,
      UserMenuInfoblockCounterDirType_Out = 1,
      UserMenuInfoblockCounterDirType_Avg = 2,
      UserMenuInfoblockCounterDirType_Max = 3,
      UserMenuInfoblockCounterDirType_Min = 4,
    } TUserMenuInfoblockCounterDirType;

    typedef struct                                    //������������ �������� � ���������
    {
      TUserMenuInfoblockCounterType counterType;      //���
      TUserMenuInfoblockCounterDirType counterDir;    //����������� �������� (��� ��������� �����������)
      unsigned char counterShift;                     //�������� ���/����/����� (��������, ��� ����: 0 - �������, 1 - ����� � �.�.)
    } TUserMenuInfoblockCounterSetup;

    typedef struct                                    //������������ ���������
    {
      TUserMenuInfoblockType infoblockType;           //��� ���������
      TUserMenuInfoblockCounterSetup counter1;        //������������ 1-�� ��������
      TUserMenuInfoblockCounterSetup counter2;        //������������ 2-�� ��������
    } TUserMenuInfoblockSetup;

    typedef enum                                      //��������� �������� ���
    {
      WorkDayShiftStructure_WholeDay = 0,             //����� ����
      WorkDayShiftStructure_Shift1 = 1,               //���� �����
      WorkDayShiftStructure_Shift2 = 2,               //��� �����
      WorkDayShiftStructure_Shift1Lunch = 3,          //���� ����� � ��������� �� ����
    } TWorkDayShiftStructure;

    typedef enum                                      //����� �������� ������� (2 ���������� ����� - ��������� ����� � ��������� ������� ����� � ����������)
    {
      DeviceBatterySaveMode_Min = 0,                  //������� (��� ���������)
      DeviceBatterySaveMode_NoCount = 1,              //��������� �������
      DeviceBatterySaveMode_NoScreen = 2,             //��������� �����
      DeviceBatterySaveMode_Max = 3,                  //�������� (��� ��������)
    } TDeviceBatterySaveMode;

    typedef struct                                    //����������� ��������� ����������
    {
      TDeviceBatterySaveMode batterySaveMode;         //��������� ����� ��� �������� �� ���� �� ��������/�������� ����������� ����� (����� ����� ����������� ������ �� ���������� � ��������� �����)
      bool backlight;                                 //��������� � ����
      unsigned char inactivityTime;                   //����� ����������� (� ��������), ����� �������� ���������� ����� �� ���� �� ��������� �����,
                                                      //��� ���������� ������ (� ������ �������� �������)
                                                      //0-5 == 5
      unsigned char workWeekMask;                     //����� ������� ������ (1 - ������� ����, 0 - ��������, 0x80 - �������� �������� �������, ��������� �� ��������� ���� �������������.
      TWorkDayShiftStructure workDayStruct;           //��������� �������� ���
      unsigned short shiftStart1;                     //������ ����� 1
      unsigned short shiftEnd1;                       //����� ����� 1
      unsigned short shiftStart2;                     //������ ����� 2 (��� �����)
      unsigned short shiftEnd2;                       //����� ����� 2 (��� �����)
                                                      //��������� ������� ������ ��������� ��������� ������� ��������� (������� � ���� ������ ��������, ����� ����).
                                                      //����� ����, ���� ����������� ����� ���������� ����� �����, �������� ������� � ��������� �����.
      unsigned short batteryCutOff;                   //���������� ����� ��� ������� ������������ ������ � ������ ������ ������ �������
    } TDeviceAdvancedSetup;

    typedef enum
    {
      UserInterfaceLanguage_RUS = 0,
    } TUserInterfaceLanguage;

    typedef struct                                    //������������ ����������������� ����������
    {
      TUserInterfaceLanguage language;
      TUserMenuScreenSaverSetup screenSaverSetup;     //��������
      TUserMenuInfoblockSetup infoblockMain;          //�������� ��������
      TUserMenuInfoblockSetup infoblockLeft;          //��������, ���������� ��� ������� ������ <-
      TUserMenuInfoblockSetup infoblockRight;         //��������, ���������� ��� ������� ������ ->
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

