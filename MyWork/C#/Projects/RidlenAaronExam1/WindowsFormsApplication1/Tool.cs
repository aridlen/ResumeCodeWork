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

namespace WindowsFormsApplication1
{
    public partial class Tool : Form
    {
        public event EventHandler buttonAdd_Click2;
        public Tool()
        {
            
            InitializeComponent();
        }
        private void button4_Click(object sender, EventArgs e)
        {
            if (buttonAdd_Click2 != null)
            {
                buttonAdd_Click2(this, EventArgs.Empty);
            }
        }
    }
}
