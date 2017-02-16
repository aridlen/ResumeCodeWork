using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Tile_Editor
{
   public class GraphicsPanel : Panel
    {
      
       public GraphicsPanel()
       {
           this.DoubleBuffered = true;
           this.SetStyle(ControlStyles.ResizeRedraw, true);
       }
    }
}
