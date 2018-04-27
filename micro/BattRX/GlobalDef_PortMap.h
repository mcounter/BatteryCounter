#ifndef __GLOBALDEF_PORTMAP_H_
#define __GLOBALDEF_PORTMAP_H_

#define MENU_KEY1_DIR             (DDRB_Bit0)
#define MENU_KEY1_PORT            (PORTB_Bit0)
#define MENU_KEY1_PIN             (PINB_Bit0)
#define MENU_KEY1_BIT             (PORTB0)
#define MENU_KEY1_INT             (PCINT0)

#define MENU_KEY2_DIR             (DDRD_Bit7)
#define MENU_KEY2_PORT            (PORTD_Bit7)
#define MENU_KEY2_PIN             (PIND_Bit7)
#define MENU_KEY2_BIT             (PORTD7)
#define MENU_KEY2_INT             (PCINT23)

#define MENU_KEY3_DIR             (DDRD_Bit6)
#define MENU_KEY3_PORT            (PORTD_Bit6)
#define MENU_KEY3_PIN             (PIND_Bit6)
#define MENU_KEY3_BIT             (PORTD6)
#define MENU_KEY3_INT             (PCINT22)

#define MENU_KEY4_DIR             (DDRD_Bit5)
#define MENU_KEY4_PORT            (PORTD_Bit5)
#define MENU_KEY4_PIN             (PIND_Bit5)
#define MENU_KEY4_BIT             (PORTD5)
#define MENU_KEY4_INT             (PCINT21)

#define LCD_VDD_DIR               (DDRC_Bit3)
#define LCD_VDD_PORT              (PORTC_Bit3)
#define LCD_VDD_PIN               (PINC_Bit3)
#define LCD_VDD_BIT               (PORTC3)

#define LCD_SDA_DIR               (DDRC_Bit4)
#define LCD_SDA_PORT              (PORTC_Bit4)
#define LCD_SDA_PIN               (PINC_Bit4)
#define LCD_SDA_BIT               (PORTC4)

#define LCD_SCL_DIR               (DDRC_Bit5)
#define LCD_SCL_PORT              (PORTC_Bit5)
#define LCD_SCL_PIN               (PINC_Bit5)
#define LCD_SCL_BIT               (PORTC5)

#define LCD_BACKLIGHT_DIR         (DDRB_Bit1)
#define LCD_BACKLIGHT_PORT        (PORTB_Bit1)
#define LCD_BACKLIGHT_PIN         (PINB_Bit1)
#define LCD_BACKLIGHT_BIT         (PORTB1)

#define PHOTO1_VDD_DIR            (DDRC_Bit0)
#define PHOTO1_VDD_PORT           (PORTC_Bit0)
#define PHOTO1_VDD_PIN            (PINC_Bit0)
#define PHOTO1_VDD_BIT            (PORTC0)

#define PHOTO1_IN_DIR             (DDRD_Bit2)
#define PHOTO1_IN_PORT            (PORTD_Bit2)
#define PHOTO1_IN_PIN             (PIND_Bit2)
#define PHOTO1_IN_BIT             (PORTD2)

#define PHOTO2_VDD_DIR            (DDRC_Bit1)
#define PHOTO2_VDD_PORT           (PORTC_Bit1)
#define PHOTO2_VDD_PIN            (PINC_Bit1)
#define PHOTO2_VDD_BIT            (PORTC1)

#define PHOTO2_IN_DIR             (DDRD_Bit3)
#define PHOTO2_IN_PORT            (PORTD_Bit3)
#define PHOTO2_IN_PIN             (PIND_Bit3)
#define PHOTO2_IN_BIT             (PORTD3)

#define INDICATOR_LED_DIR         (DDRC_Bit2)
#define INDICATOR_LED_PORT        (PORTC_Bit2)
#define INDICATOR_LED_PIN         (PINC_Bit2)
#define INDICATOR_LED_BIT         (PORTC2)

#define MEM_SS_DIR                (DDRB_Bit2)
#define MEM_SS_PORT               (PORTB_Bit2)
#define MEM_SS_PIN                (PINB_Bit2)
#define MEM_SS_BIT                (PORTB2)

#define SPI_MOSI_DIR              (DDRB_Bit3)
#define SPI_MOSI_PORT             (PORTB_Bit3)
#define SPI_MOSI_PIN              (PINB_Bit3)
#define SPI_MOSI_BIT              (PORTB3)

#define SPI_MISO_DIR              (DDRB_Bit4)
#define SPI_MISO_PORT             (PORTB_Bit4)
#define SPI_MISO_PIN              (PINB_Bit4)
#define SPI_MISO_BIT              (PORTB4)

#define SPI_SCK_DIR               (DDRB_Bit5)
#define SPI_SCK_PORT              (PORTB_Bit5)
#define SPI_SCK_PIN               (PINB_Bit5)
#define SPI_SCK_BIT               (PORTB5)

#if (BATTERY_CONFIGURATION_SELECTED == BATTERY_CONFIGURATION_LI)
  #define BATTERY_ADC_CHANNEL     (6)
#else
  #define BATTERY_ADC_CHANNEL     (7)
#endif

#endif

