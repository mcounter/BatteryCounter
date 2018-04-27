using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;

namespace LCDMenuBuilder
{
    public partial class frmMain : Form
    {
        private String configStartPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "menu.xml");
        private MenuBuilderConfig menuConfig = new MenuBuilderConfig();

        public frmMain()
        {
            InitializeComponent();

            reload();
        }

        private void refreshLangList()
        {
            menuConfig.LangRef = new Dictionary<String, int>();
            edtTextsLangList.Items.Clear();

            for (int i = 0; i < menuConfig.LangList.Count; i++)
            {
                menuConfig.LangRef.Add(menuConfig.LangList[i], i);
                edtTextsLangList.Items.Add(menuConfig.LangList[i]);
            }

            edtTextsLangList.SelectedIndex = -1;
            selectLang();
        }

        private void refreshTranslationList()
        {
            menuConfig.TranslationRef = new Dictionary<String, int>();
            edtTextsList.Items.Clear();

            for (int i = 0; i < menuConfig.TranslationList.Count; i++)
            {
                menuConfig.TranslationRef.Add(menuConfig.TranslationList[i].TranslationId, i);
                edtTextsList.Items.Add(menuConfig.TranslationList[i].TranslationId);
            }

            edtTextsList.SelectedIndex = -1;
            selectLang();
        }

        private void refreshFunctionList()
        {
            menuConfig.FunctionRef = new Dictionary<String, int>();
            edtFunctionsList.Items.Clear();

            for (int i = 0; i < menuConfig.FunctionList.Count; i++)
            {
                menuConfig.FunctionRef.Add(menuConfig.FunctionList[i].FunctionId, i);
                edtFunctionsList.Items.Add(menuConfig.FunctionList[i].FunctionId);
            }

            edtFunctionsList.SelectedIndex = -1;
            selectFunc();
        }

        private void refreshMenuList()
        {
            menuConfig.MenuRef = new Dictionary<String, int>();
            menuConfig.MenuTreeNodeIdx = new Dictionary<TreeNode, String>();
            menuConfig.MenuTreeNodeRef = new Dictionary<String, TreeNode>();

            edtMenuTree.Nodes.Clear();

            for (int i = 0; i < menuConfig.MenuList.Count; i++)
            {
                TreeNode curTreeNode = null;
                if (String.IsNullOrEmpty(menuConfig.MenuList[i].ParentMenuId))
                {
                    curTreeNode = edtMenuTree.Nodes.Add(menuConfig.MenuList[i].MenuId);
                }
                else
                {
                    if (menuConfig.MenuTreeNodeRef.ContainsKey(menuConfig.MenuList[i].ParentMenuId))
                    {
                        curTreeNode = menuConfig.MenuTreeNodeRef[menuConfig.MenuList[i].ParentMenuId];
                        if (curTreeNode != null)
                        {
                            curTreeNode = curTreeNode.Nodes.Add(menuConfig.MenuList[i].MenuId);
                        }
                    }
                }

                if (curTreeNode != null)
                {
                    menuConfig.MenuRef.Add(menuConfig.MenuList[i].MenuId, i);

                    menuConfig.MenuTreeNodeIdx.Add(curTreeNode, menuConfig.MenuList[i].MenuId);
                    menuConfig.MenuTreeNodeRef.Add(menuConfig.MenuList[i].MenuId, curTreeNode);
                }
            }

            int idx = 0;
            bool isUpdated = false;
            while (idx < menuConfig.MenuList.Count)
            {
                if (!menuConfig.MenuRef.ContainsKey(menuConfig.MenuList[idx].MenuId))
                {
                    menuConfig.MenuList.RemoveAt(idx);
                    isUpdated = true;
                }
                else
                {
                    idx++;
                }
            }

            if (isUpdated)
            {
                refreshMenuList();
            }
            else
            {
                edtMenuTree.ExpandAll();
                edtMenuTree.SelectedNode = null;
                edtMenuTree.Select();

                updateMenuCaptions();
                selectMenu();
            }
        }

        private void selectLang()
        {
            int curSelLangIdx = edtTextsLangList.SelectedIndex;
            String curSelectedLangId = String.Empty;
            if (curSelLangIdx < 0)
            {
                edtLangSelected.Text = "<None>";
                curSelectedLangId = String.Empty;
            }
            else
            {
                edtLangSelected.Text = menuConfig.LangList[curSelLangIdx];
                curSelectedLangId = menuConfig.LangList[curSelLangIdx];
            }

            int curSelTextIdx = edtTextsList.SelectedIndex;
            if (curSelTextIdx < 0)
            {
                edtTextId.Text = String.Empty;
            }
            else
            {
                edtTextId.Text = menuConfig.TranslationList[curSelTextIdx].TranslationId;
            }
             
            if ((curSelTextIdx >= 0) && (curSelLangIdx >= 0))
            {
                edtTextDesc.Text = menuConfig.TranslationList[curSelTextIdx].ContainsLangId(menuConfig.LangList[curSelLangIdx]) ? menuConfig.TranslationList[curSelTextIdx][menuConfig.LangList[curSelLangIdx]] : String.Empty;
            }
            else
            {
                edtTextDesc.Text = String.Empty;
            }

            edtTextDescMod.Visible = false;
            edtTextIdMod.Visible = false;

            edtMenuTextLine1.Items.Clear();
            edtMenuTextLine2.Items.Clear();

            foreach (TranslationListItem curTranslationItem in menuConfig.TranslationList)
            {
                String curTranslationText = curTranslationItem[curSelectedLangId];
                if (String.IsNullOrEmpty(curTranslationText))
                {
                    curTranslationText = String.Empty;
                }

                edtMenuTextLine1.Items.Add(String.Format("{0} [{1}]", curTranslationItem.TranslationId, curTranslationText));
                edtMenuTextLine2.Items.Add(String.Format("{0} [{1}]", curTranslationItem.TranslationId, curTranslationText));
            }

            updateMenuCaptions();
            selectMenu();
        }

        private void selectFunc()
        {
            int curSelFuncIdx = edtFunctionsList.SelectedIndex;
            if (curSelFuncIdx < 0)
            {
                edtFunctionId.Text = String.Empty;
                edtFunctionMethod.Text = String.Empty;
                edtFunctionParm.Value = 0;
            }
            else
            {
                edtFunctionId.Text = menuConfig.FunctionList[curSelFuncIdx].FunctionId;
                edtFunctionMethod.Text = menuConfig.FunctionList[curSelFuncIdx].Method;
                edtFunctionParm.Value = menuConfig.FunctionList[curSelFuncIdx].ParmId;
            }

            edtFunctionIdMod.Visible = false;
            edtFunctionMethodMod.Visible = false;
            edtFunctionParmMod.Visible = false;

            edtMenuFunction.Items.Clear();

            foreach (FunctionListItem curFunctionItem in menuConfig.FunctionList)
            {
                edtMenuFunction.Items.Add(curFunctionItem.FunctionId);
            }

            selectMenu();
        }

        private void updateTreeNodeCaption(TreeNode _node)
        {
            if (_node == null)
            {
                return;
            }

            String curMenuId = menuConfig.MenuTreeNodeIdx.ContainsKey(_node) ? menuConfig.MenuTreeNodeIdx[_node] : String.Empty;
            if (String.IsNullOrEmpty(curMenuId))
            {
                return;
            }

            MenuListItem curMenuItem = menuConfig.MenuList[menuConfig.MenuRef[curMenuId]];
            String curLang = (edtTextsLangList.SelectedIndex >= 0) ? menuConfig.LangList[edtTextsLangList.SelectedIndex] : String.Empty;

            if ((curMenuItem == null) || String.IsNullOrEmpty(curLang))
            {
                _node.Text = curMenuId;
            }
            else
            {
                String textLine1 = ((!String.IsNullOrEmpty(curMenuItem.TextLineId1)) && menuConfig.TranslationRef.ContainsKey(curMenuItem.TextLineId1)) ? menuConfig.TranslationList[menuConfig.TranslationRef[curMenuItem.TextLineId1]][curLang] : String.Empty;
                String textLine2 = ((!String.IsNullOrEmpty(curMenuItem.TextLineId2)) && menuConfig.TranslationRef.ContainsKey(curMenuItem.TextLineId2)) ? menuConfig.TranslationList[menuConfig.TranslationRef[curMenuItem.TextLineId2]][curLang] : String.Empty;

                if ((!String.IsNullOrEmpty(textLine1)) && (!String.IsNullOrEmpty(textLine2)))
                {
                    _node.Text = String.Format("{0} {1}", textLine1, textLine2);
                }
                else if (!String.IsNullOrEmpty(textLine1))
                {
                    _node.Text = textLine1;
                }
                else if (!String.IsNullOrEmpty(textLine2))
                {
                    _node.Text = textLine2;
                }
                else
                {
                    _node.Text = curMenuId;
                }
            }
        }

        private void updateMenuCaptions()
        {
            foreach (TreeNode curTreeNode in menuConfig.MenuTreeNodeIdx.Keys)
            {
                updateTreeNodeCaption(curTreeNode);
            }
        }

        private void selectMenu()
        {
            TreeNode selTreeNode = edtMenuTree.SelectedNode;
            MenuListItem curMenuItem = ((selTreeNode != null) && (menuConfig.MenuTreeNodeIdx.ContainsKey(selTreeNode))) ? menuConfig.MenuList[menuConfig.MenuRef[menuConfig.MenuTreeNodeIdx[selTreeNode]]] : null;

            if (curMenuItem == null)
            {
                edtMenuId.Text = String.Empty;
                edtMenuFunction.SelectedIndex = -1;
                edtMenuFunction.Enabled = false;
                edtMenuTextLine1.SelectedIndex = -1;
                edtMenuTextLine2.SelectedIndex = -1;
                edtSelectableOption.Checked = false;
                edtSelectableOption.Enabled = false;
            }
            else
            {
                edtMenuId.Text = curMenuItem.MenuId;
                edtSelectableOption.Checked = curMenuItem.SelectableOption;

                if (String.IsNullOrEmpty(curMenuItem.ParentMenuId))
                {
                    edtSelectableOption.Checked = false;
                    edtSelectableOption.Enabled = false;
                }
                else
                {
                    edtSelectableOption.Enabled = true;
                }

                if (String.IsNullOrEmpty(curMenuItem.ParentMenuId) || (selTreeNode.Nodes.Count <= 0) || edtSelectableOption.Checked)
                {
                    edtMenuFunction.Enabled = true;
                    edtMenuFunction.SelectedIndex = ((!String.IsNullOrEmpty(curMenuItem.FunctionId)) && (menuConfig.FunctionRef.ContainsKey(curMenuItem.FunctionId))) ? menuConfig.FunctionRef[curMenuItem.FunctionId] : -1;
                }
                else
                {
                    edtMenuFunction.Enabled = false;
                    edtMenuFunction.SelectedIndex = -1;
                }

                edtMenuTextLine1.SelectedIndex = ((!String.IsNullOrEmpty(curMenuItem.TextLineId1)) && (menuConfig.TranslationRef.ContainsKey(curMenuItem.TextLineId1))) ? menuConfig.TranslationRef[curMenuItem.TextLineId1] : -1;
                edtMenuTextLine2.SelectedIndex = ((!String.IsNullOrEmpty(curMenuItem.TextLineId2)) && (menuConfig.TranslationRef.ContainsKey(curMenuItem.TextLineId2))) ? menuConfig.TranslationRef[curMenuItem.TextLineId2] : -1;
            }

            edtMenuIdMod.Visible = false;
            edtMenuFunctionMod.Visible = false;
            edtMenuTextLine1Mod.Visible = false;
            edtMenuTextLine2Mod.Visible = false;
        }

        private void refreshAll()
        {
            refreshLangList();
            refreshTranslationList();
            refreshFunctionList();
            refreshMenuList();
        }

        private void reload()
        {
            if (File.Exists(configStartPath))
            {
                menuConfig = (MenuBuilderConfig)XmlSerializable.deserialize(configStartPath, typeof(MenuBuilderConfig));
            }
            else
            {
                menuConfig = new MenuBuilderConfig();
            }

            if (!String.IsNullOrEmpty(menuConfig.ConfigFilePath))
            {
                edtConfigPath.Text = menuConfig.ConfigFilePath;

                if (File.Exists(menuConfig.ConfigFilePath))
                {
                    menuConfig = (MenuBuilderConfig)XmlSerializable.deserialize(menuConfig.ConfigFilePath, typeof(MenuBuilderConfig));
                }
                else
                {
                    menuConfig = new MenuBuilderConfig();
                }
            }

            edtTargetDir.Text = menuConfig.TargetPath;

            refreshAll();

            if (edtTextsList.Items.Count > 0)
            {
                edtTextsList.SelectedIndex = 0;
            }

            if (edtTextsLangList.Items.Count > 0)
            {
                edtTextsLangList.SelectedIndex = 0;
            }

            if (edtFunctionsList.Items.Count > 0)
            {
                edtFunctionsList.SelectedIndex = 0;
            }

            if (edtMenuTree.Nodes.Count  > 0)
            {
                edtMenuTree.SelectedNode = edtMenuTree.Nodes[0];
                selectMenu();
            }
        }

        private void save()
        {
            menuConfig.TargetPath = edtTargetDir.Text;
            if (String.IsNullOrEmpty(edtConfigPath.Text))
            {
                menuConfig.serialize(configStartPath);
            }
            else
            {
                menuConfig.serialize(edtConfigPath.Text);

                new MenuBuilderConfig()
                {
                    ConfigFilePath = edtConfigPath.Text,
                }.serialize(configStartPath);
            }
        }

        private bool checkID(String _value)
        {
            foreach (Char curChar in _value)
            {
                if (!(((curChar >= 'a') && (curChar <= 'z')) ||
                     ((curChar >= 'A') && (curChar <= 'Z')) ||
                     ((curChar >= '0') && (curChar <= '9')) ||
                     (curChar == '_')))
                {
                    MessageBox.Show("ID can contain only letters, numbers and underscore (_).", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }

            return true;
        }

        private void btnLoadConfig_Click(object sender, EventArgs e)
        {
            reload();
        }

        private void btnTextsLngAdd_Click(object sender, EventArgs e)
        {
            String curLangId = edtTextsLng.Text.ToUpper();

            if (String.IsNullOrEmpty(curLangId))
            {
                MessageBox.Show("Language ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!checkID(curLangId))
            {
                return;
            }

            if (menuConfig.LangRef.ContainsKey(curLangId))
            {
                MessageBox.Show("Language ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            menuConfig.LangList.Add(curLangId);
            refreshLangList();
            edtTextsLangList.SelectedIndex = menuConfig.LangRef[curLangId];
            edtTextsLng.Text = String.Empty;
        }

        private void btnTextsLngRemove_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtTextsLangList.SelectedIndex;
            if (curSelIdx < 0)
            {
                return;
            }

            String prevLangId = menuConfig.LangList[curSelIdx];

            if (MessageBox.Show(String.Format("Do you really want remove Language '{0}' ?", prevLangId), "Removing", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != System.Windows.Forms.DialogResult.Yes)
            {
                return;
            }

            menuConfig.LangList.RemoveAt(curSelIdx);
            refreshLangList();
            if (curSelIdx >= edtTextsLangList.Items.Count)
            {
                edtTextsLangList.SelectedIndex = edtTextsLangList.Items.Count - 1;
            }
            else
            {
                edtTextsLangList.SelectedIndex = curSelIdx;
            }
        }

        private void edtTextsLangList_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectLang();
        }

        private void btnTextsAdd_Click(object sender, EventArgs e)
        {
            String curTextConst = "TEXTCONST".ToUpper();
            int curTextConstIdx = 1;

            while (menuConfig.TranslationRef.ContainsKey(curTextConst + curTextConstIdx.ToString()))
            {
                curTextConstIdx++;
            }

            curTextConst = curTextConst + curTextConstIdx.ToString();

            menuConfig.TranslationList.Add(
                new TranslationListItem()
                {
                    TranslationId = curTextConst,
                }
            );

            refreshTranslationList();
            edtTextsList.SelectedIndex = menuConfig.TranslationRef[curTextConst];
        }

        private void edtTextsList_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectLang();
        }

        private void btnTextsRemove_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtTextsList.SelectedIndex;
            if (curSelIdx < 0)
            {
                return;
            }

            String prevTextId = menuConfig.TranslationList[curSelIdx].TranslationId;

            if (MessageBox.Show(String.Format("Do you really want remove Translation Id '{0}' ?", prevTextId), "Removing", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != System.Windows.Forms.DialogResult.Yes)
            {
                return;
            }

            if (!String.IsNullOrEmpty(prevTextId))
            {
                foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                {
                    if (String.Compare(curMenuItem.TextLineId1, prevTextId, true) == 0)
                    {
                        curMenuItem.TextLineId1 = String.Empty;
                    }

                    if (String.Compare(curMenuItem.TextLineId2, prevTextId, true) == 0)
                    {
                        curMenuItem.TextLineId2 = String.Empty;
                    }
                }
            }

            menuConfig.TranslationList.RemoveAt(curSelIdx);
            refreshTranslationList();
            if (curSelIdx >= edtTextsList.Items.Count)
            {
                edtTextsList.SelectedIndex = edtTextsList.Items.Count - 1;
            }
            else
            {
                edtTextsList.SelectedIndex = curSelIdx;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtTextsList.SelectedIndex;
            if (curSelIdx <= 0)
            {
                return;
            }

            TranslationListItem curListItem = menuConfig.TranslationList[curSelIdx];
            menuConfig.TranslationList.RemoveAt(edtTextsList.SelectedIndex);

            curSelIdx--;
            menuConfig.TranslationList.Insert(curSelIdx, curListItem);
            refreshTranslationList();
            edtTextsList.SelectedIndex = curSelIdx;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtTextsList.SelectedIndex;
            if ((curSelIdx < 0) || (curSelIdx >= (edtTextsList.Items.Count - 1)))
            {
                return;
            }

            TranslationListItem curListItem = menuConfig.TranslationList[curSelIdx];
            menuConfig.TranslationList.RemoveAt(edtTextsList.SelectedIndex);

            curSelIdx++;
            menuConfig.TranslationList.Insert(curSelIdx, curListItem);
            refreshTranslationList();
            edtTextsList.SelectedIndex = curSelIdx;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int curSelTextIdx = edtTextsList.SelectedIndex;
            if (curSelTextIdx >= 0)
            {
                String curTextId = edtTextId.Text.ToUpper();

                if (String.IsNullOrEmpty(curTextId))
                {
                    MessageBox.Show("Translation ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (!checkID(curTextId))
                {
                    return;
                }

                if (menuConfig.TranslationRef.ContainsKey(curTextId) && (curTextId != menuConfig.TranslationList[curSelTextIdx].TranslationId))
                {
                    MessageBox.Show("Translation ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                String prevTextId = menuConfig.TranslationList[curSelTextIdx].TranslationId;
                menuConfig.TranslationList[curSelTextIdx].TranslationId = curTextId;

                if ((!String.IsNullOrEmpty(prevTextId)) && (prevTextId != curTextId))
                {
                    foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                    {
                        if (String.Compare(curMenuItem.TextLineId1, prevTextId, true) == 0)
                        {
                            curMenuItem.TextLineId1 = curTextId;
                        }

                        if (String.Compare(curMenuItem.TextLineId2, prevTextId, true) == 0)
                        {
                            curMenuItem.TextLineId2 = curTextId;
                        }
                    }
                }

                int curSelLangIdx = edtTextsLangList.SelectedIndex;

                if (curSelLangIdx >= 0)
                {
                    menuConfig.TranslationList[curSelTextIdx][menuConfig.LangList[curSelLangIdx]] = edtTextDesc.Text;
                }

                refreshTranslationList();
                edtTextsList.SelectedIndex = curSelTextIdx;
                if (curSelLangIdx >= 0)
                {
                    edtTextsLangList.SelectedIndex = curSelLangIdx;
                }
            }
        }

        private void btnSaveConfig_Click(object sender, EventArgs e)
        {
            save();
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            save();
        }

        private void edtTextsLng_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (Char)Keys.Enter)
            {
                btnTextsLngAdd_Click(sender, null);
            }
        }

        private void edtTextDesc_TextChanged(object sender, EventArgs e)
        {
            edtTextDescMod.Visible = true;
            edtTextDescDigits.Text = edtTextDesc.Text.Length.ToString();
        }

        private void edtTextId_TextChanged(object sender, EventArgs e)
        {
            edtTextIdMod.Visible = true;
        }

        private void edtFunctionsList_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectFunc();
        }

        private void btnFunctionUp_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtFunctionsList.SelectedIndex;
            if (curSelIdx <= 0)
            {
                return;
            }

            FunctionListItem curListItem = menuConfig.FunctionList[curSelIdx];
            menuConfig.FunctionList.RemoveAt(edtFunctionsList.SelectedIndex);

            curSelIdx--;
            menuConfig.FunctionList.Insert(curSelIdx, curListItem);
            refreshFunctionList();
            edtFunctionsList.SelectedIndex = curSelIdx;
        }

        private void btnFunctionDown_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtFunctionsList.SelectedIndex;
            if ((curSelIdx < 0) || (curSelIdx >= (edtFunctionsList.Items.Count - 1)))
            {
                return;
            }

            FunctionListItem curListItem = menuConfig.FunctionList[curSelIdx];
            menuConfig.FunctionList.RemoveAt(edtFunctionsList.SelectedIndex);

            curSelIdx++;
            menuConfig.FunctionList.Insert(curSelIdx, curListItem);
            refreshFunctionList();
            edtFunctionsList.SelectedIndex = curSelIdx;
        }

        private void btnFunctionAdd_Click(object sender, EventArgs e)
        {
            String curFuncConst = "FUNC".ToUpper();
            int curFuncConstIdx = 1;

            while (menuConfig.FunctionRef.ContainsKey(curFuncConst + curFuncConstIdx.ToString()))
            {
                curFuncConstIdx++;
            }

            curFuncConst = curFuncConst + curFuncConstIdx.ToString();

            menuConfig.FunctionList.Add(
                new FunctionListItem()
                {
                    FunctionId = curFuncConst,
                }
            );

            refreshFunctionList();
            edtFunctionsList.SelectedIndex = menuConfig.FunctionRef[curFuncConst];
        }

        private void btnFunctionRemove_Click(object sender, EventArgs e)
        {
            int curSelIdx = edtFunctionsList.SelectedIndex;
            if (curSelIdx < 0)
            {
                return;
            }

            String prevFuncId = menuConfig.FunctionList[curSelIdx].FunctionId;

            if (MessageBox.Show(String.Format("Do you really want remove Function Id '{0}' ?", prevFuncId), "Removing", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != System.Windows.Forms.DialogResult.Yes)
            {
                return;
            }

            if (!String.IsNullOrEmpty(prevFuncId))
            {
                foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                {
                    if (String.Compare(curMenuItem.FunctionId, prevFuncId, true) == 0)
                    {
                        curMenuItem.FunctionId = String.Empty;
                    }
                }
            }

            menuConfig.FunctionList.RemoveAt(curSelIdx);
            refreshFunctionList();
            if (curSelIdx >= edtFunctionsList.Items.Count)
            {
                edtFunctionsList.SelectedIndex = edtFunctionsList.Items.Count - 1;
            }
            else
            {
                edtFunctionsList.SelectedIndex = curSelIdx;
            }
        }

        private void btnFunctionSave_Click(object sender, EventArgs e)
        {
            int curSelFuncIdx = edtFunctionsList.SelectedIndex;
            if (curSelFuncIdx >= 0)
            {
                String curFuncId = edtFunctionId.Text.ToUpper();

                if (String.IsNullOrEmpty(curFuncId))
                {
                    MessageBox.Show("Function ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (!checkID(curFuncId))
                {
                    return;
                }

                if (menuConfig.FunctionRef.ContainsKey(curFuncId) && (curFuncId != menuConfig.FunctionList[curSelFuncIdx].FunctionId))
                {
                    MessageBox.Show("Function ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                String prevFuncId = menuConfig.FunctionList[curSelFuncIdx].FunctionId;
                menuConfig.FunctionList[curSelFuncIdx].FunctionId = curFuncId;
                menuConfig.FunctionList[curSelFuncIdx].Method = edtFunctionMethod.Text;
                menuConfig.FunctionList[curSelFuncIdx].ParmId = (int)edtFunctionParm.Value;

                if ((!String.IsNullOrEmpty(prevFuncId)) && (prevFuncId != curFuncId))
                {
                    foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                    {
                        if (String.Compare(curMenuItem.FunctionId, prevFuncId, true) == 0)
                        {
                            curMenuItem.FunctionId = curFuncId;
                        }
                    }
                }

                refreshFunctionList();
                edtFunctionsList.SelectedIndex = curSelFuncIdx;
            }
        }

        private void edtFunctionId_TextChanged(object sender, EventArgs e)
        {
            edtFunctionIdMod.Visible = true;
        }

        private void edtFunctionMethod_TextChanged(object sender, EventArgs e)
        {
            edtFunctionMethodMod.Visible = true;
        }

        private void edtFunctionParm_ValueChanged(object sender, EventArgs e)
        {
            edtFunctionParmMod.Visible = true;
        }

        private void btnMenuAdd_Click(object sender, EventArgs e)
        {
            String curMenuConst = "MENU".ToUpper();
            int curMenuConstIdx = 1;

            while (menuConfig.MenuRef.ContainsKey(curMenuConst + curMenuConstIdx.ToString()))
            {
                curMenuConstIdx++;
            }

            curMenuConst = curMenuConst + curMenuConstIdx.ToString();

            String curParentMenuId = (edtMenuTree.SelectedNode != null) ? menuConfig.MenuTreeNodeIdx[edtMenuTree.SelectedNode] : String.Empty;

            menuConfig.MenuList.Add(
                new MenuListItem()
                {
                    MenuId = curMenuConst,
                    ParentMenuId = curParentMenuId,
                }
            );

            menuConfig.MenuRef.Add(curMenuConst, menuConfig.MenuList.Count - 1);

            TreeNode curTreeNode = null;

            if (edtMenuTree.SelectedNode != null)
            {
                curTreeNode = edtMenuTree.SelectedNode.Nodes.Add(curMenuConst);
            }
            else
            {
                curTreeNode = edtMenuTree.Nodes.Add(curMenuConst);
            }

            if (curTreeNode != null)
            {
                menuConfig.MenuTreeNodeIdx.Add(curTreeNode, curMenuConst);
                menuConfig.MenuTreeNodeRef.Add(curMenuConst, curTreeNode);
            }

            edtMenuTree.SelectedNode = curTreeNode;
            edtMenuTree.Select();
        }

        private void btnMenuRemove_Click(object sender, EventArgs e)
        {
            if (edtMenuTree.SelectedNode == null)
            {
                return;
            }

            String curMenuId = menuConfig.MenuTreeNodeIdx.ContainsKey(edtMenuTree.SelectedNode) ? menuConfig.MenuTreeNodeIdx[edtMenuTree.SelectedNode] : String.Empty;

            if (MessageBox.Show(String.Format("Do you really want remove Menu Id '{0}' with all sub-menus?", curMenuId), "Removing", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != System.Windows.Forms.DialogResult.Yes)
            {
                return;
            }

            if (curMenuId != null)
            {
                menuConfig.MenuList.RemoveAt(menuConfig.MenuRef[curMenuId]);
            }

            String curParentMenuId = ((edtMenuTree.SelectedNode.Parent != null) &&
                                      (menuConfig.MenuTreeNodeIdx.ContainsKey(edtMenuTree.SelectedNode.Parent))) ?
                                      menuConfig.MenuTreeNodeIdx[edtMenuTree.SelectedNode.Parent] : String.Empty;

            edtMenuTree.SelectedNode.Remove();

            refreshMenuList();

            edtMenuTree.SelectedNode = ((!String.IsNullOrEmpty(curParentMenuId)) &&
                                        (menuConfig.MenuTreeNodeRef.ContainsKey(curParentMenuId))) ?
                                        menuConfig.MenuTreeNodeRef[curParentMenuId] : null;
            edtMenuTree.Select();
        }

        private void edtMenuTree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            selectMenu();
        }

        private void edtMenuId_TextChanged(object sender, EventArgs e)
        {
            edtMenuIdMod.Visible = true;
        }

        private void edtMenuFunction_TextChanged(object sender, EventArgs e)
        {
            edtMenuFunctionMod.Visible = true;
        }

        private void edtMenuFunction_SelectedIndexChanged(object sender, EventArgs e)
        {
            edtMenuFunctionMod.Visible = true;
        }

        private void edtMenuTextLine1_TextChanged(object sender, EventArgs e)
        {
            edtMenuTextLine1Mod.Visible = true;
        }

        private void edtMenuTextLine1_SelectedIndexChanged(object sender, EventArgs e)
        {
            edtMenuTextLine1Mod.Visible = true;
        }

        private void edtMenuTextLine2_TextChanged(object sender, EventArgs e)
        {
            edtMenuTextLine2Mod.Visible = true;
        }

        private void edtMenuTextLine2_SelectedIndexChanged(object sender, EventArgs e)
        {
            edtMenuTextLine2Mod.Visible = true;
        }

        private void btnMenuSave_Click(object sender, EventArgs e)
        {
            if (edtMenuTree.SelectedNode == null)
            {
                return;
            }

            String curMenuId = edtMenuId.Text.ToUpper();
            String curPrevMenuId = menuConfig.MenuTreeNodeIdx.ContainsKey(edtMenuTree.SelectedNode) ? menuConfig.MenuTreeNodeIdx[edtMenuTree.SelectedNode] : String.Empty;

            if (String.IsNullOrEmpty(curPrevMenuId))
            {
                return;
            }

            if (String.IsNullOrEmpty(curMenuId))
            {
                MessageBox.Show("Menu ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!checkID(curMenuId))
            {
                return;
            }

            if (menuConfig.MenuRef.ContainsKey(curMenuId) && (curMenuId != curPrevMenuId))
            {
                MessageBox.Show("Menu ID must be specified and unique.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            int prevMenuRefIdx = menuConfig.MenuRef[curPrevMenuId];

            menuConfig.MenuList[prevMenuRefIdx].MenuId = curMenuId;
            menuConfig.MenuList[prevMenuRefIdx].SelectableOption = edtSelectableOption.Checked;
            menuConfig.MenuList[prevMenuRefIdx].FunctionId = (edtMenuFunction.SelectedIndex >= 0) ? menuConfig.FunctionList[edtMenuFunction.SelectedIndex].FunctionId : String.Empty;
            menuConfig.MenuList[prevMenuRefIdx].TextLineId1 = (edtMenuTextLine1.SelectedIndex >= 0) ? menuConfig.TranslationList[edtMenuTextLine1.SelectedIndex].TranslationId : String.Empty;
            menuConfig.MenuList[prevMenuRefIdx].TextLineId2 = (edtMenuTextLine2.SelectedIndex >= 0) ? menuConfig.TranslationList[edtMenuTextLine2.SelectedIndex].TranslationId : String.Empty;

            if (curPrevMenuId != curMenuId)
            {
                menuConfig.MenuRef.Remove(curPrevMenuId);
                menuConfig.MenuRef.Add(curMenuId, prevMenuRefIdx);

                if (menuConfig.MenuTreeNodeRef.ContainsKey(curPrevMenuId))
                {
                    TreeNode curTreeNode = menuConfig.MenuTreeNodeRef[curPrevMenuId];
                    menuConfig.MenuTreeNodeRef.Remove(curPrevMenuId);
                    menuConfig.MenuTreeNodeRef.Add(curMenuId, curTreeNode);

                    if (menuConfig.MenuTreeNodeIdx.ContainsKey(curTreeNode))
                    {
                        menuConfig.MenuTreeNodeIdx[curTreeNode] = curMenuId;
                    }
                }

                foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                {
                    if (String.Compare(curMenuItem.ParentMenuId, curPrevMenuId, true) == 0)
                    {
                        curMenuItem.ParentMenuId = curMenuId;
                    }
                }
            }

            if (menuConfig.MenuTreeNodeRef.ContainsKey(curMenuId))
            {
                updateTreeNodeCaption(menuConfig.MenuTreeNodeRef[curMenuId]);
            }

            selectMenu();
        }

        private void edtSelectableOption_CheckedChanged(object sender, EventArgs e)
        {
            edtMenuIdMod.Visible = false;
        }

        private void buildCodeFiles()
        {
            StringBuilder sbUserInterfaceLangHdr = new StringBuilder();
            sbUserInterfaceLangHdr.AppendLine("#ifndef __USERINTERFACELANG_H_");
            sbUserInterfaceLangHdr.AppendLine("#define __USERINTERFACELANG_H_");
            sbUserInterfaceLangHdr.AppendLine();

            const String translationCodePrefix = "USER_TEXT_CONST_";
            int maxStrLng = 0;
            for (int i = 0; i < menuConfig.TranslationList.Count; i++)
            {
                int curStrLng = translationCodePrefix.Length + menuConfig.TranslationList[i].TranslationId.Length;
                if (curStrLng > maxStrLng)
                {
                    maxStrLng = curStrLng;
                }
            }

            maxStrLng = ((int)((maxStrLng + 10) / 2)) * 2;

            for (int i = 0; i < menuConfig.TranslationList.Count; i++)
            {
                sbUserInterfaceLangHdr.AppendLine(
                    String.Format("#define {0}({1})",
                        (translationCodePrefix + menuConfig.TranslationList[i].TranslationId).PadRight(maxStrLng, ' '),
                        i));
            }

            sbUserInterfaceLangHdr.AppendLine();
            sbUserInterfaceLangHdr.AppendLine("namespace UserInterface");
            sbUserInterfaceLangHdr.AppendLine("{");
            sbUserInterfaceLangHdr.AppendLine("  unsigned char __generic * getString(unsigned short _strId);");
            sbUserInterfaceLangHdr.AppendLine("}");

            sbUserInterfaceLangHdr.AppendLine("#endif");

            File.WriteAllText(Path.Combine(menuConfig.TargetPath, "UserInterfaceLang.h"), sbUserInterfaceLangHdr.ToString(), Encoding.Default);

            StringBuilder sbUserInterfaceLangCpp = new StringBuilder();
            sbUserInterfaceLangCpp.AppendLine("#ifndef __USERINTERFACELANG_CPP_");
            sbUserInterfaceLangCpp.AppendLine("#define __USERINTERFACELANG_CPP_");
            sbUserInterfaceLangCpp.AppendLine();
            sbUserInterfaceLangCpp.AppendLine("#include \"UserInterfaceLang.h\"");

            foreach (String curLangId in menuConfig.LangList)
            {
                sbUserInterfaceLangCpp.AppendLine(String.Format("#include \"UserInterfaceLang_{0}.h\"", curLangId));
            }

            sbUserInterfaceLangCpp.AppendLine();
            sbUserInterfaceLangCpp.AppendLine("#include \"GlobalSpace.h\"");
            sbUserInterfaceLangCpp.AppendLine();
            sbUserInterfaceLangCpp.AppendLine("namespace UserInterface");
            sbUserInterfaceLangCpp.AppendLine("{");
            sbUserInterfaceLangCpp.AppendLine("  unsigned char __generic* getString(unsigned short _strId)");
            sbUserInterfaceLangCpp.AppendLine("  {");
            sbUserInterfaceLangCpp.AppendLine("    switch (GLOBAL::DeviceProfile::UserInterfaceSetup.language)");
            sbUserInterfaceLangCpp.AppendLine("    {");

            foreach (String curLangId in menuConfig.LangList)
            {
                sbUserInterfaceLangCpp.AppendLine(String.Format("      case GLOBAL::DeviceProfile::UserInterfaceLanguage_{0}:", curLangId));
                sbUserInterfaceLangCpp.AppendLine(String.Format("        return (unsigned char __generic*)(textStrings_{0} + textReference_{0}[_strId]);", curLangId));
                sbUserInterfaceLangCpp.AppendLine();
            }

            sbUserInterfaceLangCpp.AppendLine("    }");
            sbUserInterfaceLangCpp.AppendLine();
            sbUserInterfaceLangCpp.AppendLine("    return 0;");
            sbUserInterfaceLangCpp.AppendLine("  }");
            sbUserInterfaceLangCpp.AppendLine("}");
            sbUserInterfaceLangCpp.AppendLine();
            sbUserInterfaceLangCpp.AppendLine("#endif");

            File.WriteAllText(Path.Combine(menuConfig.TargetPath, "UserInterfaceLang.cpp"), sbUserInterfaceLangCpp.ToString(), Encoding.Default);

            foreach (String curLangId in menuConfig.LangList)
            {
                StringBuilder sbUserInterfaceLangTranslationHdr = new StringBuilder();
                sbUserInterfaceLangTranslationHdr.AppendLine("#ifndef __USERINTERFACELANG_RUS_H_");
                sbUserInterfaceLangTranslationHdr.AppendLine("#define __USERINTERFACELANG_RUS_H_");
                sbUserInterfaceLangTranslationHdr.AppendLine();
                sbUserInterfaceLangTranslationHdr.AppendLine("namespace UserInterface");
                sbUserInterfaceLangTranslationHdr.AppendLine("{");
                sbUserInterfaceLangTranslationHdr.AppendLine(String.Format("  __flash const unsigned short textReference_{0}[] =", curLangId));
                sbUserInterfaceLangTranslationHdr.AppendLine("  {");

                int curCharPos = 0;
                for (int i = 0; i < menuConfig.TranslationList.Count; i++)
                {
                    sbUserInterfaceLangTranslationHdr.AppendLine(
                        String.Format("    {0},         //{1}",
                            curCharPos.ToString().PadLeft(4, ' '),
                            translationCodePrefix + menuConfig.TranslationList[i].TranslationId));
                    String curStr = menuConfig.TranslationList[i][curLangId];
                    curCharPos += curStr.Length + 1;
                }

                sbUserInterfaceLangTranslationHdr.AppendLine("  };");
                sbUserInterfaceLangTranslationHdr.AppendLine();
                sbUserInterfaceLangTranslationHdr.AppendLine(String.Format("  __flash const unsigned char textStrings_{0}[] =", curLangId));
                sbUserInterfaceLangTranslationHdr.AppendLine("  {");

                curCharPos = 0;
                for (int i = 0; i < menuConfig.TranslationList.Count; i++)
                {
                    String curStr = menuConfig.TranslationList[i][curLangId];
                    String curLCDStr = Win2LCDStrEngine.win2LCDStr(curStr);

                    if (curLCDStr.Length > 0)
                    {
                        curLCDStr += ",";
                    }

                    sbUserInterfaceLangTranslationHdr.AppendLine(
                        String.Format("    {0}, {1}", curStr.Length.ToString().PadLeft(2, ' '), curLCDStr).PadRight(114) +
                        String.Format("//{0} - {1}", curCharPos.ToString().PadLeft(4, ' '), curStr));

                    curCharPos += curStr.Length + 1;
                }

                sbUserInterfaceLangTranslationHdr.AppendLine("  };");
                sbUserInterfaceLangTranslationHdr.AppendLine("}");
                sbUserInterfaceLangTranslationHdr.AppendLine();
                sbUserInterfaceLangTranslationHdr.AppendLine("#endif");

                File.WriteAllText(Path.Combine(menuConfig.TargetPath, String.Format("UserInterfaceLang_{0}.h", curLangId)), sbUserInterfaceLangTranslationHdr.ToString(), Encoding.Default);
            }

            StringBuilder curFunctionList = new StringBuilder();
            curFunctionList.AppendLine("  __flash const TMenuFunctionReference menuFunctions[] =");
            curFunctionList.AppendLine("  {");

            StringBuilder curMenuList = new StringBuilder();
            curMenuList.AppendLine("  __flash const TMenuDescription menuDescription[] =");
            curMenuList.AppendLine("  {");

            StringBuilder curFunctionRefList = new StringBuilder();
            StringBuilder curMenuRefList = new StringBuilder();

            String curEmptyTranslation = (menuConfig.TranslationList.Count > 0) ? (translationCodePrefix + menuConfig.TranslationList[0].TranslationId) : "0";

            int curFunctionPos = 0;
            int curMenuPos = 0;

            for (int i = 0; i < menuConfig.FunctionList.Count; i++)
            {
                FunctionListItem curFuncItem = menuConfig.FunctionList[i];

                MenuListItem curMenuItemTop = menuConfig.MenuList.Find(
                    delegate(MenuListItem _value)
                    {
                        return String.IsNullOrEmpty(_value.ParentMenuId) &&
                               (String.Compare(_value.FunctionId, curFuncItem.FunctionId, true) == 0);
                    }
                );

                if (curMenuItemTop != null)
                {
                    List<String> menuList = new List<String>();
                    menuList.Add(curMenuItemTop.MenuId);

                    while (menuList.Count > 0)
                    {
                        String curParentMenuId = menuList[0];
                        menuList.RemoveAt(0);

                        MenuListItem curParentMenu = menuConfig.MenuList[menuConfig.MenuRef[curParentMenuId]];

                        curMenuRefList.AppendLine(
                            String.Format("#define USER_MENU_{0} ", curParentMenuId).PadRight(114) +
                            String.Format("({0})", curMenuPos));

                        curFunctionList.AppendLine(
                            ("    {" + String.Format(".entryPoint = (void*)(&({0})),",
                                (curParentMenu.SelectableOption && (!String.IsNullOrEmpty(curParentMenu.FunctionId))) ?
                                    menuConfig.FunctionList[menuConfig.FunctionRef[curParentMenu.FunctionId]].Method : curFuncItem.Method)).PadRight(114) +
                            String.Format("//{0} - USER_MENU_{1}", curFunctionPos.ToString().PadLeft(4, ' '), curParentMenuId));
                        curFunctionList.AppendLine((String.Format("     .args.parm = USER_MENU_{0}", curParentMenuId) + "},").PadRight(114) + "//");

                        curFunctionRefList.AppendLine(
                            String.Format("#define USER_MENUITEM_{0} ", curParentMenuId).PadRight(114) +
                            String.Format("({0})", curFunctionPos));

                        curFunctionPos++;

                        foreach (MenuListItem curMenuItem in menuConfig.MenuList)
                        {
                            if (String.Compare(curMenuItem.ParentMenuId, curParentMenuId, true) == 0)
                            {
                                bool isMenuItem = curMenuItem.SelectableOption || String.IsNullOrEmpty(curMenuItem.FunctionId);
                                if (!isMenuItem)
                                {
                                    isMenuItem = menuConfig.MenuList.Exists(
                                        delegate(MenuListItem _value)
                                        {
                                            return String.Compare(_value.ParentMenuId, curMenuItem.MenuId, true) == 0;
                                        }
                                    );
                                }

                                curMenuList.AppendLine("    {".PadRight(114) + String.Format("//{0}", curMenuPos.ToString().PadLeft(4, ' ')));
                                curMenuList.AppendLine(
                                    String.Format("      .menuFunction = {0},",
                                        isMenuItem ?
                                        String.Format("USER_MENUITEM_{0}", curMenuItem.MenuId) :
                                        String.Format("USER_FUNCTION_{0}", curMenuItem.FunctionId)));
                                curMenuList.AppendLine(String.Format("      .textRefLine0 = {0},", (curMenuItem.TextLineId1.Length > 0) ? translationCodePrefix + curMenuItem.TextLineId1 : curEmptyTranslation));
                                curMenuList.AppendLine(String.Format("      .textRefLine1 = {0},", (curMenuItem.TextLineId2.Length > 0) ? translationCodePrefix + curMenuItem.TextLineId2 : curEmptyTranslation));
                                curMenuList.AppendLine("    },");

                                curMenuPos++;

                                if (isMenuItem)
                                {
                                    menuList.Add(curMenuItem.MenuId);
                                }
                            }
                        }

                        curMenuList.AppendLine("    {".PadRight(114) + String.Format("//{0}", curMenuPos.ToString().PadLeft(4, ' ')));
                        curMenuList.AppendLine("      .menuFunction = 0,");
                        curMenuList.AppendLine("      .textRefLine0 = 0,");
                        curMenuList.AppendLine("      .textRefLine1 = 0,");
                        curMenuList.AppendLine("    },");

                        curMenuPos++;
                    }
                }
                else
                {
                    bool isSelectableOptionFunc = menuConfig.MenuList.Exists(
                        delegate(MenuListItem _value)
                        {
                            return _value.SelectableOption &&
                                   (String.Compare(_value.FunctionId, curFuncItem.FunctionId, true) == 0);
                        }
                    );

                    if (!isSelectableOptionFunc)
                    {
                        if (String.IsNullOrEmpty(curFuncItem.Method))
                        {
                            curFunctionList.AppendLine(
                                "    {.entryPoint = 0},".PadRight(114) +
                                String.Format("//{0} - {1}", curFunctionPos.ToString().PadLeft(4, ' '), curFuncItem.FunctionId));
                        }
                        else
                        {
                            curFunctionList.AppendLine(
                                ("    {" + String.Format(".entryPoint = (void*)(&({0})),", curFuncItem.Method)).PadRight(114) +
                                String.Format("//{0} - {1}", curFunctionPos.ToString().PadLeft(4, ' '), curFuncItem.FunctionId));
                            curFunctionList.AppendLine((String.Format("     .args.parm = {0}", curFuncItem.ParmId) + "},").PadRight(114) + "//");
                        }

                        curFunctionRefList.AppendLine(
                            String.Format("#define USER_FUNCTION_{0} ", curFuncItem.FunctionId).PadRight(114) +
                            String.Format("({0})", curFunctionPos));

                        curFunctionPos++;
                    }
                }
            }

            curFunctionList.AppendLine("  };");
            curMenuList.AppendLine("  };");

            StringBuilder sbUserInterfaceMenuBuilderHdr = new StringBuilder();
            sbUserInterfaceMenuBuilderHdr.AppendLine("#ifndef __USERINTERFACEMENUBUILDER_H_");
            sbUserInterfaceMenuBuilderHdr.AppendLine("#define __USERINTERFACEMENUBUILDER_H_");
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.Append(curFunctionRefList);
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.Append(curMenuRefList);
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.AppendLine("namespace UserInterface");
            sbUserInterfaceMenuBuilderHdr.AppendLine("{");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  typedef struct");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  {");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    unsigned char parm;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  } TMenuFunctionArgs;");
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.AppendLine("  typedef struct");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  {");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    void* entryPoint;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    TMenuFunctionArgs args;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  } TMenuFunctionReference;");
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.AppendLine("  typedef struct");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  {");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    unsigned char menuFunction;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    unsigned char textRefLine0;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("    unsigned char textRefLine1;");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  } TMenuDescription;");
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.AppendLine("  extern __flash const TMenuFunctionReference menuFunctions[];");
            sbUserInterfaceMenuBuilderHdr.AppendLine("  extern __flash const TMenuDescription menuDescription[];");
            sbUserInterfaceMenuBuilderHdr.AppendLine("}");
            sbUserInterfaceMenuBuilderHdr.AppendLine();
            sbUserInterfaceMenuBuilderHdr.AppendLine("#endif");

            File.WriteAllText(Path.Combine(menuConfig.TargetPath, "UserInterfaceMenuBuilder.h"), sbUserInterfaceMenuBuilderHdr.ToString(), Encoding.Default);

            StringBuilder sbUserInterfaceMenuBuilderCpp = new StringBuilder();
            sbUserInterfaceMenuBuilderCpp.AppendLine("#ifndef __USERINTERFACEMENUBUILDER_CPP_");
            sbUserInterfaceMenuBuilderCpp.AppendLine("#define __USERINTERFACEMENUBUILDER_CPP_");
            sbUserInterfaceMenuBuilderCpp.AppendLine();
            sbUserInterfaceMenuBuilderCpp.AppendLine("#include \"UserInterfaceMenuBuilder.h\"");
            sbUserInterfaceMenuBuilderCpp.AppendLine("#include \"UserInterface.h\"");
            sbUserInterfaceMenuBuilderCpp.AppendLine("#include \"UserInterfaceLang.h\"");
            sbUserInterfaceMenuBuilderCpp.AppendLine();
            sbUserInterfaceMenuBuilderCpp.AppendLine("namespace UserInterface");
            sbUserInterfaceMenuBuilderCpp.AppendLine("{");
            sbUserInterfaceMenuBuilderCpp.Append(curFunctionList);
            sbUserInterfaceMenuBuilderCpp.AppendLine();
            sbUserInterfaceMenuBuilderCpp.Append(curMenuList);
            sbUserInterfaceMenuBuilderCpp.AppendLine();
            sbUserInterfaceMenuBuilderCpp.AppendLine("}");
            sbUserInterfaceMenuBuilderCpp.AppendLine();
            sbUserInterfaceMenuBuilderCpp.AppendLine("#endif");


            File.WriteAllText(Path.Combine(menuConfig.TargetPath, "UserInterfaceMenuBuilder.cpp"), sbUserInterfaceMenuBuilderCpp.ToString(), Encoding.Default);
        }

        private void btnBuild_Click(object sender, EventArgs e)
        {
            buildCodeFiles();
        }

        private void btnMenuAddRoot_Click(object sender, EventArgs e)
        {
            edtMenuTree.SelectedNode = null;
            btnMenuAdd_Click(sender, e);
        }
    }
}
