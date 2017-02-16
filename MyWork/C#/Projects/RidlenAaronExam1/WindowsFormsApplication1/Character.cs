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
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    
    public class Character
    {
        private string m_name;
        public decimal x, y;

        public decimal Y
        {
            get { return y; }
            set { y = value; }
        }

        public decimal X
        {
            get { return x; }
            set { x = value; }
        }
        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }

        public override string ToString()
        {

            
            return this.Name+"{ X = "+this.x+','+" Y = "+this.y+'}';
        }



    }
}
