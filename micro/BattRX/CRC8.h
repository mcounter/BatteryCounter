#ifndef __CRC8_H_
#define __CRC8_H_

namespace CRC8
{
  typedef unsigned char TCRC8;

  TCRC8 calcCRC8(unsigned char* _data, unsigned char _cnt);
}

#endif

