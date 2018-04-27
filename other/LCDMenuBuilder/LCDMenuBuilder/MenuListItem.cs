using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    [XmlRoot("MenuListItem")]
    public class MenuListItem : XmlSerializable
    {
        private String menuId = String.Empty;
        private String parentMenuId = String.Empty;
        private bool selectableOption = false;
        private String functionId = String.Empty;
        private String textLineId1 = String.Empty;
        private String textLineId2 = String.Empty;

        [XmlElement("MenuId")]
        public String MenuId
        {
            get
            {
                return menuId;
            }

            set
            {
                menuId = value;
            }
        }

        [XmlElement("ParentMenuId")]
        public String ParentMenuId
        {
            get
            {
                return parentMenuId;
            }

            set
            {
                parentMenuId = value;
            }
        }

        [XmlElement("SelectableOption")]
        public bool SelectableOption
        {
            get
            {
                return selectableOption;
            }

            set
            {
                selectableOption = value;
            }
        }

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

        [XmlElement("TextLine1")]
        public String TextLineId1
        {
            get
            {
                return textLineId1;
            }

            set
            {
                textLineId1 = value;
            }
        }

        [XmlElement("TextLine2")]
        public String TextLineId2
        {
            get
            {
                return textLineId2;
            }

            set
            {
                textLineId2 = value;
            }
        }
    }
}
