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

namespace Tile_Editor
{

    public struct Tiles
    {
        int x, y;

        public int Y
        {
            get { return y; }
            set { y = value; }
        }

        public int X
        {
            get { return x; }
            set { x = value; }
        }
        
    public Tiles (int _x,int _y)
    {
        this.x = _x;
        this.y = _y;

    }
    }
}
