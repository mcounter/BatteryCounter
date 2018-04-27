#ifndef __PHOTOSENSOR_CPP_
#define __PHOTOSENSOR_CPP_

#include "PhotoSensor.h"
#include "GlobalCounter.h"
#include "Timer0Handler.h"

#define COUNTER_PHOTO_SWITCHON_TIME       (1000 / timerDiscreteness)
#define COUNTER_PHOTO_QUALITY_BASE        (1000 / timerDiscreteness)
#define COUNTER_PRESCALER_LEVEL           (3)
#define COUNTER_LIGHT_THRESHOLD           (30 / timerDiscreteness)
#define COUNTER_NOSENSOR_DET_THRESHOLD    (15000 / timerDiscreteness)
#define COUNTER_NOSENSOR_INC_DISCRET_SEC  (5)

namespace PhotoSensor
{
  bool isEnabled = false;
  unsigned short switchOnTime = 0;

  unsigned short idleTimeCnt = 0;
  bool isBodyDetected = false;
  bool counterDirection = false;

  unsigned short counterCnt = 0;
  unsigned char counterPrescaler = 0;
  unsigned short counterQualityCnt1 = 0;
  unsigned char counterQualityPct1 = 0;
  unsigned short counterQualityCnt2 = 0;
  unsigned char counterQualityPct2 = 0;

  unsigned char counterDetectorMatrix[2] = {0, 0};
  unsigned char counterDetectorPos = 0;

  unsigned short counterNoSensor = 0;
  bool counterNoSensorDetected = false;

  __monitor void disable()
  {
    EIMSK &= 0xFF ^ ((1<<INT0) | (1<<INT1)); // Disable interrupts

    PHOTO1_VDD_DIR = 1;
    PHOTO1_VDD_PORT = 0;

    PHOTO1_IN_DIR = 1;
    PHOTO1_IN_PORT = 0;

    PHOTO2_VDD_DIR = 1;
    PHOTO2_VDD_PORT = 0;

    PHOTO2_IN_DIR = 1;
    PHOTO2_IN_PORT = 0;

    isEnabled = false;
  }

  __monitor void enable()
  {
    Timer0Handler::enable();

    PHOTO1_VDD_DIR = 1;
    PHOTO1_VDD_PORT = 1;

    PHOTO1_IN_DIR = 0;
    PHOTO1_IN_PORT = 0;

    EICRA &= 0xFF ^ ((1<<ISC00) | (1<<ISC01));  //
    EICRA |= (1<<ISC01);                        // The falling edge generates an interrupt request

    if (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection >= GLOBAL::DeviceProfile::CounterDetectDirectionType_StrongDetection)
    {
      PHOTO2_VDD_DIR = 1;
      PHOTO2_VDD_PORT = 1;

      PHOTO2_IN_DIR = 0;
      PHOTO2_IN_PORT = 0;

      EICRA &= 0xFF ^ ((1<<ISC10) | (1<<ISC11));  //
      EICRA |= (1<<ISC11);                        // The falling edge generates an interrupt request
    }

    idleTimeCnt = 0;
    isBodyDetected = false;
    counterCnt = 0;
    counterPrescaler = 0;

    counterDetectorMatrix[0] = 0x03;
    counterDetectorMatrix[1] = 0x03;
    counterDetectorPos = 0;

    counterQualityCnt1 = 0;
    counterQualityPct1 = 0;
    counterQualityCnt2 = 0;
    counterQualityPct2 = 0;

    counterNoSensor = 0;
    counterNoSensorDetected = false;

    switchOnTime = COUNTER_PHOTO_SWITCHON_TIME;

    isEnabled = true;
  }

  __monitor bool enabled()
  {
    return isEnabled;
  }

  void addCounterValueSoftDetection()
  {
    counterDirection = !counterDirection;

    switch (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection)
    {
      case GLOBAL::DeviceProfile::CounterDetectDirectionType_NoDetection:
        GLOBAL::Counter::addCounter(1, 0, 0);
        break;

      case GLOBAL::DeviceProfile::CounterDetectDirectionType_NoDetectionDiv2:
        if (counterDirection)
        {
          GLOBAL::Counter::addCounter(1, 0, 0);
        }
        break;

      case GLOBAL::DeviceProfile::CounterDetectDirectionType_Simulation:
      case GLOBAL::DeviceProfile::CounterDetectDirectionType_SoftDetection:
        if (counterDirection ^ GLOBAL::DeviceProfile::DeviceCounterConfig.invertCounting)
        {
          GLOBAL::Counter::addCounter(1, 0, 0);
        }
        else
        {
          GLOBAL::Counter::addCounter(0, 1, 0);
        }
        break;
    }
  }

  void addCounterValueStrongDetection(bool _isOutCnt)
  {
    if (_isOutCnt ^ GLOBAL::DeviceProfile::DeviceCounterConfig.invertCounting)
    {
      GLOBAL::Counter::addCounter(0, 1, 0);
    }
    else
    {
      GLOBAL::Counter::addCounter(1, 0, 0);
    }
  }

  __monitor void processIdleTime()
  {
    if (!isEnabled)
    {
      return;
    }

    if (switchOnTime)
    {
      switchOnTime--;
      return;
    }

    if (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection >= GLOBAL::DeviceProfile::CounterDetectDirectionType_StrongDetection)
    {
      counterCnt++;

      unsigned char detectedValue = 0x00;

      if (EIFR & (1<<INTF0))
      {
        detectedValue |= 0x01;

        EIFR |= (1<<INTF0);

        counterQualityCnt1++;
      }

      if (EIFR & (1<<INTF1))
      {
        detectedValue |= 0x02;

        EIFR |= (1<<INTF1);

        counterQualityCnt2++;
      }

      if (detectedValue == 0x03)
      {
        counterNoSensor = 0;
        counterNoSensorDetected = false;

        if (counterDetectorPos >= 1)
        {
          if ((counterDetectorMatrix[0] == 0x03) || (counterDetectorMatrix[1] == 0x03))
          {
            if (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection == GLOBAL::DeviceProfile::CounterDetectDirectionType_SoftDetection)
            {
              if (counterDetectorMatrix[0] == counterDetectorMatrix[1])
              {
                addCounterValueSoftDetection();
              }
              else if ((counterDetectorMatrix[0] == 0x01) || (counterDetectorMatrix[1] == 0x02))
              {
                addCounterValueStrongDetection(false);
              }
              else
              {
                addCounterValueStrongDetection(true);
              }
            }
          }
          else if (counterDetectorMatrix[0] != counterDetectorMatrix[1])
          {
            if (counterDetectorMatrix[0] == 0x01)
            {
              addCounterValueStrongDetection(false);
            }
            else
            {
              addCounterValueStrongDetection(true);
            }
          }
        }

        idleTimeCnt = 0;
        counterDetectorPos = 0;
        counterDetectorMatrix[0] = 0x03;
        counterDetectorMatrix[1] = 0x03;
      }
      else
      {
        counterNoSensor++;

        if (detectedValue == 0x00)
        {
          if (counterDetectorPos <= 0)
          {
            idleTimeCnt++;

            if (idleTimeCnt >= GLOBAL::DeviceProfile::DeviceCounterConfig.bodyDetectionLevel)
            {
              counterDetectorPos = 1;
              counterDetectorMatrix[1] = 0x03;
            }
          }
        }
        else
        {
          idleTimeCnt = 0;
          counterDetectorMatrix[counterDetectorPos] = detectedValue;
        }
      }
    }
    else
    {
      counterPrescaler = (counterPrescaler + 1) % COUNTER_PRESCALER_LEVEL;

      if (counterPrescaler != 0)
      {
        return;
      }

      counterCnt += COUNTER_PRESCALER_LEVEL;

      if (EIFR & (1<<INTF0))
      {
        EIFR |= (1<<INTF0);

        counterQualityCnt1 += COUNTER_PRESCALER_LEVEL;
        counterNoSensor = 0;
        counterNoSensorDetected = false;

        if (idleTimeCnt >= ((unsigned short)(GLOBAL::DeviceProfile::DeviceCounterConfig.bodyDetectionLevel) + (COUNTER_BODY_DETECTION_ADD_MS / timerDiscreteness)))
        {
          isBodyDetected = true;
        }
        else if (isBodyDetected && (idleTimeCnt <= COUNTER_LIGHT_THRESHOLD))
        {
            addCounterValueSoftDetection();
            isBodyDetected = false;
        }

        idleTimeCnt = 0;
      }
      else
      {
        counterNoSensor += COUNTER_PRESCALER_LEVEL;

        if (idleTimeCnt < ((unsigned short)(GLOBAL::DeviceProfile::DeviceCounterConfig.bodyDetectionLevel) + (COUNTER_BODY_DETECTION_ADD_MS / timerDiscreteness)))
        {
          idleTimeCnt += COUNTER_PRESCALER_LEVEL;
        }
      }
    }

    if (counterCnt >= COUNTER_PHOTO_QUALITY_BASE)
    {
      counterQualityPct1 = (counterQualityCnt1 * 100) / counterCnt;
      counterQualityCnt1 = 0;
      counterQualityPct2 = (counterQualityCnt2 * 100) / counterCnt;
      counterQualityCnt2 = 0;
      counterCnt = 0;
    }

    if (counterNoSensor >= COUNTER_NOSENSOR_DET_THRESHOLD)
    {
      counterNoSensorDetected = true;
    }

    if (counterNoSensorDetected)
    {
      unsigned char curCounterDelta = counterNoSensor / (1000 / timerDiscreteness);

      if (curCounterDelta > COUNTER_NOSENSOR_INC_DISCRET_SEC)
      {
        GLOBAL::Counter::addCounter(0, 0, curCounterDelta);
        counterNoSensor = counterNoSensor % (1000 / timerDiscreteness);
      }
    }
  }

  __monitor unsigned char getCounterQualityPct1()
  {
    return counterQualityPct1;
  }

  __monitor unsigned char getCounterQualityPct2()
  {
    return counterQualityPct2;
  }

  __monitor void init()
  {
    counterDirection = false;

    disable();
  }
}

#endif

