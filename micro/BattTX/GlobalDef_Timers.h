#ifndef __GLOBALTIMERS_H_
#define __GLOBALTIMERS_H_

#define GLOBALHOLDTIMERS_COUNT                  (0)
#define GLOBALCOMMONTIMERS_COUNT                (4)
#define GLOBALTIMERS_COUNT                      (GLOBALHOLDTIMERS_COUNT + GLOBALCOMMONTIMERS_COUNT)
#define GLOBALCLOCKS_COUNT                      (0)

//Hold timers
//#define GLOBALTIMERS_NAME_HOLDTIMER             (0)

//Other timers
//#define GLOBALTIMERS_NAME_ERRORTIMER            (0)
#define GLOBALTIMERS_ADC_ERRORTIMER             (0)
#define GLOBALTIMERS_ADC_DELAYTIMER             (1)
#define GLOBALTIMERS_INDICATOR_WAITINGTIMER     (2)
#define GLOBALTIMERS_KEYBOARD_KEYTHRESHOLD      (3)

//Clocks
//#define GLOBALCLOCK_NAME                        (0)

#endif

