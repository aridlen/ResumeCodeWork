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
using System.Drawing;
using System.Drawing.Drawing2D;
namespace WindowsFormsApplication1
{
    public class Region_editor
    {

        private System.Drawing.Color colors;

        public System.Drawing.Color Colors
        {
            get { return colors; }
            set { colors = value; }
        }
        private string title;

        public string Title
        {
            get { return title; }
            set { title = value; }
        }
        bool selection;

        public bool Selection
        {
            get { return selection; }
            set { selection = value; }
        }
        public decimal xd, yd, wd, hd;
        public enum shapes { Rectangle };
        shapes shapebox;

        public shapes Shapebox
        {
            get { return shapebox; }
            set { shapebox = value; }
        }

        public decimal Hd
        {
            get { return hd; }
            set { hd = value; }
        }

        public decimal Wd
        {
            get { return wd; }
            set { wd = value; }
        }

        public decimal Yd
        {
            get { return yd; }
            set { yd = value; }
        }

        public decimal Xd
        {
            get { return xd; }
            set { xd = value; }
        }
        Point location;

        public Point Location
        {
            get { return location; }
            set { location = value; }
        }
        Rectangle rect;

        public Rectangle Rect
        {
            get { return rect; }
            set { rect = value; }
        }
        Size sizes;

        public Size Sizes
        {
            get { return sizes; }
            set { sizes = value; }
        }
        public int GetSize()
        {
            return ((int)wd * (int)hd);

        }
    }
}
