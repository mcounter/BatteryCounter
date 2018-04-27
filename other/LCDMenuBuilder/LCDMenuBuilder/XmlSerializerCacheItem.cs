using System;
using System.Collections.Generic;
using System.Text;

using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    public class XmlSerializerCacheItem
    {
        private string typeName = null;
        private XmlSerializer xmlSerializer = null;

        public XmlSerializerCacheItem(string _typeName, XmlSerializer _xmlSerializer)
        {
            typeName = _typeName;
            xmlSerializer = _xmlSerializer;
        }

        public string TypeName
        {
            get
            {
                return typeName;
            }

            set
            {
                typeName = value;
            }
        }

        public XmlSerializer XmlSerializer
        {
            get
            {
                return xmlSerializer;
            }

            set
            {
                xmlSerializer = value;
            }
        }
    }
}
