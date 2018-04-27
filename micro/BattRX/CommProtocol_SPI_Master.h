#ifndef __COMMPROTOCOL_SPI_MASTER_H_
#define __COMMPROTOCOL_SPI_MASTER_H_

#include "GlobalSpace.h"

namespace CommProtocol_SPI_Master
{
  typedef enum
  {
    SPIResultCodeType_OK = 0x00,
    SPIResultCodeType_Error = 0xFF,
  } TSPIResultCodeType;

  typedef enum
  {
    SPIBufferStatus_None = 0,
    SPIBufferStatus_Ready = 1,
    SPIBufferStatus_InProcess = 2,
    SPIBufferStatus_Processed = 3
  } TSPIBufferStatus;

  typedef struct
  {
    unsigned char length;
    TSPIBufferStatus status;
    TSPIResultCodeType result;

    unsigned char buffer[COMMBUFFERSIZE_SPI_MASTER];
  } TSPIBuffer;

  extern TSPIBuffer bufferSPI;

  void init();
  void enable();
  void disable();
  bool enabled();
  bool ready();

  void run();
}

#endif

