using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    [XmlRoot("TranslationListItem")]
    public class TranslationListItem : XmlSerializable
    {
        private String translationId = String.Empty;
        private List<TranslationPair> translationText = new List<TranslationPair>();

        [XmlElement("TranslationId")]
        public String TranslationId
        {
            get
            {
                return translationId;
            }

            set
            {
                translationId = value;
            }
        }

        [XmlArray("Variants")]
        [XmlArrayItem("Variant")]
        public List<TranslationPair> TranslationText
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

        [XmlIgnore]
        public String this[String _langId]
        {
            get
            {
                TranslationPair curTransPair = FindLangId(_langId);
                return (curTransPair == null) ? String.Empty : curTransPair.TranslationText;
            }

            set
            {
                TranslationPair curTransPair = FindLangId(_langId);

                if (curTransPair != null)
                {
                    curTransPair.TranslationText = value;
                }
                else
                {
                    translationText.Add(
                        new TranslationPair()
                        {
                            LangId = _langId,
                            TranslationText = value,
                        }
                    );
                }
            }
        }

        public bool ContainsLangId(String _langId)
        {
            return translationText.Exists(
                delegate(TranslationPair _value)
                {
                    return String.Compare(_value.LangId, _langId, true) == 0;
                }
            );
        }

        public TranslationPair FindLangId(String _langId)
        {
            return translationText.Find(
                delegate(TranslationPair _value)
                {
                    return String.Compare(_value.LangId, _langId, true) == 0;
                }
            );
        }
    }
}
