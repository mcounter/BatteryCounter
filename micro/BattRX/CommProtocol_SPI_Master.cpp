#ifndef __COMMPROTOCOL_SPI_MASTER_CPP_
#define __COMMPROTOCOL_SPI_MASTER_CPP_

#include "CommProtocol_SPI_Master.h"
#include "MultyThreading.h"

#define SPI_BUFFER_TRANS_TIMEOUT        (1000)
#define SPI_MASTER_HOLDTIME             (1)

namespace CommProtocol_SPI_Master
{
  TSPIBuffer bufferSPI =
  {
    .length = 0,
    .status = SPIBufferStatus_None,
    .result = SPIResultCodeType_OK,
  };

  bool isEnabled = false;
  unsigned short bufferPos = 0;

  void spiStart()
  {
    // Clear the SPIF flag
    volatile unsigned char dummy;
    dummy = SPSR;
    dummy = SPDR;

    MEM_SS_PORT = 0;

    SPCR |= (1 << SPIE);
  }

  void spiStop()
  {
    MEM_SS_PORT = 1;

    SPCR &= ~(1 << SPIE);
  }

  __monitor void enable()
  {
    bufferSPI.status = SPIBufferStatus_None;

    PRR &= ~(1<<PRSPI);
    SPCR = (0<<SPE);                    // Disable the SPI

    MEM_SS_DIR = 1;
    MEM_SS_PORT = 1;

    SPI_SCK_DIR = 1;
    SPI_SCK_PORT = 1;

    SPI_MOSI_DIR = 1;
    SPI_MOSI_PORT = 1;

    SPI_MISO_DIR = 0;
    SPI_MISO_PORT = 1;

    SPCR = (1<<MSTR);                   // Select the master mode prior to enable the SPI
    SPSR = 1<<SPI2X;                    // Select double speed mode;
    SPCR = (0<<SPIE) |                  // Disable the SPI interrupt line,
           (1<<SPE) |                   // Enable the SPI
           (1<<MSTR) |                  // Select the master
           (0<<DORD) |                  // Select the MSB first transmitted bit
           (0<<CPOL) | (0<<CPHA) |      // SPI mode 0
           (0<<SPR1) | (0<<SPR0);       // Clock prescaler 2

    spiStop();

    isEnabled = true;
  }

  __monitor void disable()
  {
    isEnabled = false;

    SPCR = (0<<SPE);                    // Disable the SPI
    PRR |= (1<<PRSPI);

    MEM_SS_DIR = 1;
    MEM_SS_PORT = 1;

    SPI_SCK_DIR = 1;
    SPI_SCK_PORT = 1;

    SPI_MOSI_DIR = 1;
    SPI_MOSI_PORT = 1;

    SPI_MISO_DIR = 0;
    SPI_MISO_PORT = 1;
  }

  bool enabled()
  {
    return isEnabled;
  }

  bool ready()
  {
    return isEnabled &&
           ((bufferSPI.status == SPIBufferStatus_None) ||
            (bufferSPI.status == SPIBufferStatus_Processed));
  }

  __monitor void init()
  {
    disable();
  }

  void sendByte()
  {
    SPDR = bufferSPI.buffer[bufferPos];
  }

  void cancelWithError()
  {
    spiStop();

    bufferSPI.result = SPIResultCodeType_Error;
    bufferSPI.length = 0;
    bufferSPI.status = SPIBufferStatus_Processed;
  }

  void start()
  {
    if (bufferSPI.length <= 0)
    {
      cancelWithError();
      return;
    }

    bufferPos = 0;
    bufferSPI.result = SPIResultCodeType_OK;
    bufferSPI.status = SPIBufferStatus_InProcess;
    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_SPIMASTER_ERRORTIMER, SPI_BUFFER_TRANS_TIMEOUT);

    spiStart();

    sendByte();
  }

  void stop()
  {
    bufferSPI.result = SPIResultCodeType_OK;
    bufferSPI.status = SPIBufferStatus_Processed;

    spiStop();
  }

  bool send()
  {
    if (bufferSPI.status != SPIBufferStatus_Ready)
    {
      return false;
    }

    start();

    return true;
  }

  #pragma vector=SPI_STC_vect
  __interrupt void SPIEventIRQ()
  {
    if (bufferSPI.status != SPIBufferStatus_InProcess)
    {
      spiStop();
      return;
    }

    if (SPSR & (1 << WCOL))
    {
      cancelWithError();
      return;
    }

    bufferSPI.buffer[bufferPos] = SPDR;
    bufferPos++;

    if (bufferPos >= bufferSPI.length)
    {
      stop();
    }
    else
    {
      sendByte();
    }
  }

  void run()
  {
    if (!isEnabled)
    {
      return;
    }

    switch (bufferSPI.status)
    {
      case SPIBufferStatus_Ready:
        send();
        break;

      case SPIBufferStatus_InProcess:
        if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_SPIMASTER_ERRORTIMER))
        {
          cancelWithError();
        }
        break;
    }
  }
}

#endif

