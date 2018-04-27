#ifndef __GLOBALADC_CPP_
#define __GLOBALADC_CPP_

#include "GlobalADC.h"
#include "MultyThreading.h"
#include "IndicatorDriver.h"

#define BATTERY_REFERENCE_VOLTAGE       (275)
#define BATTERY_MEASURE_TIMEOUT         (1000)
#define BATTERY_MEASURE_SWITCHON_TIME   (200)

#define ADC_DELAYTIMER_PERIOD_MS        (30000)       //30 seconds
#define ADC_DELAYTIMER_DISPLAYPERIOD    (30)          //15 minutes
#define ADC_DELAYTIMER_MEASUREPERIOD    (120)         //1 hour

namespace GLOBAL
{
  namespace ADC
  {
    bool isBusy = false;
    bool curBatteryVoltageDetected = false;

    unsigned char batteryCutOffVoltage = 0;
    unsigned char batteryCurrentVoltage = 0xFF;

    unsigned char delayPeriodNum = 0;

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
      delayPeriodNum = 0;

      setCutOffVoltage(_cutOffVoltage);
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_ADC_ERRORTIMER, BATTERY_MEASURE_SWITCHON_TIME);
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_ADC_DELAYTIMER, ADC_DELAYTIMER_PERIOD_MS);
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

      if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_ADC_DELAYTIMER))
      {
        GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_ADC_DELAYTIMER, ADC_DELAYTIMER_PERIOD_MS);

        delayPeriodNum = (delayPeriodNum + 1) % ADC_DELAYTIMER_MEASUREPERIOD;

        if ((delayPeriodNum % ADC_DELAYTIMER_DISPLAYPERIOD) == 0)
        {
          if (isLowBatteryVoltage())
          {
            IndicatorDriver::schedule(3, 150, 250);
          }
        }

        if (delayPeriodNum == 0)
        {
          startConversion();
        }
      }
    }
  }
}

#endif

