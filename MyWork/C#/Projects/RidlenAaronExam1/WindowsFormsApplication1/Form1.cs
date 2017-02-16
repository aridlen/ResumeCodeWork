using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        List<Region_editor> obj = new List<Region_editor>();
        List<Point> clickobj = new List<Point>();
        Tool tool = null;
        public Form1()
        {
            InitializeComponent();
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            Character c = new Character();

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            Character c = new Character();
            c.Name = textBoxName.Text;
            c.x = numericUpDownX.Value;
            c.y = numericUpDownY.Value;
            listBoxMain.Items.Add(c);
            ///drawing
            Region_editor obj1 = new Region_editor();
            Rectangle obj2 = new Rectangle();
            obj2.X = (int)numericUpDownX.Value;
            obj2.Y = (int)numericUpDownY.Value;
            obj2.Width = (int)50;
            obj2.Height = (int)50;
            obj1.Title = textBoxName.Text;
            obj1.xd = (int)numericUpDownX.Value;
            obj1.yd = (int)numericUpDownY.Value;
            obj1.wd = (int)50;
            obj1.hd = (int)50;
            obj1.Location = new Point((int)numericUpDownX.Value, (int)numericUpDownY.Value);
            obj1.Sizes = new Size((int)50, (int)50);
            obj1.Colors = Color.Aqua;
            obj1.Rect = obj2;
            obj.Add(obj1);
            splitContainer1.Panel2.Invalidate();


        }

        private void buttonRemove_Click(object sender, EventArgs e)
        {
            if (listBoxMain.SelectedIndex <= -1)
                return;
            obj.RemoveAt(listBoxMain.SelectedIndex);
            listBoxMain.Items.RemoveAt(listBoxMain.SelectedIndex);
            
            listBoxMain.SelectedIndex = -1;
            textBoxName.Clear();
            numericUpDownX.Value = 0;
            numericUpDownY.Value = 0;
            
            
            
            splitContainer1.Panel2.Invalidate();

        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (listBoxMain.SelectedIndex <= -1)
                return;
            Character c = (Character)listBoxMain.Items[listBoxMain.SelectedIndex];
            c.Name = textBoxName.Text;
            c.x = numericUpDownX.Value;
            c.y = numericUpDownY.Value;
            
            ////
            for (int i = 0; i < obj.Count; ++i)
            {
                if (obj[i].Selection == true)
                {

                    obj[i].Location = new Point((int)numericUpDownX.Value,(int)numericUpDownY.Value);
                    obj[i].Title = textBoxName.Text;
                    splitContainer1.Panel2.Invalidate();
                }

            }
            listBoxMain.Items[listBoxMain.SelectedIndex] = listBoxMain.Items[listBoxMain.SelectedIndex];
            
        }


        private void buttonDeselect_Click(object sender, EventArgs e)
        {
            if (listBoxMain.SelectedIndex <= -1)
                return;
            listBoxMain.SelectedIndex = -1;
            textBoxName.Clear();
            numericUpDownX.Value = 0;
            numericUpDownY.Value = 0;
            for (int i = 0; i < obj.Count; ++i)
            {
                obj[i].Selection = false;
            }
            splitContainer1.Panel2.Invalidate();

        }
        private void listBoxMain_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBoxMain.SelectedIndex <= -1)
                return;
            Character c = (Character)listBoxMain.Items[listBoxMain.SelectedIndex];
            textBoxName.Text = c.Name;
            numericUpDownX.Value = c.x;
            numericUpDownY.Value = c.y;
            for (int i = 0; i < obj.Count; ++i)
            {
                obj[i].Selection = false;
                
            }
            obj[listBoxMain.SelectedIndex].Selection = true;
            splitContainer1.Panel2.Invalidate();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxName.Clear();
            numericUpDownX.Value = 0;
            numericUpDownY.Value = 0;
            listBoxMain.Items.Clear();
            obj.Clear();
            splitContainer1.Panel2.Invalidate();
            
        }
        private void splitContainer1_Panel2_Click(object sender, MouseEventArgs e)
        {

            for (int i = 0; i < obj.Count; ++i)
            {
                obj[i].Selection = false;

            }
            if (e.Button == MouseButtons.Left)
            {
                for (int j = 0; j < obj.Count; ++j)
                {
                    if (obj[j].Rect.Contains(e.Location))
                    {
                        obj[j].Selection = true;
                        listBoxMain.SelectedIndex = j;
                        splitContainer1.Panel2.Invalidate();
                        
                    }

                }
            }
                if (e.Button == MouseButtons.Right)
                {

                    Character c = new Character();
                    c.Name = "Default";
                    c.x = e.Location.X;
                    c.y = e.Location.Y;
                    listBoxMain.Items.Add(c);
                    Region_editor obj1 = new Region_editor();
                    Rectangle obj2 = new Rectangle();
                    obj2.X = e.Location.X;
                    obj2.Y = e.Location.Y;
                    obj2.Width = (int)50;
                    obj2.Height = (int)50;
                    obj1.Title = "Default";
                    obj1.xd = e.Location.X;
                    obj1.yd = e.Location.Y;
                    obj1.wd = (int)50;
                    obj1.hd = (int)50;
                    obj1.Location = new Point(e.Location.X, e.Location.Y);
                    obj1.Sizes = new Size((int)50, (int)50);
                    obj1.Colors = Color.Aqua;
                  
                        numericUpDownX.Value = e.Location.X;
                        numericUpDownY.Value = e.Location.Y;
                    
                    textBoxName.Text = "Default";
                    obj1.Rect = obj2;
                    obj.Add(obj1);
                    
                    splitContainer1.Panel2.Invalidate();






                }
            



        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {
            Pen pen = new Pen(Color.Blue, 5.0f);
            for (int i = 0; i < obj.Count; ++i)
            {
                if (obj[i].Selection)
                {
                    pen.Color = Color.Coral;

                }
                else
                {
                    pen.Color = Color.Blue;


                }
                Rectangle newrex = new Rectangle();
                newrex.Location = obj[i].Location;
                newrex.Size = obj[i].Sizes;

                String drawnstring = obj[i].Title;

                Font drawnfont = new Font("Times Roman Numerial", 8, FontStyle.Regular, GraphicsUnit.Point);

                StringFormat newformat = new StringFormat();
                newformat.Alignment = StringAlignment.Center;
                newformat.LineAlignment = StringAlignment.Center;
                Brush brushes = new SolidBrush(Color.Crimson);


                e.Graphics.DrawRectangle(pen, newrex);
                
               
                e.Graphics.DrawString(drawnstring, drawnfont, brushes, newrex, newformat);
                if (i >= 1)
                    e.Graphics.DrawLine(Pens.Blue, obj[i - 1].Location, obj[i].Location);

               
                


            }
        }
             private void buttonAdd_Click2(object sender, EventArgs e)
        {
            Character c = new Character();
            c.Name = textBoxName.Text;
            c.x = numericUpDownX.Value;
            c.y = numericUpDownY.Value;
            listBoxMain.Items.Add(c);
            ///drawing
            Region_editor obj1 = new Region_editor();
            Rectangle obj2 = new Rectangle();
            obj2.X = (int)numericUpDownX.Value;
            obj2.Y = (int)numericUpDownY.Value;
            obj2.Width = (int)50;
            obj2.Height = (int)50;
            obj1.Title = textBoxName.Text;
            obj1.xd = (int)numericUpDownX.Value;
            obj1.yd = (int)numericUpDownY.Value;
            obj1.wd = (int)50;
            obj1.hd = (int)50;
            obj1.Location = new Point((int)numericUpDownX.Value, (int)numericUpDownY.Value);
            obj1.Sizes = new Size((int)50, (int)50);
            obj1.Colors = Color.Aqua;
            obj1.Rect = obj2;
            obj.Add(obj1);
            


        }

             private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
             {
                 if (tool == null)
                 {
                     tool = new Tool();
                     tool.FormClosed += tool_FormClosed;
                     tool.buttonAdd_Click2 += buttonAdd_Click2;
                     tool.Show(this);
                 }
             }
             void tool_FormClosed(object sender, FormClosedEventArgs e)
             {
                 tool = null;
             }

             private void exitToolStripMenuItem_Click(object sender, EventArgs e)
             {
                 this.Close();
             }
        }

        
        
            

           

        
    }

