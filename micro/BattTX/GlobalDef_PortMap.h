#ifndef __GLOBALDEF_PORTMAP_H_
#define __GLOBALDEF_PORTMAP_H_

#define CONFIG_KEY_DIR            (DDRD_Bit5)
#define CONFIG_KEY_PORT           (PORTD_Bit5)
#define CONFIG_KEY_PIN            (PIND_Bit5)
#define CONFIG_KEY_BIT            (PORTD5)

#define IR_GENERATOR_DIR          (DDRC_Bit0)
#define IR_GENERATOR_PORT         (PORTC_Bit0)
#define IR_GENERATOR_PIN          (PINC_Bit0)
#define IR_GENERATOR_BIT          (PORTC0)

#define INDICATOR_LED_DIR         (DDRC_Bit2)
#define INDICATOR_LED_PORT        (PORTC_Bit2)
#define INDICATOR_LED_PIN         (PINC_Bit2)
#define INDICATOR_LED_BIT         (PORTC2)

#if (BATTERY_CONFIGURATION_SELECTED == BATTERY_CONFIGURATION_LI)
  #define BATTERY_ADC_CHANNEL     (6)
#else
  #define BATTERY_ADC_CHANNEL     (7)
#endif

#endif

