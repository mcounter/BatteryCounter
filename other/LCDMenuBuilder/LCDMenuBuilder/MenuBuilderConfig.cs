using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    [XmlRoot("MenuBuilderConfig")]
    public class MenuBuilderConfig : XmlSerializable
    {
        private String targetPath = String.Empty;
        private String configFilePath = String.Empty;

        private List<String> langList = new List<String>();
        private Dictionary<String, int> langRef = new Dictionary<String, int>();

        private List<TranslationListItem> translationList = new List<TranslationListItem>();
        private Dictionary<String, int> translationRef = new Dictionary<String, int>();

        private List<FunctionListItem> functionList = new List<FunctionListItem>();
        private Dictionary<String, int> functionRef = new Dictionary<String, int>();

        private List<MenuListItem> menuList = new List<MenuListItem>();
        private Dictionary<String, int> menuRef = new Dictionary<String, int>();
        private Dictionary<String, TreeNode> menuTreeNodeRef = new Dictionary<String, TreeNode>();
        private Dictionary<TreeNode, String> menuTreeNodeIdx = new Dictionary<TreeNode, String>();

        [XmlElement("TargetPath")]
        public String TargetPath
        {
            get
            {
                return targetPath;
            }

            set
            {
                targetPath = value;
            }
        }

        [XmlElement("ConfigFilePath")]
        public String ConfigFilePath
        {
            get
            {
                return configFilePath;
            }

            set
            {
                configFilePath = value;
            }
        }

        [XmlArray("Languages")]
        [XmlArrayItem("Lang")]
        public List<String> LangList
        {
            get
            {
                return langList;
            }

            set
            {
                langList = value;
            }
        }

        [XmlIgnore]
        public Dictionary<String, int> LangRef
        {
            get
            {
                return langRef;
            }

            set
            {
                langRef = value;
            }
        }

        [XmlArray("Translations")]
        [XmlArrayItem("Translation")]
        public List<TranslationListItem> TranslationList
        {
            get
            {
                return translationList;
            }

            set
            {
                translationList = value;
            }
        }

        [XmlIgnore]
        public Dictionary<String, int> TranslationRef
        {
            get
            {
                return translationRef;
            }

            set
            {
                translationRef = value;
            }
        }

        [XmlArray("Functions")]
        [XmlArrayItem("Function")]
        public List<FunctionListItem> FunctionList
        {
            get
            {
                return functionList;
            }

            set
            {
                functionList = value;
            }
        }

        [XmlIgnore]
        public Dictionary<String, int> FunctionRef
        {
            get
            {
                return functionRef;
            }

            set
            {
                functionRef = value;
            }
        }

        [XmlArray("Menus")]
        [XmlArrayItem("Menu")]
        public List<MenuListItem> MenuList
        {
            get
            {
                return menuList;
            }

            set
            {
                menuList = value;
            }
        }

        [XmlIgnore]
        public Dictionary<String, int> MenuRef
        {
            get
            {
                return menuRef;
            }

            set
            {
                menuRef = value;
            }
        }

        [XmlIgnore]
        public Dictionary<String, TreeNode> MenuTreeNodeRef
        {
            get
            {
                return menuTreeNodeRef;
            }

            set
            {
                menuTreeNodeRef = value;
            }
        }

        [XmlIgnore]
        public Dictionary<TreeNode, String> MenuTreeNodeIdx
        {
            get
            {
                return menuTreeNodeIdx;
            }

            set
            {
                menuTreeNodeIdx = value;
            }
        }
    }
}
