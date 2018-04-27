#ifndef __COMMPROTOCOL_TWI_MASTER_H_
#define __COMMPROTOCOL_TWI_MASTER_H_

#include "GlobalSpace.h"

namespace CommProtocol_TWI_Master
{
  typedef enum
  {
    TWIResultCodeType_OK = 0x00,
    TWIResultCodeType_Error = 0xFF,
  } TTWIResultCodeType;

  typedef enum
  {
    TWIBufferStatus_None = 0,
    TWIBufferStatus_Ready = 1,
    TWIBufferStatus_InProcess = 2,
    TWIBufferStatus_Processed = 3
  } TTWIBufferStatus;

  typedef struct
  {
    unsigned char length;
    TTWIBufferStatus status;
    TTWIResultCodeType result;

    unsigned char buffer[COMMBUFFERSIZE_TWI_MASTER];
  } TTWIBuffer;

  extern TTWIBuffer bufferTWI;

  void init();
  void enable();
  void disable();
  bool enabled();
  bool ready();

  void run();
}

#endif

