namespace Tile_Editor
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.groupBoxControl1 = new System.Windows.Forms.GroupBox();
            this.radioButtonImport = new System.Windows.Forms.RadioButton();
            this.radioButtonDes = new System.Windows.Forms.RadioButton();
            this.radioButtonPixel = new System.Windows.Forms.RadioButton();
            this.radioButtonGrass = new System.Windows.Forms.RadioButton();
            this.buttonTool = new System.Windows.Forms.Button();
            this.radioButtonDesert = new System.Windows.Forms.RadioButton();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.graphicsPanel1 = new Tile_Editor.GraphicsPanel();
            this.graphicsPanel2 = new Tile_Editor.GraphicsPanel();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.groupBoxControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(992, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.toolStripSeparator,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.toolStripSeparator2,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("newToolStripMenuItem.Image")));
            this.newToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(171, 26);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripMenuItem.Image")));
            this.openToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(171, 26);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(168, 6);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("saveToolStripMenuItem.Image")));
            this.saveToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(171, 26);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(168, 6);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(168, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(171, 26);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolWindowToolStripMenuItem,
            this.importToolStripMenuItem});
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(57, 24);
            this.toolsToolStripMenuItem.Text = "&Tools";
            // 
            // toolWindowToolStripMenuItem
            // 
            this.toolWindowToolStripMenuItem.Name = "toolWindowToolStripMenuItem";
            this.toolWindowToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.toolWindowToolStripMenuItem.Text = "Tool Window";
            this.toolWindowToolStripMenuItem.Click += new System.EventHandler(this.ToolsButton_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 28);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.graphicsPanel2);
            this.splitContainer1.Size = new System.Drawing.Size(992, 442);
            this.splitContainer1.SplitterDistance = 330;
            this.splitContainer1.TabIndex = 1;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.graphicsPanel1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.AutoScroll = true;
            this.splitContainer2.Panel2.Controls.Add(this.groupBoxControl1);
            this.splitContainer2.Panel2.Controls.Add(this.buttonTool);
            this.splitContainer2.Panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer2_Panel2_Paint);
            this.splitContainer2.Size = new System.Drawing.Size(330, 442);
            this.splitContainer2.SplitterDistance = 221;
            this.splitContainer2.TabIndex = 3;
            // 
            // groupBoxControl1
            // 
            this.groupBoxControl1.Controls.Add(this.radioButtonImport);
            this.groupBoxControl1.Controls.Add(this.radioButtonDes);
            this.groupBoxControl1.Controls.Add(this.radioButtonPixel);
            this.groupBoxControl1.Controls.Add(this.radioButtonGrass);
            this.groupBoxControl1.Location = new System.Drawing.Point(12, 18);
            this.groupBoxControl1.Name = "groupBoxControl1";
            this.groupBoxControl1.Size = new System.Drawing.Size(172, 187);
            this.groupBoxControl1.TabIndex = 1;
            this.groupBoxControl1.TabStop = false;
            this.groupBoxControl1.Text = "Terrain";
            // 
            // radioButtonImport
            // 
            this.radioButtonImport.AutoSize = true;
            this.radioButtonImport.Location = new System.Drawing.Point(37, 119);
            this.radioButtonImport.Name = "radioButtonImport";
            this.radioButtonImport.Size = new System.Drawing.Size(68, 21);
            this.radioButtonImport.TabIndex = 4;
            this.radioButtonImport.Text = "Import";
            this.radioButtonImport.UseVisualStyleBackColor = true;
            this.radioButtonImport.CheckedChanged += new System.EventHandler(this.radioButtonImport_CheckedChanged);
            // 
            // radioButtonDes
            // 
            this.radioButtonDes.AutoSize = true;
            this.radioButtonDes.Location = new System.Drawing.Point(37, 37);
            this.radioButtonDes.Name = "radioButtonDes";
            this.radioButtonDes.Size = new System.Drawing.Size(71, 21);
            this.radioButtonDes.TabIndex = 3;
            this.radioButtonDes.Text = "Desert";
            this.radioButtonDes.UseVisualStyleBackColor = true;
            this.radioButtonDes.CheckedChanged += new System.EventHandler(this.radioButtonDes_CheckedChanged);
            // 
            // radioButtonPixel
            // 
            this.radioButtonPixel.AutoSize = true;
            this.radioButtonPixel.Location = new System.Drawing.Point(37, 91);
            this.radioButtonPixel.Name = "radioButtonPixel";
            this.radioButtonPixel.Size = new System.Drawing.Size(73, 21);
            this.radioButtonPixel.TabIndex = 2;
            this.radioButtonPixel.Text = "Beauty";
            this.radioButtonPixel.UseVisualStyleBackColor = true;
            this.radioButtonPixel.CheckedChanged += new System.EventHandler(this.radioButtonDes_CheckedChanged);
            // 
            // radioButtonGrass
            // 
            this.radioButtonGrass.AutoSize = true;
            this.radioButtonGrass.Checked = true;
            this.radioButtonGrass.Location = new System.Drawing.Point(37, 64);
            this.radioButtonGrass.Name = "radioButtonGrass";
            this.radioButtonGrass.Size = new System.Drawing.Size(94, 21);
            this.radioButtonGrass.TabIndex = 1;
            this.radioButtonGrass.TabStop = true;
            this.radioButtonGrass.Text = "Grassland";
            this.radioButtonGrass.UseVisualStyleBackColor = true;
            this.radioButtonGrass.CheckedChanged += new System.EventHandler(this.radioButtonDes_CheckedChanged);
            // 
            // buttonTool
            // 
            this.buttonTool.Location = new System.Drawing.Point(225, 108);
            this.buttonTool.Name = "buttonTool";
            this.buttonTool.Size = new System.Drawing.Size(75, 23);
            this.buttonTool.TabIndex = 2;
            this.buttonTool.Text = "Tools";
            this.buttonTool.UseVisualStyleBackColor = true;
            this.buttonTool.Click += new System.EventHandler(this.ToolsButton_Click);
            // 
            // radioButtonDesert
            // 
            this.radioButtonDesert.AutoSize = true;
            this.radioButtonDesert.Location = new System.Drawing.Point(58, 294);
            this.radioButtonDesert.Name = "radioButtonDesert";
            this.radioButtonDesert.Size = new System.Drawing.Size(71, 21);
            this.radioButtonDesert.TabIndex = 0;
            this.radioButtonDesert.TabStop = true;
            this.radioButtonDesert.Text = "Desert";
            this.radioButtonDesert.UseVisualStyleBackColor = true;
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.importToolStripMenuItem.Text = "Import";
            this.importToolStripMenuItem.Click += new System.EventHandler(this.importToolStripMenuItem_Click);
            // 
            // graphicsPanel1
            // 
            this.graphicsPanel1.BackColor = System.Drawing.SystemColors.Control;
            this.graphicsPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphicsPanel1.Location = new System.Drawing.Point(0, 0);
            this.graphicsPanel1.Name = "graphicsPanel1";
            this.graphicsPanel1.Size = new System.Drawing.Size(330, 221);
            this.graphicsPanel1.TabIndex = 0;
            this.graphicsPanel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel1_Paint);
            this.graphicsPanel1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.graphicsPanel1_ClickSelectTile);
            // 
            // graphicsPanel2
            // 
            this.graphicsPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphicsPanel2.Location = new System.Drawing.Point(0, 0);
            this.graphicsPanel2.Name = "graphicsPanel2";
            this.graphicsPanel2.Size = new System.Drawing.Size(658, 442);
            this.graphicsPanel2.TabIndex = 0;
            this.graphicsPanel2.Paint += new System.Windows.Forms.PaintEventHandler(this.graphicsPanel2_Paint);
            this.graphicsPanel2.MouseClick += new System.Windows.Forms.MouseEventHandler(this.graphicsPanel2_MouseClick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(992, 470);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.radioButtonDesert);
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.groupBoxControl1.ResumeLayout(false);
            this.groupBoxControl1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ToolStripMenuItem toolWindowToolStripMenuItem;
        private GraphicsPanel graphicsPanel2;
        private System.Windows.Forms.GroupBox groupBoxControl1;
        private System.Windows.Forms.RadioButton radioButtonPixel;
        private System.Windows.Forms.RadioButton radioButtonGrass;
        private System.Windows.Forms.RadioButton radioButtonDesert;
        private System.Windows.Forms.Button buttonTool;
        private System.Windows.Forms.RadioButton radioButtonImport;
        private System.Windows.Forms.RadioButton radioButtonDes;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private GraphicsPanel graphicsPanel1;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
         
    }
}

