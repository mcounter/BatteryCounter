#ifndef __COMMPROTOCOL_TWI_MASTER_CPP_
#define __COMMPROTOCOL_TWI_MASTER_CPP_

#include "CommProtocol_TWI_Master.h"
#include "MultyThreading.h"

#define TWI_BUFFER_TRANS_TIMEOUT        (1000)

namespace CommProtocol_TWI_Master
{
  typedef enum
  {
    TWIStatusCode_Start = 0x08,
    TWIStatusCode_RepStart = 0x10,
    TWIStatusCode_AbrLost = 0x38,

    TWIStatusCode_MTX_AdrAck = 0x18,
    TWIStatusCode_MTX_AdrNack = 0x20,
    TWIStatusCode_MTX_DataAck = 0x28,
    TWIStatusCode_MTX_DataNack = 0x30,

    TWIStatusCode_MRX_AdrAck = 0x40,
    TWIStatusCode_MRX_AdrNack = 0x48,
    TWIStatusCode_MRX_DataAck = 0x50,
    TWIStatusCode_MRX_DataNack = 0x58,

    TWIStatusCode_STX_AdrAck = 0xA8,
    TWIStatusCode_STX_AdrAck_MasterArbLost = 0xB0,
    TWIStatusCode_STX_DataAck = 0xB8,
    TWIStatusCode_STX_DataNack = 0xC0,
    TWIStatusCode_STX_DataAck_LastByte = 0xC8,

    TWIStatusCode_SRX_AdrAck = 0x60,
    TWIStatusCode_SRX_AdrAck_MasterArbLost = 0x68,
    TWIStatusCode_SRX_GenAck = 0x70,
    TWIStatusCode_SRX_GenAck_MasterArbLost = 0x78,
    TWIStatusCode_SRX_AdrDataAck = 0x80,
    TWIStatusCode_SRX_AdrDataNack = 0x88,
    TWIStatusCode_SRX_GenDataAck = 0x90,
    TWIStatusCode_SRX_GenDataNack = 0x98,
    TWIStatusCode_SRX_StopRestart = 0xA0,

    TWIStatusCode_NoState = 0xF8,
    TWIStatusCode_BusError = 0x00,
  } TTWIStatusCode;

  TTWIBuffer bufferTWI =
  {
    .length = 0,
    .status = TWIBufferStatus_None,
    .result = TWIResultCodeType_OK,
  };

  bool isEnabled = false;
  unsigned short bufferPos = 0;

  __monitor void enable()
  {
    bufferTWI.status = TWIBufferStatus_None;

    PRR &= ~(1<<PRTWI);

    LCD_SDA_DIR = 0;
    LCD_SDA_PORT = 1;

    LCD_SCL_DIR = 0;
    LCD_SCL_PORT = 1;

    TWBR = (clockFrequency/TWIClockFrequency/2) - 8;

    TWSR = TWIStatusCode_NoState & 0xF8;              // Prescaler = 1, Status = No_State
    TWDR = 0xFF;                                      // Default content = SDA released.
    TWCR = (1<<TWEN)|                                 // Enable TWI-interface and release TWI pins.
           (0<<TWIE)|(0<<TWINT)|                      // Disable Interupt.
           (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|           // No Signal requests.
           (0<<TWWC);                                 //

    isEnabled = true;
  }

  __monitor void disable()
  {
    isEnabled = false;

    TWCR = 0x00;
    PRR |= (1<<PRTWI);

    LCD_SDA_DIR = 1;
    LCD_SDA_PORT = 0;

    LCD_SCL_DIR = 1;
    LCD_SCL_PORT = 0;
  }

  bool enabled()
  {
    return isEnabled;
  }

  bool ready()
  {
    return isEnabled &&
           ((bufferTWI.status == TWIBufferStatus_None) ||
            (bufferTWI.status == TWIBufferStatus_Processed));
  }

  __monitor void init()
  {
    disable();
  }

  bool txBusy()
  {
    return (TWCR & (1<<TWIE));
  }

  void cancel()
  {
    TWCR = (1<<TWEN)|                                     // TWI Interface enabled
           (0<<TWIE)|(0<<TWINT)|                          // Disable TWI Interrupt
           (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|               //
           (0<<TWWC);                                     //
  }

  void cancelWithError()
  {
    cancel();

    bufferTWI.result = TWIResultCodeType_Error;
    bufferTWI.length = 0;
    bufferTWI.status = TWIBufferStatus_Processed;
  }

  void start()
  {
    if (bufferTWI.length <= 0)
    {
      cancelWithError();
      return;
    }

    bufferPos = 0;
    TWCR = (1<<TWEN)|                                       // TWI Interface enabled.
           (1<<TWIE)|(1<<TWINT)|                            // Enable TWI Interupt and clear the flag.
           (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|                 // Initiate a START condition.
           (0<<TWWC);                                       //
  }

  void stop()
  {
    bufferTWI.result = TWIResultCodeType_OK;
    bufferTWI.status = TWIBufferStatus_Processed;
    TWCR = (1<<TWEN)|                                       // TWI Interface enabled
           (0<<TWIE)|(1<<TWINT)|                            // Disable TWI Interrupt and clear the flag
           (0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|                 // Initiate a STOP condition.
           (0<<TWWC);                                       //
  }

  bool send()
  {
    if (txBusy() || (bufferTWI.status != TWIBufferStatus_Ready))
    {
      return false;
    }

    start();

    return true;
  }

  void sendByte()
  {
    if (bufferPos < bufferTWI.length)
    {
      TWDR = bufferTWI.buffer[bufferPos];
      bufferPos++;

      TWCR = (1<<TWEN)|                                     // TWI Interface enabled
             (1<<TWIE)|(1<<TWINT)|                          // Enable TWI Interupt and clear the flag to send byte
             (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|               //
             (0<<TWWC);                                     //
    }
    else
    {
      stop();
    }
  }

  void startReceiveNextByte()
  {
    if (bufferPos < (bufferTWI.length - 1))                 // Detect the last byte to NACK it.
    {
      TWCR = (1<<TWEN)|                                     // TWI Interface enabled
             (1<<TWIE)|(1<<TWINT)|                          // Enable TWI Interupt and clear the flag to read next byte
             (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|               // Send ACK after reception
             (0<<TWWC);                                     //
    }
    else
    {
      TWCR = (1<<TWEN)|                                     // TWI Interface enabled
             (1<<TWIE)|(1<<TWINT)|                          // Enable TWI Interupt and clear the flag to read next byte
             (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|               // Send NACK after reception
             (0<<TWWC);                                     //
    }
  }

  void receiveByte(bool _last)
  {
    if (bufferPos < bufferTWI.length)
    {
      bufferTWI.buffer[bufferPos] = TWDR;
      bufferPos++;
    }

    if (_last)
    {
      stop();
    }
    else
    {
      startReceiveNextByte();
    }
  }

  #pragma vector=TWI_vect
  __interrupt void TWIEventIRQ()
  {
    TTWIStatusCode curStatus = (TTWIStatusCode)(TWSR & 0xF8);

    if (bufferTWI.status == TWIBufferStatus_Ready)
    {
      bufferTWI.status = TWIBufferStatus_InProcess;
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_TWIMASTER_ERRORTIMER, TWI_BUFFER_TRANS_TIMEOUT);
    }

    if (bufferTWI.status != TWIBufferStatus_InProcess)
    {
      cancel();
      return;
    }

    switch (curStatus)
    {
      case TWIStatusCode_Start:                             // START has been transmitted
      case TWIStatusCode_RepStart:                          // Repeated START has been transmitted
        bufferPos = 0;
        sendByte();
        break;

      case TWIStatusCode_MTX_AdrAck:                        // SLA+W has been tramsmitted and ACK received
      case TWIStatusCode_MTX_DataAck:                       // Data byte has been tramsmitted and ACK received
        sendByte();
        break;

      case TWIStatusCode_MRX_DataAck:                       // Data byte has been received and ACK tramsmitted
        receiveByte(false);
        break;

      case TWIStatusCode_MRX_AdrAck:                        // SLA+R has been tramsmitted and ACK received
        startReceiveNextByte();
        break;

      case TWIStatusCode_MRX_DataNack:                      // Data byte has been received and NACK tramsmitted
        receiveByte(true);
        break;

      case TWIStatusCode_AbrLost:                           // Arbitration lost
        start();
        break;

      case TWIStatusCode_MTX_AdrNack:                       // SLA+W has been tramsmitted and NACK received
      case TWIStatusCode_MRX_AdrNack:                       // SLA+R has been tramsmitted and NACK received
      case TWIStatusCode_MTX_DataNack:                      // Data byte has been tramsmitted and NACK received
      case TWIStatusCode_BusError:                          // Bus error due to an illegal START or STOP condition
      default:                                              // Incorrect status
        cancelWithError();
        break;
    }
  }

  void run()
  {
    if (!isEnabled)
    {
      return;
    }

    switch (bufferTWI.status)
    {
      case TWIBufferStatus_Ready:
        send();
        break;

      case TWIBufferStatus_InProcess:
        if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_TWIMASTER_ERRORTIMER))
        {
          cancelWithError();
        }
        break;
    }
  }
}

#endif

