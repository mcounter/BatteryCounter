using System;
using System.Collections.Generic;
using System.Text;

namespace LCDMenuBuilder
{
    public class Win2LCDStrEngine
    {
        public static Byte win2LCD(Char _char)
        {
            if (((int)_char >= 0x20) && ((int)_char <= 0x7F))
            {
                return (Byte)_char;
            }
            else
            {
                switch (_char)
                {
                    case 'А': return 0x41;
                    case 'Б': return 0xA0;
                    case 'В': return 0x42;
                    case 'Г': return 0xA1;
                    case 'Д': return 0xE0;
                    case 'Е': return 0x45;
                    case 'Ё': return 0xA2;
                    case 'Ж': return 0xA3;
                    case 'З': return 0xA4;
                    case 'И': return 0xA5;
                    case 'Й': return 0xA6;
                    case 'К': return 0x4B;
                    case 'Л': return 0xA7;
                    case 'М': return 0x4D;
                    case 'Н': return 0x48;
                    case 'О': return 0x4F;
                    case 'П': return 0xA8;
                    case 'Р': return 0x50;
                    case 'С': return 0x43;
                    case 'Т': return 0x54;
                    case 'У': return 0xA9;
                    case 'Ф': return 0xAA;
                    case 'Х': return 0x58;
                    case 'Ц': return 0xE1;
                    case 'Ч': return 0xAB;
                    case 'Ш': return 0xAC;
                    case 'Щ': return 0xE2;
                    case 'Ъ': return 0xAD;
                    case 'Ы': return 0xAE;
                    case 'Ь': return 0x62;
                    case 'Э': return 0xAF;
                    case 'Ю': return 0xB0;
                    case 'Я': return 0xB1;
                    case 'І': return 0x49;
                    case 'Є': return 0x00;
                    case 'Ї': return 0x02;

                    case 'а': return 0x61;
                    case 'б': return 0xB2;
                    case 'в': return 0xB3;
                    case 'г': return 0xB4;
                    case 'д': return 0xE3;
                    case 'е': return 0x65;
                    case 'ё': return 0xB5;
                    case 'ж': return 0xB6;
                    case 'з': return 0xB7;
                    case 'и': return 0xB8;
                    case 'й': return 0xB9;
                    case 'к': return 0xBA;
                    case 'л': return 0xBB;
                    case 'м': return 0xBC;
                    case 'н': return 0xBD;
                    case 'о': return 0x6F;
                    case 'п': return 0xBE;
                    case 'р': return 0x70;
                    case 'с': return 0x63;
                    case 'т': return 0xBF;
                    case 'у': return 0x79;
                    case 'ф': return 0xE4;
                    case 'х': return 0x78;
                    case 'ц': return 0xE5;
                    case 'ч': return 0xC0;
                    case 'ш': return 0xC1;
                    case 'щ': return 0xE6;
                    case 'ъ': return 0xC2;
                    case 'ы': return 0xC3;
                    case 'ь': return 0xC4;
                    case 'э': return 0xC5;
                    case 'ю': return 0xC6;
                    case 'я': return 0xC7;
                    case 'і': return 0x69;
                    case 'є': return 0x01;
                    case 'ї': return 0x03;

                    default: return (Byte)'.';
                }
            }
        }

        public static Byte[] win2LCD(String _str)
        {
            Byte[] buffer = new Byte[_str.Length];

            for (int i = 0; i < _str.Length; i++)
            {
                buffer[i] = win2LCD(_str[i]);
            }

            return buffer;
        }

        public static String byte2Hex(Byte _value)
        {
            StringBuilder resStr = new StringBuilder(2);
            Byte value = _value;

            for (int i = 0; i < 2; i++)
            {
                int curHalfByte = value % 0x10;
                switch (curHalfByte)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        resStr.Insert(0, (Char)(((int)'0') + curHalfByte));
                        break;

                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                        resStr.Insert(0, (Char)(((int)'A') + curHalfByte - 10));
                        break;
                }

                value /= 0x10;
            }

            return resStr.ToString();
        }

        public static String win2LCDStr(String _str)
        {
            StringBuilder curLCDStr = new StringBuilder();

            foreach (Char curChar in _str)
            {
                if (curLCDStr.Length > 0)
                {
                    curLCDStr.Append(", ");
                }

                curLCDStr.Append("0x" + byte2Hex(win2LCD(curChar)));
            }

            return curLCDStr.ToString();
        }
    }
}
