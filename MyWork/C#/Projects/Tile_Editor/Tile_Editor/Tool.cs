///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Charles               //
//      Date:  AUGUST 2015               //
//                                       //
///////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tile_Editor
{
    
    public partial class Tool : Form
    {
        public event EventHandler UpdateButton_Click;
        
        public Tool()
        {
            InitializeComponent();
            comboBoxTileSizeH.SelectedIndex = 3;
            comboBoxTileSizeW.SelectedIndex = 3;
        }

       public int MapSizeH ()
       {
           return (int)numericUpDownTH1.Value;


       }
        public void MapSizeSet(int _x)
       {
           numericUpDownTH1.Value = _x;
           numericUpDownTW1.Value = _x;

       }
        public int MapSizeW ()
       {
           return (int)numericUpDownTW1.Value;
           
       }
        public int TileSizeH ()
        {
            return Int32.Parse(comboBoxTileSizeH.SelectedItem.ToString());

        }
     public int TileSizeW ()
        {
            return Int32.Parse(comboBoxTileSizeW.SelectedItem.ToString());

        }
        public int TileSetH ()
     {
         return (int)numericUpDownTH3.Value;
     }
       public int TileSetW ()
        {
            return (int)numericUpDownTW3.Value;

        }
        public void TileSizeToolChangeIndex(int _x)
       {
           comboBoxTileSizeH.SelectedIndex = _x;
           comboBoxTileSizeW.SelectedIndex = _x;

       }
        public void TilesettoolchangeW(int _x)
        {
            numericUpDownTW3.Value = _x;

        }
        public void TilesettoolchangeH(int _x)
        {
            numericUpDownTH3.Value = _x;

        }
       private void buttonToolUpdate_Click(object sender, EventArgs e)
       {
           if (UpdateButton_Click != null)
           {
               UpdateButton_Click(this, EventArgs.Empty);
           }
          
       }
    }
}
