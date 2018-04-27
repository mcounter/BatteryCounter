#ifndef __GLOBALDEF_PARAMETERS_H_
#define __GLOBALDEF_PARAMETERS_H_

#define clockFrequency                    (128000)
#define timerDiscreteness                 (5)
#define TWIClockFrequency                 (2560)

#define EXT_MEMORY_SIZE_HOUR_SEGMENT      (12288)
#define EXT_MEMORY_SIZE_DAY_SEGMENT       (3584)
#define EXT_MEMORY_SIZE_MONTH_SEGMENT     (512)
#define EXT_MEMORY_SIZE_TOTAL             (16384)
#define EXT_MEMORY_SEGMENTSIZE            (16)

#if (EXT_MEMORY_SIZE_HOUR_SEGMENT+EXT_MEMORY_SIZE_DAY_SEGMENT+EXT_MEMORY_SIZE_MONTH_SEGMENT > EXT_MEMORY_SIZE_TOTAL)
#error Incorrect memory size
#endif

#define COMMBUFFERSIZE_TWI_MASTER         (64)
#define COMMBUFFERSIZE_SPI_MASTER         (32)

#define LCD_DISPLAY_HEIGHT                (2)
#define LCD_DISPLAY_WIDTH                 (16)

#define DEVICE_PASSWORD_LENGTH            (8)
#define COUNTER_BODY_DETECTION_ADD_MS     (30)

#define BATTERY_CONFIGURATION_LI          (0)
#define BATTERY_CONFIGURATION_STD         (1)

#define BATTERY_CONFIGURATION_SELECTED    (BATTERY_CONFIGURATION_LI)

#endif
