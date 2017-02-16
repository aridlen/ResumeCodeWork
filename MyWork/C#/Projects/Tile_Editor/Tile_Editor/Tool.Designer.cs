namespace Tile_Editor
{
    partial class Tool
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDownTH1 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTW1 = new System.Windows.Forms.NumericUpDown();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.numericUpDownTH3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTW3 = new System.Windows.Forms.NumericUpDown();
            this.buttonToolUpdate = new System.Windows.Forms.Button();
            this.comboBoxTileSizeW = new System.Windows.Forms.ComboBox();
            this.comboBoxTileSizeH = new System.Windows.Forms.ComboBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTH1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTW1)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTH3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTW3)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.numericUpDownTH1);
            this.groupBox1.Controls.Add(this.numericUpDownTW1);
            this.groupBox1.Location = new System.Drawing.Point(88, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Map Size";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(54, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Height";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(55, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Width";
            // 
            // numericUpDownTH1
            // 
            this.numericUpDownTH1.Location = new System.Drawing.Point(105, 62);
            this.numericUpDownTH1.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.numericUpDownTH1.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDownTH1.Name = "numericUpDownTH1";
            this.numericUpDownTH1.Size = new System.Drawing.Size(89, 22);
            this.numericUpDownTH1.TabIndex = 1;
            this.numericUpDownTH1.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // numericUpDownTW1
            // 
            this.numericUpDownTW1.Location = new System.Drawing.Point(105, 22);
            this.numericUpDownTW1.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.numericUpDownTW1.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDownTW1.Name = "numericUpDownTW1";
            this.numericUpDownTW1.Size = new System.Drawing.Size(89, 22);
            this.numericUpDownTW1.TabIndex = 0;
            this.numericUpDownTW1.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.comboBoxTileSizeH);
            this.groupBox2.Controls.Add(this.comboBoxTileSizeW);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(88, 118);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 100);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Tile Size";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(55, 27);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "Width";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(50, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 17);
            this.label3.TabIndex = 4;
            this.label3.Text = "Height";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.numericUpDownTH3);
            this.groupBox3.Controls.Add(this.numericUpDownTW3);
            this.groupBox3.Location = new System.Drawing.Point(88, 226);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 100);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Tile Set";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(55, 26);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(44, 17);
            this.label6.TabIndex = 5;
            this.label6.Text = "Width";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(50, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 17);
            this.label4.TabIndex = 4;
            this.label4.Text = "Height";
            // 
            // numericUpDownTH3
            // 
            this.numericUpDownTH3.Location = new System.Drawing.Point(105, 50);
            this.numericUpDownTH3.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericUpDownTH3.Name = "numericUpDownTH3";
            this.numericUpDownTH3.Size = new System.Drawing.Size(89, 22);
            this.numericUpDownTH3.TabIndex = 1;
            this.numericUpDownTH3.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // numericUpDownTW3
            // 
            this.numericUpDownTW3.Location = new System.Drawing.Point(105, 21);
            this.numericUpDownTW3.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericUpDownTW3.Name = "numericUpDownTW3";
            this.numericUpDownTW3.Size = new System.Drawing.Size(89, 22);
            this.numericUpDownTW3.TabIndex = 0;
            this.numericUpDownTW3.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // buttonToolUpdate
            // 
            this.buttonToolUpdate.Location = new System.Drawing.Point(146, 344);
            this.buttonToolUpdate.Name = "buttonToolUpdate";
            this.buttonToolUpdate.Size = new System.Drawing.Size(75, 23);
            this.buttonToolUpdate.TabIndex = 3;
            this.buttonToolUpdate.Text = "Update";
            this.buttonToolUpdate.UseVisualStyleBackColor = true;
            this.buttonToolUpdate.Click += new System.EventHandler(this.buttonToolUpdate_Click);
            // 
            // comboBoxTileSizeW
            // 
            this.comboBoxTileSizeW.FormattingEnabled = true;
            this.comboBoxTileSizeW.Items.AddRange(new object[] {
            "16",
            "32",
            "48",
            "64"});
            this.comboBoxTileSizeW.Location = new System.Drawing.Point(105, 21);
            this.comboBoxTileSizeW.Name = "comboBoxTileSizeW";
            this.comboBoxTileSizeW.Size = new System.Drawing.Size(89, 24);
            this.comboBoxTileSizeW.TabIndex = 6;
            // 
            // comboBoxTileSizeH
            // 
            this.comboBoxTileSizeH.FormattingEnabled = true;
            this.comboBoxTileSizeH.Items.AddRange(new object[] {
            "16",
            "32",
            "48",
            "64"});
            this.comboBoxTileSizeH.Location = new System.Drawing.Point(106, 47);
            this.comboBoxTileSizeH.Name = "comboBoxTileSizeH";
            this.comboBoxTileSizeH.Size = new System.Drawing.Size(88, 24);
            this.comboBoxTileSizeH.TabIndex = 7;
            // 
            // Tool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 394);
            this.Controls.Add(this.buttonToolUpdate);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Tool";
            this.Text = "Tool";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTH1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTW1)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTH3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTW3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownTH1;
        private System.Windows.Forms.NumericUpDown numericUpDownTW1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownTH3;
        private System.Windows.Forms.NumericUpDown numericUpDownTW3;
        private System.Windows.Forms.Button buttonToolUpdate;
        private System.Windows.Forms.ComboBox comboBoxTileSizeH;
        private System.Windows.Forms.ComboBox comboBoxTileSizeW;
    }
}