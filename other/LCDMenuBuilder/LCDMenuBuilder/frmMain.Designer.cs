namespace LCDMenuBuilder
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabMainTabs = new System.Windows.Forms.TabControl();
            this.tpMenu = new System.Windows.Forms.TabPage();
            this.pnlMenu = new System.Windows.Forms.Panel();
            this.edtSelectableOption = new System.Windows.Forms.CheckBox();
            this.edtMenuTextLine2Mod = new System.Windows.Forms.Label();
            this.edtMenuTextLine1Mod = new System.Windows.Forms.Label();
            this.edtMenuFunctionMod = new System.Windows.Forms.Label();
            this.edtMenuIdMod = new System.Windows.Forms.Label();
            this.btnMenuSave = new System.Windows.Forms.Button();
            this.edtMenuTextLine2 = new System.Windows.Forms.ComboBox();
            this.lblMenuTextLine2 = new System.Windows.Forms.Label();
            this.edtMenuTextLine1 = new System.Windows.Forms.ComboBox();
            this.lblMenuTextLine1 = new System.Windows.Forms.Label();
            this.edtMenuFunction = new System.Windows.Forms.ComboBox();
            this.lblMenuFunction = new System.Windows.Forms.Label();
            this.edtMenuId = new System.Windows.Forms.TextBox();
            this.lblMenuId = new System.Windows.Forms.Label();
            this.btnMenuRemove = new System.Windows.Forms.Button();
            this.btnMenuAdd = new System.Windows.Forms.Button();
            this.splitterMenu = new System.Windows.Forms.Splitter();
            this.edtMenuTree = new System.Windows.Forms.TreeView();
            this.tpFunctions = new System.Windows.Forms.TabPage();
            this.pnlFunctions = new System.Windows.Forms.Panel();
            this.edtFunctionParmMod = new System.Windows.Forms.Label();
            this.edtFunctionMethodMod = new System.Windows.Forms.Label();
            this.edtFunctionIdMod = new System.Windows.Forms.Label();
            this.edtFunctionParm = new System.Windows.Forms.NumericUpDown();
            this.edtFunctionMethod = new System.Windows.Forms.TextBox();
            this.btnFunctionSave = new System.Windows.Forms.Button();
            this.lblFunctionParm = new System.Windows.Forms.Label();
            this.lblFunctionMethod = new System.Windows.Forms.Label();
            this.edtFunctionId = new System.Windows.Forms.TextBox();
            this.lblFunctionId = new System.Windows.Forms.Label();
            this.btnFunctionRemove = new System.Windows.Forms.Button();
            this.btnFunctionAdd = new System.Windows.Forms.Button();
            this.splitterFunctions = new System.Windows.Forms.Splitter();
            this.pnlFunctionsList = new System.Windows.Forms.Panel();
            this.edtFunctionsList = new System.Windows.Forms.ListBox();
            this.pnlFunctionsListBtn = new System.Windows.Forms.Panel();
            this.btnFunctionDown = new System.Windows.Forms.Button();
            this.btnFunctionUp = new System.Windows.Forms.Button();
            this.tpTexts = new System.Windows.Forms.TabPage();
            this.pnlTexts = new System.Windows.Forms.Panel();
            this.edtTextDescDigits = new System.Windows.Forms.Label();
            this.edtTextIdMod = new System.Windows.Forms.Label();
            this.edtTextDescMod = new System.Windows.Forms.Label();
            this.edtLangSelected = new System.Windows.Forms.Label();
            this.lblLangSelected = new System.Windows.Forms.Label();
            this.edtTextsLng = new System.Windows.Forms.TextBox();
            this.btnTextsLngRemove = new System.Windows.Forms.Button();
            this.btnTextsLngAdd = new System.Windows.Forms.Button();
            this.edtTextDesc = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.lblTextDesc = new System.Windows.Forms.Label();
            this.edtTextId = new System.Windows.Forms.TextBox();
            this.lblTextId = new System.Windows.Forms.Label();
            this.btnTextsRemove = new System.Windows.Forms.Button();
            this.btnTextsAdd = new System.Windows.Forms.Button();
            this.splitterTexts = new System.Windows.Forms.Splitter();
            this.pnlTextsList = new System.Windows.Forms.Panel();
            this.edtTextsList = new System.Windows.Forms.ListBox();
            this.pnlTextsListRight = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.edtTextsLangList = new System.Windows.Forms.ListBox();
            this.pnlMain = new System.Windows.Forms.Panel();
            this.edtConfigPath = new System.Windows.Forms.TextBox();
            this.lblConfigPath = new System.Windows.Forms.Label();
            this.btnBuild = new System.Windows.Forms.Button();
            this.btnSaveConfig = new System.Windows.Forms.Button();
            this.btnLoadConfig = new System.Windows.Forms.Button();
            this.edtTargetDir = new System.Windows.Forms.TextBox();
            this.lblTargetDir = new System.Windows.Forms.Label();
            this.btnMenuAddRoot = new System.Windows.Forms.Button();
            this.tabMainTabs.SuspendLayout();
            this.tpMenu.SuspendLayout();
            this.pnlMenu.SuspendLayout();
            this.tpFunctions.SuspendLayout();
            this.pnlFunctions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.edtFunctionParm)).BeginInit();
            this.pnlFunctionsList.SuspendLayout();
            this.pnlFunctionsListBtn.SuspendLayout();
            this.tpTexts.SuspendLayout();
            this.pnlTexts.SuspendLayout();
            this.pnlTextsList.SuspendLayout();
            this.pnlTextsListRight.SuspendLayout();
            this.pnlMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabMainTabs
            // 
            this.tabMainTabs.Controls.Add(this.tpMenu);
            this.tabMainTabs.Controls.Add(this.tpFunctions);
            this.tabMainTabs.Controls.Add(this.tpTexts);
            this.tabMainTabs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabMainTabs.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tabMainTabs.Location = new System.Drawing.Point(0, 120);
            this.tabMainTabs.Name = "tabMainTabs";
            this.tabMainTabs.SelectedIndex = 0;
            this.tabMainTabs.Size = new System.Drawing.Size(1201, 482);
            this.tabMainTabs.TabIndex = 0;
            // 
            // tpMenu
            // 
            this.tpMenu.Controls.Add(this.pnlMenu);
            this.tpMenu.Controls.Add(this.splitterMenu);
            this.tpMenu.Controls.Add(this.edtMenuTree);
            this.tpMenu.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tpMenu.Location = new System.Drawing.Point(4, 29);
            this.tpMenu.Name = "tpMenu";
            this.tpMenu.Padding = new System.Windows.Forms.Padding(3);
            this.tpMenu.Size = new System.Drawing.Size(1193, 449);
            this.tpMenu.TabIndex = 0;
            this.tpMenu.Text = "Menu";
            this.tpMenu.UseVisualStyleBackColor = true;
            // 
            // pnlMenu
            // 
            this.pnlMenu.Controls.Add(this.btnMenuAddRoot);
            this.pnlMenu.Controls.Add(this.edtSelectableOption);
            this.pnlMenu.Controls.Add(this.edtMenuTextLine2Mod);
            this.pnlMenu.Controls.Add(this.edtMenuTextLine1Mod);
            this.pnlMenu.Controls.Add(this.edtMenuFunctionMod);
            this.pnlMenu.Controls.Add(this.edtMenuIdMod);
            this.pnlMenu.Controls.Add(this.btnMenuSave);
            this.pnlMenu.Controls.Add(this.edtMenuTextLine2);
            this.pnlMenu.Controls.Add(this.lblMenuTextLine2);
            this.pnlMenu.Controls.Add(this.edtMenuTextLine1);
            this.pnlMenu.Controls.Add(this.lblMenuTextLine1);
            this.pnlMenu.Controls.Add(this.edtMenuFunction);
            this.pnlMenu.Controls.Add(this.lblMenuFunction);
            this.pnlMenu.Controls.Add(this.edtMenuId);
            this.pnlMenu.Controls.Add(this.lblMenuId);
            this.pnlMenu.Controls.Add(this.btnMenuRemove);
            this.pnlMenu.Controls.Add(this.btnMenuAdd);
            this.pnlMenu.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlMenu.Location = new System.Drawing.Point(303, 3);
            this.pnlMenu.Name = "pnlMenu";
            this.pnlMenu.Size = new System.Drawing.Size(887, 443);
            this.pnlMenu.TabIndex = 2;
            // 
            // edtSelectableOption
            // 
            this.edtSelectableOption.AutoSize = true;
            this.edtSelectableOption.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtSelectableOption.Location = new System.Drawing.Point(89, 80);
            this.edtSelectableOption.Name = "edtSelectableOption";
            this.edtSelectableOption.Size = new System.Drawing.Size(159, 24);
            this.edtSelectableOption.TabIndex = 46;
            this.edtSelectableOption.Text = "Selectable option";
            this.edtSelectableOption.UseVisualStyleBackColor = true;
            this.edtSelectableOption.CheckedChanged += new System.EventHandler(this.edtSelectableOption_CheckedChanged);
            // 
            // edtMenuTextLine2Mod
            // 
            this.edtMenuTextLine2Mod.AutoSize = true;
            this.edtMenuTextLine2Mod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuTextLine2Mod.ForeColor = System.Drawing.Color.Red;
            this.edtMenuTextLine2Mod.Location = new System.Drawing.Point(587, 181);
            this.edtMenuTextLine2Mod.Name = "edtMenuTextLine2Mod";
            this.edtMenuTextLine2Mod.Size = new System.Drawing.Size(16, 20);
            this.edtMenuTextLine2Mod.TabIndex = 45;
            this.edtMenuTextLine2Mod.Text = "*";
            this.edtMenuTextLine2Mod.Visible = false;
            // 
            // edtMenuTextLine1Mod
            // 
            this.edtMenuTextLine1Mod.AutoSize = true;
            this.edtMenuTextLine1Mod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuTextLine1Mod.ForeColor = System.Drawing.Color.Red;
            this.edtMenuTextLine1Mod.Location = new System.Drawing.Point(587, 147);
            this.edtMenuTextLine1Mod.Name = "edtMenuTextLine1Mod";
            this.edtMenuTextLine1Mod.Size = new System.Drawing.Size(16, 20);
            this.edtMenuTextLine1Mod.TabIndex = 44;
            this.edtMenuTextLine1Mod.Text = "*";
            this.edtMenuTextLine1Mod.Visible = false;
            // 
            // edtMenuFunctionMod
            // 
            this.edtMenuFunctionMod.AutoSize = true;
            this.edtMenuFunctionMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuFunctionMod.ForeColor = System.Drawing.Color.Red;
            this.edtMenuFunctionMod.Location = new System.Drawing.Point(587, 113);
            this.edtMenuFunctionMod.Name = "edtMenuFunctionMod";
            this.edtMenuFunctionMod.Size = new System.Drawing.Size(16, 20);
            this.edtMenuFunctionMod.TabIndex = 43;
            this.edtMenuFunctionMod.Text = "*";
            this.edtMenuFunctionMod.Visible = false;
            // 
            // edtMenuIdMod
            // 
            this.edtMenuIdMod.AutoSize = true;
            this.edtMenuIdMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuIdMod.ForeColor = System.Drawing.Color.Red;
            this.edtMenuIdMod.Location = new System.Drawing.Point(587, 50);
            this.edtMenuIdMod.Name = "edtMenuIdMod";
            this.edtMenuIdMod.Size = new System.Drawing.Size(16, 20);
            this.edtMenuIdMod.TabIndex = 42;
            this.edtMenuIdMod.Text = "*";
            this.edtMenuIdMod.Visible = false;
            // 
            // btnMenuSave
            // 
            this.btnMenuSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnMenuSave.Location = new System.Drawing.Point(246, 244);
            this.btnMenuSave.Name = "btnMenuSave";
            this.btnMenuSave.Size = new System.Drawing.Size(150, 28);
            this.btnMenuSave.TabIndex = 10;
            this.btnMenuSave.Text = "Save";
            this.btnMenuSave.UseVisualStyleBackColor = true;
            this.btnMenuSave.Click += new System.EventHandler(this.btnMenuSave_Click);
            // 
            // edtMenuTextLine2
            // 
            this.edtMenuTextLine2.DropDownHeight = 250;
            this.edtMenuTextLine2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.edtMenuTextLine2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuTextLine2.FormattingEnabled = true;
            this.edtMenuTextLine2.IntegralHeight = false;
            this.edtMenuTextLine2.Location = new System.Drawing.Point(131, 178);
            this.edtMenuTextLine2.Name = "edtMenuTextLine2";
            this.edtMenuTextLine2.Size = new System.Drawing.Size(450, 28);
            this.edtMenuTextLine2.TabIndex = 9;
            this.edtMenuTextLine2.SelectedIndexChanged += new System.EventHandler(this.edtMenuTextLine2_SelectedIndexChanged);
            this.edtMenuTextLine2.TextChanged += new System.EventHandler(this.edtMenuTextLine2_TextChanged);
            // 
            // lblMenuTextLine2
            // 
            this.lblMenuTextLine2.AutoSize = true;
            this.lblMenuTextLine2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMenuTextLine2.Location = new System.Drawing.Point(6, 181);
            this.lblMenuTextLine2.Name = "lblMenuTextLine2";
            this.lblMenuTextLine2.Size = new System.Drawing.Size(111, 20);
            this.lblMenuTextLine2.TabIndex = 8;
            this.lblMenuTextLine2.Text = "Menu text L2:";
            // 
            // edtMenuTextLine1
            // 
            this.edtMenuTextLine1.DropDownHeight = 250;
            this.edtMenuTextLine1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.edtMenuTextLine1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuTextLine1.FormattingEnabled = true;
            this.edtMenuTextLine1.IntegralHeight = false;
            this.edtMenuTextLine1.Location = new System.Drawing.Point(131, 144);
            this.edtMenuTextLine1.Name = "edtMenuTextLine1";
            this.edtMenuTextLine1.Size = new System.Drawing.Size(450, 28);
            this.edtMenuTextLine1.TabIndex = 7;
            this.edtMenuTextLine1.SelectedIndexChanged += new System.EventHandler(this.edtMenuTextLine1_SelectedIndexChanged);
            this.edtMenuTextLine1.TextChanged += new System.EventHandler(this.edtMenuTextLine1_TextChanged);
            // 
            // lblMenuTextLine1
            // 
            this.lblMenuTextLine1.AutoSize = true;
            this.lblMenuTextLine1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMenuTextLine1.Location = new System.Drawing.Point(6, 147);
            this.lblMenuTextLine1.Name = "lblMenuTextLine1";
            this.lblMenuTextLine1.Size = new System.Drawing.Size(111, 20);
            this.lblMenuTextLine1.TabIndex = 6;
            this.lblMenuTextLine1.Text = "Menu text L1:";
            // 
            // edtMenuFunction
            // 
            this.edtMenuFunction.DropDownHeight = 250;
            this.edtMenuFunction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.edtMenuFunction.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuFunction.FormattingEnabled = true;
            this.edtMenuFunction.IntegralHeight = false;
            this.edtMenuFunction.Location = new System.Drawing.Point(131, 110);
            this.edtMenuFunction.Name = "edtMenuFunction";
            this.edtMenuFunction.Size = new System.Drawing.Size(450, 28);
            this.edtMenuFunction.TabIndex = 5;
            this.edtMenuFunction.SelectedIndexChanged += new System.EventHandler(this.edtMenuFunction_SelectedIndexChanged);
            this.edtMenuFunction.TextChanged += new System.EventHandler(this.edtMenuFunction_TextChanged);
            // 
            // lblMenuFunction
            // 
            this.lblMenuFunction.AutoSize = true;
            this.lblMenuFunction.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMenuFunction.Location = new System.Drawing.Point(6, 113);
            this.lblMenuFunction.Name = "lblMenuFunction";
            this.lblMenuFunction.Size = new System.Drawing.Size(119, 20);
            this.lblMenuFunction.TabIndex = 4;
            this.lblMenuFunction.Text = "Menu function:";
            // 
            // edtMenuId
            // 
            this.edtMenuId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuId.Location = new System.Drawing.Point(89, 47);
            this.edtMenuId.Name = "edtMenuId";
            this.edtMenuId.Size = new System.Drawing.Size(492, 27);
            this.edtMenuId.TabIndex = 3;
            this.edtMenuId.TextChanged += new System.EventHandler(this.edtMenuId_TextChanged);
            // 
            // lblMenuId
            // 
            this.lblMenuId.AutoSize = true;
            this.lblMenuId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMenuId.Location = new System.Drawing.Point(6, 50);
            this.lblMenuId.Name = "lblMenuId";
            this.lblMenuId.Size = new System.Drawing.Size(77, 20);
            this.lblMenuId.TabIndex = 2;
            this.lblMenuId.Text = "Menu ID:";
            // 
            // btnMenuRemove
            // 
            this.btnMenuRemove.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnMenuRemove.Location = new System.Drawing.Point(162, 3);
            this.btnMenuRemove.Name = "btnMenuRemove";
            this.btnMenuRemove.Size = new System.Drawing.Size(150, 28);
            this.btnMenuRemove.TabIndex = 1;
            this.btnMenuRemove.Text = "Remove";
            this.btnMenuRemove.UseVisualStyleBackColor = true;
            this.btnMenuRemove.Click += new System.EventHandler(this.btnMenuRemove_Click);
            // 
            // btnMenuAdd
            // 
            this.btnMenuAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnMenuAdd.Location = new System.Drawing.Point(6, 3);
            this.btnMenuAdd.Name = "btnMenuAdd";
            this.btnMenuAdd.Size = new System.Drawing.Size(150, 28);
            this.btnMenuAdd.TabIndex = 0;
            this.btnMenuAdd.Text = "Add";
            this.btnMenuAdd.UseVisualStyleBackColor = true;
            this.btnMenuAdd.Click += new System.EventHandler(this.btnMenuAdd_Click);
            // 
            // splitterMenu
            // 
            this.splitterMenu.Location = new System.Drawing.Point(300, 3);
            this.splitterMenu.Name = "splitterMenu";
            this.splitterMenu.Size = new System.Drawing.Size(3, 443);
            this.splitterMenu.TabIndex = 1;
            this.splitterMenu.TabStop = false;
            // 
            // edtMenuTree
            // 
            this.edtMenuTree.Dock = System.Windows.Forms.DockStyle.Left;
            this.edtMenuTree.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtMenuTree.HideSelection = false;
            this.edtMenuTree.Location = new System.Drawing.Point(3, 3);
            this.edtMenuTree.Name = "edtMenuTree";
            this.edtMenuTree.Size = new System.Drawing.Size(297, 443);
            this.edtMenuTree.TabIndex = 0;
            this.edtMenuTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.edtMenuTree_AfterSelect);
            // 
            // tpFunctions
            // 
            this.tpFunctions.Controls.Add(this.pnlFunctions);
            this.tpFunctions.Controls.Add(this.splitterFunctions);
            this.tpFunctions.Controls.Add(this.pnlFunctionsList);
            this.tpFunctions.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tpFunctions.Location = new System.Drawing.Point(4, 29);
            this.tpFunctions.Name = "tpFunctions";
            this.tpFunctions.Padding = new System.Windows.Forms.Padding(3);
            this.tpFunctions.Size = new System.Drawing.Size(1193, 449);
            this.tpFunctions.TabIndex = 1;
            this.tpFunctions.Text = "Functions";
            this.tpFunctions.UseVisualStyleBackColor = true;
            // 
            // pnlFunctions
            // 
            this.pnlFunctions.Controls.Add(this.edtFunctionParmMod);
            this.pnlFunctions.Controls.Add(this.edtFunctionMethodMod);
            this.pnlFunctions.Controls.Add(this.edtFunctionIdMod);
            this.pnlFunctions.Controls.Add(this.edtFunctionParm);
            this.pnlFunctions.Controls.Add(this.edtFunctionMethod);
            this.pnlFunctions.Controls.Add(this.btnFunctionSave);
            this.pnlFunctions.Controls.Add(this.lblFunctionParm);
            this.pnlFunctions.Controls.Add(this.lblFunctionMethod);
            this.pnlFunctions.Controls.Add(this.edtFunctionId);
            this.pnlFunctions.Controls.Add(this.lblFunctionId);
            this.pnlFunctions.Controls.Add(this.btnFunctionRemove);
            this.pnlFunctions.Controls.Add(this.btnFunctionAdd);
            this.pnlFunctions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlFunctions.Location = new System.Drawing.Point(389, 3);
            this.pnlFunctions.Name = "pnlFunctions";
            this.pnlFunctions.Size = new System.Drawing.Size(801, 443);
            this.pnlFunctions.TabIndex = 1;
            // 
            // edtFunctionParmMod
            // 
            this.edtFunctionParmMod.AutoSize = true;
            this.edtFunctionParmMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionParmMod.ForeColor = System.Drawing.Color.Red;
            this.edtFunctionParmMod.Location = new System.Drawing.Point(216, 115);
            this.edtFunctionParmMod.Name = "edtFunctionParmMod";
            this.edtFunctionParmMod.Size = new System.Drawing.Size(16, 20);
            this.edtFunctionParmMod.TabIndex = 43;
            this.edtFunctionParmMod.Text = "*";
            this.edtFunctionParmMod.Visible = false;
            // 
            // edtFunctionMethodMod
            // 
            this.edtFunctionMethodMod.AutoSize = true;
            this.edtFunctionMethodMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionMethodMod.ForeColor = System.Drawing.Color.Red;
            this.edtFunctionMethodMod.Location = new System.Drawing.Point(568, 83);
            this.edtFunctionMethodMod.Name = "edtFunctionMethodMod";
            this.edtFunctionMethodMod.Size = new System.Drawing.Size(16, 20);
            this.edtFunctionMethodMod.TabIndex = 42;
            this.edtFunctionMethodMod.Text = "*";
            this.edtFunctionMethodMod.Visible = false;
            // 
            // edtFunctionIdMod
            // 
            this.edtFunctionIdMod.AutoSize = true;
            this.edtFunctionIdMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionIdMod.ForeColor = System.Drawing.Color.Red;
            this.edtFunctionIdMod.Location = new System.Drawing.Point(568, 50);
            this.edtFunctionIdMod.Name = "edtFunctionIdMod";
            this.edtFunctionIdMod.Size = new System.Drawing.Size(16, 20);
            this.edtFunctionIdMod.TabIndex = 41;
            this.edtFunctionIdMod.Text = "*";
            this.edtFunctionIdMod.Visible = false;
            // 
            // edtFunctionParm
            // 
            this.edtFunctionParm.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionParm.Location = new System.Drawing.Point(112, 113);
            this.edtFunctionParm.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.edtFunctionParm.Name = "edtFunctionParm";
            this.edtFunctionParm.Size = new System.Drawing.Size(98, 27);
            this.edtFunctionParm.TabIndex = 23;
            this.edtFunctionParm.ValueChanged += new System.EventHandler(this.edtFunctionParm_ValueChanged);
            // 
            // edtFunctionMethod
            // 
            this.edtFunctionMethod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionMethod.Location = new System.Drawing.Point(112, 80);
            this.edtFunctionMethod.Name = "edtFunctionMethod";
            this.edtFunctionMethod.Size = new System.Drawing.Size(450, 27);
            this.edtFunctionMethod.TabIndex = 22;
            this.edtFunctionMethod.TextChanged += new System.EventHandler(this.edtFunctionMethod_TextChanged);
            // 
            // btnFunctionSave
            // 
            this.btnFunctionSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnFunctionSave.Location = new System.Drawing.Point(179, 168);
            this.btnFunctionSave.Name = "btnFunctionSave";
            this.btnFunctionSave.Size = new System.Drawing.Size(150, 28);
            this.btnFunctionSave.TabIndex = 21;
            this.btnFunctionSave.Text = "Save";
            this.btnFunctionSave.UseVisualStyleBackColor = true;
            this.btnFunctionSave.Click += new System.EventHandler(this.btnFunctionSave_Click);
            // 
            // lblFunctionParm
            // 
            this.lblFunctionParm.AutoSize = true;
            this.lblFunctionParm.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblFunctionParm.Location = new System.Drawing.Point(6, 115);
            this.lblFunctionParm.Name = "lblFunctionParm";
            this.lblFunctionParm.Size = new System.Drawing.Size(92, 20);
            this.lblFunctionParm.TabIndex = 17;
            this.lblFunctionParm.Text = "Parameter:";
            // 
            // lblFunctionMethod
            // 
            this.lblFunctionMethod.AutoSize = true;
            this.lblFunctionMethod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblFunctionMethod.Location = new System.Drawing.Point(6, 83);
            this.lblFunctionMethod.Name = "lblFunctionMethod";
            this.lblFunctionMethod.Size = new System.Drawing.Size(69, 20);
            this.lblFunctionMethod.TabIndex = 15;
            this.lblFunctionMethod.Text = "Method:";
            // 
            // edtFunctionId
            // 
            this.edtFunctionId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionId.Location = new System.Drawing.Point(112, 47);
            this.edtFunctionId.Name = "edtFunctionId";
            this.edtFunctionId.Size = new System.Drawing.Size(450, 27);
            this.edtFunctionId.TabIndex = 14;
            this.edtFunctionId.TextChanged += new System.EventHandler(this.edtFunctionId_TextChanged);
            // 
            // lblFunctionId
            // 
            this.lblFunctionId.AutoSize = true;
            this.lblFunctionId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblFunctionId.Location = new System.Drawing.Point(6, 50);
            this.lblFunctionId.Name = "lblFunctionId";
            this.lblFunctionId.Size = new System.Drawing.Size(100, 20);
            this.lblFunctionId.TabIndex = 13;
            this.lblFunctionId.Text = "Function ID:";
            // 
            // btnFunctionRemove
            // 
            this.btnFunctionRemove.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnFunctionRemove.Location = new System.Drawing.Point(162, 3);
            this.btnFunctionRemove.Name = "btnFunctionRemove";
            this.btnFunctionRemove.Size = new System.Drawing.Size(150, 28);
            this.btnFunctionRemove.TabIndex = 12;
            this.btnFunctionRemove.Text = "Remove";
            this.btnFunctionRemove.UseVisualStyleBackColor = true;
            this.btnFunctionRemove.Click += new System.EventHandler(this.btnFunctionRemove_Click);
            // 
            // btnFunctionAdd
            // 
            this.btnFunctionAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnFunctionAdd.Location = new System.Drawing.Point(6, 3);
            this.btnFunctionAdd.Name = "btnFunctionAdd";
            this.btnFunctionAdd.Size = new System.Drawing.Size(150, 28);
            this.btnFunctionAdd.TabIndex = 11;
            this.btnFunctionAdd.Text = "Add";
            this.btnFunctionAdd.UseVisualStyleBackColor = true;
            this.btnFunctionAdd.Click += new System.EventHandler(this.btnFunctionAdd_Click);
            // 
            // splitterFunctions
            // 
            this.splitterFunctions.Location = new System.Drawing.Point(386, 3);
            this.splitterFunctions.Name = "splitterFunctions";
            this.splitterFunctions.Size = new System.Drawing.Size(3, 443);
            this.splitterFunctions.TabIndex = 4;
            this.splitterFunctions.TabStop = false;
            // 
            // pnlFunctionsList
            // 
            this.pnlFunctionsList.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlFunctionsList.Controls.Add(this.edtFunctionsList);
            this.pnlFunctionsList.Controls.Add(this.pnlFunctionsListBtn);
            this.pnlFunctionsList.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlFunctionsList.Location = new System.Drawing.Point(3, 3);
            this.pnlFunctionsList.Name = "pnlFunctionsList";
            this.pnlFunctionsList.Size = new System.Drawing.Size(383, 443);
            this.pnlFunctionsList.TabIndex = 3;
            // 
            // edtFunctionsList
            // 
            this.edtFunctionsList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.edtFunctionsList.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtFunctionsList.FormattingEnabled = true;
            this.edtFunctionsList.ItemHeight = 20;
            this.edtFunctionsList.Location = new System.Drawing.Point(0, 0);
            this.edtFunctionsList.Name = "edtFunctionsList";
            this.edtFunctionsList.Size = new System.Drawing.Size(311, 441);
            this.edtFunctionsList.TabIndex = 1;
            this.edtFunctionsList.SelectedIndexChanged += new System.EventHandler(this.edtFunctionsList_SelectedIndexChanged);
            // 
            // pnlFunctionsListBtn
            // 
            this.pnlFunctionsListBtn.Controls.Add(this.btnFunctionDown);
            this.pnlFunctionsListBtn.Controls.Add(this.btnFunctionUp);
            this.pnlFunctionsListBtn.Dock = System.Windows.Forms.DockStyle.Right;
            this.pnlFunctionsListBtn.Location = new System.Drawing.Point(311, 0);
            this.pnlFunctionsListBtn.Name = "pnlFunctionsListBtn";
            this.pnlFunctionsListBtn.Size = new System.Drawing.Size(70, 441);
            this.pnlFunctionsListBtn.TabIndex = 2;
            // 
            // btnFunctionDown
            // 
            this.btnFunctionDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnFunctionDown.Location = new System.Drawing.Point(10, 100);
            this.btnFunctionDown.Name = "btnFunctionDown";
            this.btnFunctionDown.Size = new System.Drawing.Size(50, 28);
            this.btnFunctionDown.TabIndex = 4;
            this.btnFunctionDown.Text = "Dn";
            this.btnFunctionDown.UseVisualStyleBackColor = true;
            this.btnFunctionDown.Click += new System.EventHandler(this.btnFunctionDown_Click);
            // 
            // btnFunctionUp
            // 
            this.btnFunctionUp.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnFunctionUp.Location = new System.Drawing.Point(10, 40);
            this.btnFunctionUp.Name = "btnFunctionUp";
            this.btnFunctionUp.Size = new System.Drawing.Size(50, 28);
            this.btnFunctionUp.TabIndex = 3;
            this.btnFunctionUp.Text = "Up";
            this.btnFunctionUp.UseVisualStyleBackColor = true;
            this.btnFunctionUp.Click += new System.EventHandler(this.btnFunctionUp_Click);
            // 
            // tpTexts
            // 
            this.tpTexts.Controls.Add(this.pnlTexts);
            this.tpTexts.Controls.Add(this.splitterTexts);
            this.tpTexts.Controls.Add(this.pnlTextsList);
            this.tpTexts.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tpTexts.Location = new System.Drawing.Point(4, 29);
            this.tpTexts.Name = "tpTexts";
            this.tpTexts.Padding = new System.Windows.Forms.Padding(3);
            this.tpTexts.Size = new System.Drawing.Size(1193, 449);
            this.tpTexts.TabIndex = 2;
            this.tpTexts.Text = "Translations";
            this.tpTexts.UseVisualStyleBackColor = true;
            // 
            // pnlTexts
            // 
            this.pnlTexts.Controls.Add(this.edtTextDescDigits);
            this.pnlTexts.Controls.Add(this.edtTextIdMod);
            this.pnlTexts.Controls.Add(this.edtTextDescMod);
            this.pnlTexts.Controls.Add(this.edtLangSelected);
            this.pnlTexts.Controls.Add(this.lblLangSelected);
            this.pnlTexts.Controls.Add(this.edtTextsLng);
            this.pnlTexts.Controls.Add(this.btnTextsLngRemove);
            this.pnlTexts.Controls.Add(this.btnTextsLngAdd);
            this.pnlTexts.Controls.Add(this.edtTextDesc);
            this.pnlTexts.Controls.Add(this.button3);
            this.pnlTexts.Controls.Add(this.lblTextDesc);
            this.pnlTexts.Controls.Add(this.edtTextId);
            this.pnlTexts.Controls.Add(this.lblTextId);
            this.pnlTexts.Controls.Add(this.btnTextsRemove);
            this.pnlTexts.Controls.Add(this.btnTextsAdd);
            this.pnlTexts.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlTexts.Location = new System.Drawing.Point(474, 3);
            this.pnlTexts.Name = "pnlTexts";
            this.pnlTexts.Size = new System.Drawing.Size(716, 443);
            this.pnlTexts.TabIndex = 2;
            // 
            // edtTextDescDigits
            // 
            this.edtTextDescDigits.AutoSize = true;
            this.edtTextDescDigits.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextDescDigits.Location = new System.Drawing.Point(609, 113);
            this.edtTextDescDigits.Name = "edtTextDescDigits";
            this.edtTextDescDigits.Size = new System.Drawing.Size(19, 20);
            this.edtTextDescDigits.TabIndex = 41;
            this.edtTextDescDigits.Text = "0";
            // 
            // edtTextIdMod
            // 
            this.edtTextIdMod.AutoSize = true;
            this.edtTextIdMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextIdMod.ForeColor = System.Drawing.Color.Red;
            this.edtTextIdMod.Location = new System.Drawing.Point(587, 80);
            this.edtTextIdMod.Name = "edtTextIdMod";
            this.edtTextIdMod.Size = new System.Drawing.Size(16, 20);
            this.edtTextIdMod.TabIndex = 40;
            this.edtTextIdMod.Text = "*";
            this.edtTextIdMod.Visible = false;
            // 
            // edtTextDescMod
            // 
            this.edtTextDescMod.AutoSize = true;
            this.edtTextDescMod.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextDescMod.ForeColor = System.Drawing.Color.Red;
            this.edtTextDescMod.Location = new System.Drawing.Point(587, 113);
            this.edtTextDescMod.Name = "edtTextDescMod";
            this.edtTextDescMod.Size = new System.Drawing.Size(16, 20);
            this.edtTextDescMod.TabIndex = 39;
            this.edtTextDescMod.Text = "*";
            this.edtTextDescMod.Visible = false;
            // 
            // edtLangSelected
            // 
            this.edtLangSelected.AutoSize = true;
            this.edtLangSelected.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtLangSelected.Location = new System.Drawing.Point(127, 46);
            this.edtLangSelected.Name = "edtLangSelected";
            this.edtLangSelected.Size = new System.Drawing.Size(74, 20);
            this.edtLangSelected.TabIndex = 38;
            this.edtLangSelected.Text = "<None>";
            // 
            // lblLangSelected
            // 
            this.lblLangSelected.AutoSize = true;
            this.lblLangSelected.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblLangSelected.Location = new System.Drawing.Point(6, 46);
            this.lblLangSelected.Name = "lblLangSelected";
            this.lblLangSelected.Size = new System.Drawing.Size(96, 20);
            this.lblLangSelected.TabIndex = 37;
            this.lblLangSelected.Text = "Language:";
            // 
            // edtTextsLng
            // 
            this.edtTextsLng.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextsLng.Location = new System.Drawing.Point(10, 212);
            this.edtTextsLng.Name = "edtTextsLng";
            this.edtTextsLng.Size = new System.Drawing.Size(168, 27);
            this.edtTextsLng.TabIndex = 36;
            this.edtTextsLng.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.edtTextsLng_KeyPress);
            // 
            // btnTextsLngRemove
            // 
            this.btnTextsLngRemove.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnTextsLngRemove.Location = new System.Drawing.Point(184, 245);
            this.btnTextsLngRemove.Name = "btnTextsLngRemove";
            this.btnTextsLngRemove.Size = new System.Drawing.Size(150, 28);
            this.btnTextsLngRemove.TabIndex = 34;
            this.btnTextsLngRemove.Text = "Remove Lng";
            this.btnTextsLngRemove.UseVisualStyleBackColor = true;
            this.btnTextsLngRemove.Click += new System.EventHandler(this.btnTextsLngRemove_Click);
            // 
            // btnTextsLngAdd
            // 
            this.btnTextsLngAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnTextsLngAdd.Location = new System.Drawing.Point(184, 211);
            this.btnTextsLngAdd.Name = "btnTextsLngAdd";
            this.btnTextsLngAdd.Size = new System.Drawing.Size(150, 28);
            this.btnTextsLngAdd.TabIndex = 33;
            this.btnTextsLngAdd.Text = "Add Lng";
            this.btnTextsLngAdd.UseVisualStyleBackColor = true;
            this.btnTextsLngAdd.Click += new System.EventHandler(this.btnTextsLngAdd_Click);
            // 
            // edtTextDesc
            // 
            this.edtTextDesc.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextDesc.Location = new System.Drawing.Point(131, 110);
            this.edtTextDesc.MaxLength = 16;
            this.edtTextDesc.Name = "edtTextDesc";
            this.edtTextDesc.Size = new System.Drawing.Size(450, 27);
            this.edtTextDesc.TabIndex = 31;
            this.edtTextDesc.TextChanged += new System.EventHandler(this.edtTextDesc_TextChanged);
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button3.Location = new System.Drawing.Point(184, 157);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(150, 28);
            this.button3.TabIndex = 30;
            this.button3.Text = "Save";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // lblTextDesc
            // 
            this.lblTextDesc.AutoSize = true;
            this.lblTextDesc.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTextDesc.Location = new System.Drawing.Point(6, 113);
            this.lblTextDesc.Name = "lblTextDesc";
            this.lblTextDesc.Size = new System.Drawing.Size(46, 20);
            this.lblTextDesc.TabIndex = 28;
            this.lblTextDesc.Text = "Text:";
            // 
            // edtTextId
            // 
            this.edtTextId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextId.Location = new System.Drawing.Point(131, 77);
            this.edtTextId.Name = "edtTextId";
            this.edtTextId.Size = new System.Drawing.Size(450, 27);
            this.edtTextId.TabIndex = 27;
            this.edtTextId.TextChanged += new System.EventHandler(this.edtTextId_TextChanged);
            // 
            // lblTextId
            // 
            this.lblTextId.AutoSize = true;
            this.lblTextId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTextId.Location = new System.Drawing.Point(6, 80);
            this.lblTextId.Name = "lblTextId";
            this.lblTextId.Size = new System.Drawing.Size(119, 20);
            this.lblTextId.TabIndex = 26;
            this.lblTextId.Text = "Translation ID:";
            // 
            // btnTextsRemove
            // 
            this.btnTextsRemove.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnTextsRemove.Location = new System.Drawing.Point(162, 3);
            this.btnTextsRemove.Name = "btnTextsRemove";
            this.btnTextsRemove.Size = new System.Drawing.Size(150, 28);
            this.btnTextsRemove.TabIndex = 25;
            this.btnTextsRemove.Text = "Remove";
            this.btnTextsRemove.UseVisualStyleBackColor = true;
            this.btnTextsRemove.Click += new System.EventHandler(this.btnTextsRemove_Click);
            // 
            // btnTextsAdd
            // 
            this.btnTextsAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnTextsAdd.Location = new System.Drawing.Point(6, 3);
            this.btnTextsAdd.Name = "btnTextsAdd";
            this.btnTextsAdd.Size = new System.Drawing.Size(150, 28);
            this.btnTextsAdd.TabIndex = 24;
            this.btnTextsAdd.Text = "Add";
            this.btnTextsAdd.UseVisualStyleBackColor = true;
            this.btnTextsAdd.Click += new System.EventHandler(this.btnTextsAdd_Click);
            // 
            // splitterTexts
            // 
            this.splitterTexts.Location = new System.Drawing.Point(471, 3);
            this.splitterTexts.Name = "splitterTexts";
            this.splitterTexts.Size = new System.Drawing.Size(3, 443);
            this.splitterTexts.TabIndex = 1;
            this.splitterTexts.TabStop = false;
            // 
            // pnlTextsList
            // 
            this.pnlTextsList.Controls.Add(this.edtTextsList);
            this.pnlTextsList.Controls.Add(this.pnlTextsListRight);
            this.pnlTextsList.Controls.Add(this.edtTextsLangList);
            this.pnlTextsList.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlTextsList.Location = new System.Drawing.Point(3, 3);
            this.pnlTextsList.Name = "pnlTextsList";
            this.pnlTextsList.Size = new System.Drawing.Size(468, 443);
            this.pnlTextsList.TabIndex = 0;
            // 
            // edtTextsList
            // 
            this.edtTextsList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.edtTextsList.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextsList.FormattingEnabled = true;
            this.edtTextsList.ItemHeight = 20;
            this.edtTextsList.Location = new System.Drawing.Point(0, 0);
            this.edtTextsList.Name = "edtTextsList";
            this.edtTextsList.Size = new System.Drawing.Size(286, 443);
            this.edtTextsList.TabIndex = 0;
            this.edtTextsList.SelectedIndexChanged += new System.EventHandler(this.edtTextsList_SelectedIndexChanged);
            // 
            // pnlTextsListRight
            // 
            this.pnlTextsListRight.Controls.Add(this.button1);
            this.pnlTextsListRight.Controls.Add(this.button2);
            this.pnlTextsListRight.Dock = System.Windows.Forms.DockStyle.Right;
            this.pnlTextsListRight.Location = new System.Drawing.Point(286, 0);
            this.pnlTextsListRight.Name = "pnlTextsListRight";
            this.pnlTextsListRight.Size = new System.Drawing.Size(70, 443);
            this.pnlTextsListRight.TabIndex = 5;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button1.Location = new System.Drawing.Point(10, 100);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(50, 28);
            this.button1.TabIndex = 4;
            this.button1.Text = "Dn";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button2.Location = new System.Drawing.Point(10, 40);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(50, 28);
            this.button2.TabIndex = 3;
            this.button2.Text = "Up";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // edtTextsLangList
            // 
            this.edtTextsLangList.Dock = System.Windows.Forms.DockStyle.Right;
            this.edtTextsLangList.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTextsLangList.FormattingEnabled = true;
            this.edtTextsLangList.ItemHeight = 20;
            this.edtTextsLangList.Location = new System.Drawing.Point(356, 0);
            this.edtTextsLangList.Name = "edtTextsLangList";
            this.edtTextsLangList.Size = new System.Drawing.Size(112, 443);
            this.edtTextsLangList.TabIndex = 4;
            this.edtTextsLangList.SelectedIndexChanged += new System.EventHandler(this.edtTextsLangList_SelectedIndexChanged);
            // 
            // pnlMain
            // 
            this.pnlMain.Controls.Add(this.edtConfigPath);
            this.pnlMain.Controls.Add(this.lblConfigPath);
            this.pnlMain.Controls.Add(this.btnBuild);
            this.pnlMain.Controls.Add(this.btnSaveConfig);
            this.pnlMain.Controls.Add(this.btnLoadConfig);
            this.pnlMain.Controls.Add(this.edtTargetDir);
            this.pnlMain.Controls.Add(this.lblTargetDir);
            this.pnlMain.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlMain.Location = new System.Drawing.Point(0, 0);
            this.pnlMain.Name = "pnlMain";
            this.pnlMain.Size = new System.Drawing.Size(1201, 120);
            this.pnlMain.TabIndex = 1;
            // 
            // edtConfigPath
            // 
            this.edtConfigPath.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtConfigPath.Location = new System.Drawing.Point(150, 48);
            this.edtConfigPath.Name = "edtConfigPath";
            this.edtConfigPath.Size = new System.Drawing.Size(507, 27);
            this.edtConfigPath.TabIndex = 34;
            // 
            // lblConfigPath
            // 
            this.lblConfigPath.AutoSize = true;
            this.lblConfigPath.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblConfigPath.Location = new System.Drawing.Point(12, 51);
            this.lblConfigPath.Name = "lblConfigPath";
            this.lblConfigPath.Size = new System.Drawing.Size(99, 20);
            this.lblConfigPath.TabIndex = 33;
            this.lblConfigPath.Text = "Config path:";
            // 
            // btnBuild
            // 
            this.btnBuild.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnBuild.Location = new System.Drawing.Point(663, 14);
            this.btnBuild.Name = "btnBuild";
            this.btnBuild.Size = new System.Drawing.Size(150, 28);
            this.btnBuild.TabIndex = 32;
            this.btnBuild.Text = "Build";
            this.btnBuild.UseVisualStyleBackColor = true;
            this.btnBuild.Click += new System.EventHandler(this.btnBuild_Click);
            // 
            // btnSaveConfig
            // 
            this.btnSaveConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnSaveConfig.Location = new System.Drawing.Point(168, 81);
            this.btnSaveConfig.Name = "btnSaveConfig";
            this.btnSaveConfig.Size = new System.Drawing.Size(150, 28);
            this.btnSaveConfig.TabIndex = 31;
            this.btnSaveConfig.Text = "Save";
            this.btnSaveConfig.UseVisualStyleBackColor = true;
            this.btnSaveConfig.Click += new System.EventHandler(this.btnSaveConfig_Click);
            // 
            // btnLoadConfig
            // 
            this.btnLoadConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnLoadConfig.Location = new System.Drawing.Point(12, 81);
            this.btnLoadConfig.Name = "btnLoadConfig";
            this.btnLoadConfig.Size = new System.Drawing.Size(150, 28);
            this.btnLoadConfig.TabIndex = 30;
            this.btnLoadConfig.Text = "Load";
            this.btnLoadConfig.UseVisualStyleBackColor = true;
            this.btnLoadConfig.Click += new System.EventHandler(this.btnLoadConfig_Click);
            // 
            // edtTargetDir
            // 
            this.edtTargetDir.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.edtTargetDir.Location = new System.Drawing.Point(150, 15);
            this.edtTargetDir.Name = "edtTargetDir";
            this.edtTargetDir.Size = new System.Drawing.Size(507, 27);
            this.edtTargetDir.TabIndex = 29;
            // 
            // lblTargetDir
            // 
            this.lblTargetDir.AutoSize = true;
            this.lblTargetDir.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTargetDir.Location = new System.Drawing.Point(12, 18);
            this.lblTargetDir.Name = "lblTargetDir";
            this.lblTargetDir.Size = new System.Drawing.Size(132, 20);
            this.lblTargetDir.TabIndex = 28;
            this.lblTargetDir.Text = "Target directory:";
            // 
            // btnMenuAddRoot
            // 
            this.btnMenuAddRoot.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnMenuAddRoot.Location = new System.Drawing.Point(318, 3);
            this.btnMenuAddRoot.Name = "btnMenuAddRoot";
            this.btnMenuAddRoot.Size = new System.Drawing.Size(150, 28);
            this.btnMenuAddRoot.TabIndex = 47;
            this.btnMenuAddRoot.Text = "Add root";
            this.btnMenuAddRoot.UseVisualStyleBackColor = true;
            this.btnMenuAddRoot.Click += new System.EventHandler(this.btnMenuAddRoot_Click);
            // 
            // frmMain
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1201, 602);
            this.Controls.Add(this.tabMainTabs);
            this.Controls.Add(this.pnlMain);
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "LCD menu builder";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.tabMainTabs.ResumeLayout(false);
            this.tpMenu.ResumeLayout(false);
            this.pnlMenu.ResumeLayout(false);
            this.pnlMenu.PerformLayout();
            this.tpFunctions.ResumeLayout(false);
            this.pnlFunctions.ResumeLayout(false);
            this.pnlFunctions.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.edtFunctionParm)).EndInit();
            this.pnlFunctionsList.ResumeLayout(false);
            this.pnlFunctionsListBtn.ResumeLayout(false);
            this.tpTexts.ResumeLayout(false);
            this.pnlTexts.ResumeLayout(false);
            this.pnlTexts.PerformLayout();
            this.pnlTextsList.ResumeLayout(false);
            this.pnlTextsListRight.ResumeLayout(false);
            this.pnlMain.ResumeLayout(false);
            this.pnlMain.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabMainTabs;
        private System.Windows.Forms.TabPage tpMenu;
        private System.Windows.Forms.TreeView edtMenuTree;
        private System.Windows.Forms.Panel pnlMain;
        private System.Windows.Forms.Splitter splitterMenu;
        private System.Windows.Forms.Panel pnlMenu;
        private System.Windows.Forms.Button btnMenuRemove;
        private System.Windows.Forms.Button btnMenuAdd;
        private System.Windows.Forms.Label lblMenuId;
        private System.Windows.Forms.TextBox edtMenuId;
        private System.Windows.Forms.Label lblMenuFunction;
        private System.Windows.Forms.ComboBox edtMenuFunction;
        private System.Windows.Forms.ComboBox edtMenuTextLine1;
        private System.Windows.Forms.Label lblMenuTextLine1;
        private System.Windows.Forms.ComboBox edtMenuTextLine2;
        private System.Windows.Forms.Label lblMenuTextLine2;
        private System.Windows.Forms.Button btnMenuSave;
        private System.Windows.Forms.TabPage tpFunctions;
        private System.Windows.Forms.Panel pnlFunctions;
        private System.Windows.Forms.Button btnFunctionSave;
        private System.Windows.Forms.Label lblFunctionParm;
        private System.Windows.Forms.Label lblFunctionMethod;
        private System.Windows.Forms.TextBox edtFunctionId;
        private System.Windows.Forms.Label lblFunctionId;
        private System.Windows.Forms.Button btnFunctionRemove;
        private System.Windows.Forms.Button btnFunctionAdd;
        private System.Windows.Forms.TextBox edtFunctionMethod;
        private System.Windows.Forms.NumericUpDown edtFunctionParm;
        private System.Windows.Forms.TabPage tpTexts;
        private System.Windows.Forms.Splitter splitterFunctions;
        private System.Windows.Forms.Panel pnlFunctionsList;
        private System.Windows.Forms.ListBox edtFunctionsList;
        private System.Windows.Forms.Panel pnlFunctionsListBtn;
        private System.Windows.Forms.Button btnFunctionDown;
        private System.Windows.Forms.Button btnFunctionUp;
        private System.Windows.Forms.Splitter splitterTexts;
        private System.Windows.Forms.Panel pnlTextsList;
        private System.Windows.Forms.Panel pnlTexts;
        private System.Windows.Forms.TextBox edtTextDesc;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label lblTextDesc;
        private System.Windows.Forms.TextBox edtTextId;
        private System.Windows.Forms.Label lblTextId;
        private System.Windows.Forms.Button btnTextsRemove;
        private System.Windows.Forms.Button btnTextsAdd;
        private System.Windows.Forms.ListBox edtTextsList;
        private System.Windows.Forms.Panel pnlTextsListRight;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ListBox edtTextsLangList;
        private System.Windows.Forms.Button btnTextsLngRemove;
        private System.Windows.Forms.Button btnTextsLngAdd;
        private System.Windows.Forms.TextBox edtTargetDir;
        private System.Windows.Forms.Label lblTargetDir;
        private System.Windows.Forms.Button btnSaveConfig;
        private System.Windows.Forms.Button btnLoadConfig;
        private System.Windows.Forms.Button btnBuild;
        private System.Windows.Forms.TextBox edtTextsLng;
        private System.Windows.Forms.Label edtLangSelected;
        private System.Windows.Forms.Label lblLangSelected;
        private System.Windows.Forms.Label edtTextDescMod;
        private System.Windows.Forms.Label edtTextIdMod;
        private System.Windows.Forms.Label edtFunctionIdMod;
        private System.Windows.Forms.TextBox edtConfigPath;
        private System.Windows.Forms.Label lblConfigPath;
        private System.Windows.Forms.Label edtFunctionMethodMod;
        private System.Windows.Forms.Label edtFunctionParmMod;
        private System.Windows.Forms.Label edtMenuTextLine2Mod;
        private System.Windows.Forms.Label edtMenuTextLine1Mod;
        private System.Windows.Forms.Label edtMenuFunctionMod;
        private System.Windows.Forms.Label edtMenuIdMod;
        private System.Windows.Forms.Label edtTextDescDigits;
        private System.Windows.Forms.CheckBox edtSelectableOption;
        private System.Windows.Forms.Button btnMenuAddRoot;
    }
}

