#ifndef __COMMONFUNCTIONS_H_
#define __COMMONFUNCTIONS_H_

namespace Functions
{
  namespace Common
  {
    template <class T> T minof(T _value1, T _value2)
    {
      return (_value1 <= _value2) ? _value1 : _value2;
    }

    template <class T> T maxof(T _value1, T _value2)
    {
      return (_value1 >= _value2) ? _value1 : _value2;
    }

    template <class T> T roundDown(T _value, T _base)
    {
      return ((T)(_value / _base)) * _base;
    }

    template <class T> T roundUp(T _value, T _base)
    {
      return (((T)(_value / _base)) * _base) + (((_value % _base) != 0) ? _base : 0);
    }

    template <class T> T cSHL(T _value, unsigned long _shift)
    {
      unsigned char typeSize = sizeof(T) * 8;
      unsigned char shift = (_shift % typeSize);

      if (shift == 0)
      {
          return _value;
      }

      return (_value << shift) ^ (_value >> (typeSize - shift));
    }

    template <class T> T cSHR(T _value, unsigned long _shift)
    {
      unsigned char typeSize = sizeof(T) * 8;
      unsigned char shift = (_shift % typeSize);

      if (shift == 0)
      {
          return _value;
      }

      return (_value >> shift) ^ (_value << (typeSize - shift));
    }

    template <class T> void incWithLimit(T* _value, T _inc)
    {
      T tmpValue = (*_value) + _inc;
      *_value = (tmpValue < (*_value)) ? ((T)(-1)) : tmpValue;
    }

    template <class T> void incWithLimit(T* _value)
    {
      if ((*_value) < ((T)(-1)))
      {
        (*_value)++;
      }
    }

    unsigned char bcd2int(unsigned char _value);
    unsigned char int2bcd(unsigned char _value);
  }
}

#endif


