#ifndef __GLOBALDEVICEPROFILE_H_
#define __GLOBALDEVICEPROFILE_H_

#include "GlobalSpace.h"

namespace GLOBAL
{
  namespace DeviceProfile
  {
    typedef enum                                        //������ �����������
    {
      DeviceTransmitterMode_NoDetetion = 0,             //��� �������� ��� �������� ����������� (���������)
      DeviceTransmitterMode_WithDetection = 1,          //��� �������� � ��������� ����������� (������ ����������������)
    } TDeviceTransmitterMode;

    typedef struct                                      //��������� �����������
    {
      TDeviceTransmitterMode transmitterMode;           //����� �����������
      unsigned short batteryCutOff;                     //���������� ����� ��� ������� ������������ ������ � ������ ������ ������ �������
    } TDeviceTransmitterConfig;

    typedef struct                                      //������ �����������
    {
      unsigned char Major;
      unsigned char Minor;
      unsigned char Release;
      unsigned short Build;
    } TApplicationVersion;

    typedef enum                                        //�������� ��� ������� �����������
    {
      DeviceStartAction_Standard = 0x00,                //������� ������
      DeviceStartAction_FirstStart = 0x01,              //������ ������ ����� ������� ������
    } TDeviceStartAction;

    extern TApplicationVersion ApplicationVersion;
    extern TDeviceTransmitterConfig DeviceTransmitterConfig;
  }
}

#endif

