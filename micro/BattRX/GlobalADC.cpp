#ifndef __GLOBALADC_CPP_
#define __GLOBALADC_CPP_

#include "GlobalADC.h"
#include "MultyThreading.h"

#define BATTERY_REFERENCE_VOLTAGE       (275)
#define BATTERY_MEASURE_TIMEOUT         (1000)
#define BATTERY_MEASURE_SWITCHON_TIME   (200)

namespace GLOBAL
{
  namespace ADC
  {
    bool isBusy = false;
    bool curBatteryVoltageDetected = false;

    unsigned char batteryCutOffVoltage = 0;
    unsigned char batteryCurrentVoltage = 0xFF;

    void scheduleConversion()
    {
      ADMUX = (0<<REFS0) | (0<<REFS1) | (1<<ADLAR) | BATTERY_ADC_CHANNEL;
      ADCSRA = (1<<ADEN) | (1<<ADSC) | (0<<ADATE) | (1<<ADIE) |
               (0<<ADPS0) | (0<<ADPS1) | (1<<ADPS2);
    }

    __monitor void startConversion()
    {
      if (isBusy)
      {
        return;
      }

      isBusy = true;

      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_ADC_ERRORTIMER, BATTERY_MEASURE_TIMEOUT);

      PRR &= ~(1<<PRADC);
      scheduleConversion();
    }

    __monitor void disable()
    {
      ADCSRA &= ~(1<<ADEN);
      PRR |= (1<<PRADC);

      isBusy = false;
    }

    #pragma vector=ADC_vect
    __interrupt void irqADC()
    {
      batteryCurrentVoltage = ADCH;
      curBatteryVoltageDetected = true;

      disable();
    }

    __monitor bool isBatteryVoltageDetected()
    {
      return curBatteryVoltageDetected;
    }

    __monitor unsigned short getBatteryCurrentVoltage()
    {
      return (((unsigned long)batteryCurrentVoltage) * 2 * BATTERY_REFERENCE_VOLTAGE) / 256;
    }

    __monitor void setCutOffVoltage(unsigned short _cutOffVoltage)
    {
      batteryCutOffVoltage = (((unsigned long)_cutOffVoltage * 256) / 2 / BATTERY_REFERENCE_VOLTAGE);
    }

    __monitor bool isLowBatteryVoltage()
    {
      return batteryCurrentVoltage < batteryCutOffVoltage;
    }

    bool ready()
    {
      return !isBusy;
    }

    void init(unsigned short _cutOffVoltage)
    {
      isBusy = true;
      curBatteryVoltageDetected = false;

      setCutOffVoltage(_cutOffVoltage);
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_ADC_ERRORTIMER, BATTERY_MEASURE_SWITCHON_TIME);
    }

    void run()
    {
      if (isBusy)
      {
        if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_ADC_ERRORTIMER))
        {
          disable();

          if (!curBatteryVoltageDetected)
          {
            startConversion();
          }
        }
      }
    }
  }
}

#endif

