using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    [XmlRoot("FunctionListItem")]
    public class FunctionListItem : XmlSerializable
    {
        private String functionId = String.Empty;
        private String method = String.Empty;
        private int parmId = 0;

        [XmlElement("FunctionId")]
        public String FunctionId
        {
            get
            {
                return functionId;
            }

            set
            {
                functionId = value;
            }
        }

        [XmlElement("Method")]
        public String Method
        {
            get
            {
                return method;
            }

            set
            {
                method = value;
            }
        }

        [XmlElement("ParmId")]
        public int ParmId
        {
            get
            {
                return parmId;
            }

            set
            {
                parmId = value;
            }
        }
    }
}
