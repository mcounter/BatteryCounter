using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    [XmlRoot("TranslationPair")]
    public class TranslationPair : XmlSerializable
    {
        private String langId = String.Empty;
        private String translationText = String.Empty;

        [XmlElement("Lang")]
        public String LangId
        {
            get
            {
                return langId;
            }

            set
            {
                langId = value;
            }
        }

        [XmlElement("Text")]
        public String TranslationText
        {
            get
            {
                return translationText;
            }

            set
            {
                translationText = value;
            }
        }
    }
}
