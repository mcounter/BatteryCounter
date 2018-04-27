#ifndef __GLOBALDEF_PARAMETERS_H_
#define __GLOBALDEF_PARAMETERS_H_

#define clockFrequency                    (128000)
#define timerDiscreteness                 (4)

#define NODETECTION_PRESCALER_LEVEL       (3)

#if (((((clockFrequency/8) * timerDiscreteness * NODETECTION_PRESCALER_LEVEL)/1000) - 1) > 255)
#error Incorrect timer configuration
#endif

#define BATTERY_CONFIGURATION_LI          (0)
#define BATTERY_CONFIGURATION_STD         (1)

#define BATTERY_CONFIGURATION_SELECTED    (BATTERY_CONFIGURATION_LI)

#endif
