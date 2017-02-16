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
    public partial class Form1 : Form
    {
        Bitmap bitmap = Properties.Resources._default;
        Size tilesizeset = new Size(4, 2);
        Size tilesize = new Size(64, 64);
        Tiles[,] map = new Tiles[5, 5];
        Size mapsize = new Size(5, 5);
        Tiles selected;
        Tool ToolButton = null;
        //bool action = false;
        
        public Form1()
        {
            //Reset DPI
            InitializeComponent();
            Graphics pic = splitContainer1.Panel1.CreateGraphics();
            //Reset bitmap and help the trash out
            bitmap.SetResolution(pic.DpiX, pic.DpiY);
            pic.Dispose();
            graphicsPanel1.AutoScrollMinSize = bitmap.Size;
            
            graphicsPanel2.AutoScrollMinSize=new Size(tilesize.Width*mapsize.Width,tilesize.Height*mapsize.Height);
        }

        private void customizeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
            
          
            Point Location = new Point(0, 0);
            //Location.X;
            Location.X += graphicsPanel1.AutoScrollPosition.X;
            Location.Y += graphicsPanel1.AutoScrollPosition.Y;

            e.Graphics.DrawImage(bitmap, Location);
            Rectangle rext = Rectangle.Empty;
            for(int i=0;i<tilesizeset.Width;++i)
            {
                for(int j=0;j<tilesizeset.Height;++j)
                {
                    
                    rext.X = i * tilesize.Width + Location.X;
                    rext.Y = j * tilesize.Height + Location.Y;
                    rext.Size = tilesize;
                    //if(selected.X == i && selected.Y == j)
                    //{
                    //    e.Graphics.DrawRectangle(Pens.Red, rext);
                    //}
                    //else
                    e.Graphics.DrawRectangle(Pens.Black, rext);

                }

            }
           
               rext.X = selected.X * tilesize.Width + Location.X;
               rext.Y = selected.Y * tilesize.Height + Location.Y;
               e.Graphics.DrawRectangle(Pens.Red, rext);

        }

        private void graphicsPanel1_ClickSelectTile(object sender, MouseEventArgs e)
        {
            int x, y;
            x=(e.X - graphicsPanel1.AutoScrollPosition.X) / tilesize.Width;
           y= (e.Y - graphicsPanel1.AutoScrollPosition.Y) / tilesize.Height;

            if ((x <= (tilesizeset.Width-1) && y <= (tilesizeset.Height-1)))
            {
                selected.X = (e.X - graphicsPanel1.AutoScrollPosition.X) / tilesize.Width;
                selected.Y = (e.Y - graphicsPanel1.AutoScrollPosition.Y) / tilesize.Height;
                graphicsPanel1.Invalidate();
            }
        }

        private void graphicsPanel2_Paint(object sender, PaintEventArgs e)
        {
        
            Point offset = new Point(0,0);
            offset.X += graphicsPanel2.AutoScrollPosition.X;
            offset.Y += graphicsPanel2.AutoScrollPosition.Y;

            for(int i=0;i<mapsize.Width;++i)
            {
                for(int j=0;j<mapsize.Height;++j)
                {
                    //Figure where tile will be drawn
                    Rectangle drawnrext = Rectangle.Empty;
                    drawnrext.X=i*tilesize.Width;
                    drawnrext.Y=j*tilesize.Height;
                    drawnrext.Size = tilesize;
                    //Calculate the tile drawn in the bitmap
                    Rectangle tilerext = Rectangle.Empty;
                    tilerext.X = map[i, j].X * tilesize.Width;
                    tilerext.Y=map[i,j].Y*tilesize.Height;
                    tilerext.Size=tilesize;
                    
                    //Input autoscroll position and draw the tile and gridlines
                    drawnrext.X += graphicsPanel2.AutoScrollPosition.X;
                    drawnrext.Y += graphicsPanel2.AutoScrollPosition.Y;

                    //Don't forget your Graphics Pixel usage
                    e.Graphics.DrawImage(bitmap, drawnrext, tilerext, GraphicsUnit.Pixel);

                    e.Graphics.DrawRectangle(Pens.Black, drawnrext);
                }
            }
        }

        private void graphicsPanel2_MouseClick(object sender, MouseEventArgs e)
        {
            int x = (e.X - graphicsPanel2.AutoScrollPosition.X)/tilesize.Width;
            int y = (e.Y - graphicsPanel2.AutoScrollPosition.Y) / tilesize.Height;

            if(x<mapsize.Width && y <mapsize.Height)
            {
                map[x,y] = selected;
                graphicsPanel2.Invalidate();


            }


        }
        private void ToolsButton_Click(object sender, EventArgs e)
        {
            if (ToolButton == null)
            {
                ToolButton = new Tool();
                ToolButton.FormClosed += tool_FormClosed;
                ToolButton.UpdateButton_Click += UpdateButton_Click;
               // ToolButton.buttonAdd_Click2 += buttonAdd_Click2;
                ToolButton.Show(this);
            }
        }
        void tool_FormClosed(object sender, FormClosedEventArgs e)
        {
            ToolButton = null;
        }
        private void UpdateButton_Click(object sender,EventArgs e)
        {

        
            
            Tiles[,] tempmap = map;
            int oldwidth = mapsize.Width;
            int oldheight = mapsize.Height;
            mapsize.Width = ToolButton.MapSizeW();
            mapsize.Height = ToolButton.MapSizeH();
            Size tempsize = mapsize;
           tempsize.Width = ToolButton.MapSizeW() * ToolButton.TileSizeW();
            tempsize.Height= ToolButton.MapSizeH() * ToolButton.TileSizeH();
            graphicsPanel2.AutoScrollMinSize = tempsize;
            map = new Tiles[tempsize.Width, tempsize.Height];
            ///Redo tile set
            tilesize.Width = ToolButton.TileSizeW();
            tilesize.Height = ToolButton.TileSizeH();
            Size temptilesize = new Size();
            temptilesize.Width = ToolButton.TileSizeW() * mapsize.Width;
            temptilesize.Height = ToolButton.TileSizeH() * mapsize.Height;
            graphicsPanel2.AutoScrollMinSize = temptilesize;
            graphicsPanel1.AutoScrollMinSize = temptilesize;
            graphicsPanel1.Invalidate();
            
            //
           // tilesize = new Size(ToolButton.TileSizeW(), ToolButton.TileSizeH());
            
            tilesizeset.Width = ToolButton.TileSetW();
            tilesizeset.Height = ToolButton.TileSetH();
            //tilesizeset = new Size(ToolButton.TileSetW(), ToolButton.TileSetH());
            for (int h = 0; h < oldheight && h<tempsize.Height;++h )
            {
                for (int w=0;w<oldwidth && w<tempsize.Width;++w)
                {
                    map[w, h] = tempmap[w, h];
                }

            }
                graphicsPanel2.Invalidate();

        }

        private void radioButtonDes_CheckedChanged(object sender, EventArgs e)
        {
           
            if (radioButtonDes.Checked == true)
            {
                
                bitmap = new Bitmap(Properties.Resources.desert_default);
                Graphics g = graphicsPanel1.CreateGraphics();
                
                for (int i = 0; i < mapsize.Height;++i )
                {
                    for(int j=0;j<mapsize.Width;++j)
                    {

                        map[j, i] = new Tiles (0,0);

                    }

                }
                    selected.X = 0;
                selected.Y = 0;
                bitmap.SetResolution(g.DpiX, g.DpiY);
                g.Dispose();
                graphicsPanel1.AutoScrollMinSize = bitmap.Size;
                Graphics k = graphicsPanel2.CreateGraphics();
                bitmap.SetResolution(k.DpiX, k.DpiY);
                k.Dispose();
                graphicsPanel2.AutoScrollMinSize = bitmap.Size;
                graphicsPanel1.Invalidate();
                graphicsPanel2.Invalidate();
                //
                
                tilesizeset.Width = 9;
                tilesizeset.Height = 8;
                tilesize.Width = 32;
                tilesize.Height = 32;
                mapsize.Width = 5;
                mapsize.Height = 5;
                if (ToolButton != null)
                {
                    ToolButton.TileSizeToolChangeIndex(1);
                    ToolButton.TilesettoolchangeW(9);
                    ToolButton.TilesettoolchangeH(8);
                    ToolButton.MapSizeSet(5);
                }

            }
            else if (radioButtonGrass.Checked == true)
            {
                bitmap = new Bitmap(Properties.Resources._default);
                Graphics g = graphicsPanel1.CreateGraphics();
              
                for (int i = 0; i < mapsize.Height; ++i)
                {
                    for (int j = 0; j < mapsize.Width; ++j)
                    {

                        map[j, i] = new Tiles (0,0);

                    }

                }
                selected.X = 0;
                selected.Y = 0;
                bitmap.SetResolution(g.DpiX, g.DpiY);
                g.Dispose();
                graphicsPanel1.AutoScrollMinSize = bitmap.Size;
                Graphics k = graphicsPanel2.CreateGraphics();
                bitmap.SetResolution(k.DpiX, k.DpiY);
                k.Dispose();
                graphicsPanel2.AutoScrollMinSize = bitmap.Size;
                graphicsPanel1.Invalidate();
                graphicsPanel2.Invalidate();
                //
                
                tilesizeset.Width = 4;
                tilesizeset.Height = 2;
                tilesize.Width = 64;
                tilesize.Height = 64;
                mapsize.Width = 5;
                mapsize.Height = 5;
                if (ToolButton != null)
                {
                    ToolButton.TileSizeToolChangeIndex(3);
                    ToolButton.TilesettoolchangeW(4);
                    ToolButton.TilesettoolchangeH(2);
                    ToolButton.MapSizeSet(5);
                }
            }
            else if (radioButtonPixel.Checked == true)
            {
                bitmap = new Bitmap(Properties.Resources.super4x4x64x64);
                
                Graphics g = graphicsPanel1.CreateGraphics();
                
                for (int i = 0; i < mapsize.Height; ++i)
                {
                    for (int j = 0; j < mapsize.Width; ++j)
                    {

                        map[j, i] = new Tiles (0,0);

                    }

                }
                selected.X = 0;
                selected.Y = 0;
                bitmap.SetResolution(g.DpiX, g.DpiY);
                g.Dispose();
                graphicsPanel1.AutoScrollMinSize = bitmap.Size;
                Graphics k = graphicsPanel2.CreateGraphics();
                bitmap.SetResolution(k.DpiX, k.DpiY);
                k.Dispose();
                graphicsPanel2.AutoScrollMinSize = bitmap.Size;
                graphicsPanel1.Invalidate();
                graphicsPanel2.Invalidate();
                //
                
                tilesizeset.Width = 4;
                tilesizeset.Height = 4;
                tilesize.Width = 64;
                tilesize.Height = 64;
                mapsize.Width = 5;
                mapsize.Height = 5;
                if (ToolButton != null)
                {
                    ToolButton.TileSizeToolChangeIndex(3);
                    ToolButton.TilesettoolchangeW(4);
                    ToolButton.TilesettoolchangeH(4);
                    ToolButton.MapSizeSet(5);
                }

            }
        }

        

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bitmap = new Bitmap(Properties.Resources._default);
            Graphics newg = graphicsPanel2.CreateGraphics();
            Tiles temp = map[0, 0];
            for (int i = 0; i < mapsize.Height; ++i)
            {
                for (int j = 0; j < mapsize.Width; ++j)
                {

                    map[j, i] = temp;

                }

            }
            bitmap.SetResolution(newg.DpiX, newg.DpiY);
            newg.Dispose();
            graphicsPanel2.AutoScrollMinSize = bitmap.Size;
            mapsize = new Size(5, 5);
            if(ToolButton!=null)
            ToolButton.MapSizeSet(5);
            tilesize = new Size(64, 64);
            if (ToolButton != null)
            ToolButton.TileSizeToolChangeIndex(3);
            tilesizeset = new Size(4, 2);
            if (ToolButton != null)
            {
                ToolButton.TilesettoolchangeW(4);
                ToolButton.TilesettoolchangeH(2);
            }
            map = new Tiles[5, 5];
            graphicsPanel1.Invalidate();
            graphicsPanel2.Invalidate();



        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.cvs)|*.cvs";
            if (DialogResult.OK==dlg.ShowDialog())
            {
                System.IO.StreamReader reader = new
                System.IO.StreamReader(dlg.FileName);

                string userinput = reader.ReadLine();
                char[] delims = { ' ', ',' };
                string[] input = userinput.Split(delims);


                tilesizeset.Width =int.Parse(input[0]);
                    tilesizeset.Height = int.Parse(input[1]);
                    tilesize.Width = int.Parse(input[2]);
                    tilesize.Height = int.Parse(input[3]);
                    mapsize.Width = int.Parse(input[4]);
                    mapsize.Height = int.Parse(input[5]);
                
                    for (int i = 0; i <mapsize.Height ;++i )
                    {
                        // readline
                        string input2=reader.ReadLine();
                        string[] input22 = input2.Split(delims);
                        
                        for(int j=0,k=0;j<mapsize.Width;++j)
                        {
                            //parse the line
                            
                            //Set the x and y at map j,i
                            map[j, i].X= int.Parse(input22[k++]);
                            map[j, i].Y = int.Parse(input22[k++]);
                        }

                    }


          
                
                    reader.Close();

            }
            graphicsPanel1.Invalidate();
            graphicsPanel2.Invalidate();


        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.cvs)|*.cvs";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                System.IO.StreamWriter writer = new
                System.IO.StreamWriter(dlg.FileName);

                dlg.DefaultExt = "cvs";
                writer.WriteLine(tilesizeset.Width + " " + tilesizeset.Height + " " + tilesize.Width + " " + tilesize.Height +" "+ mapsize.Width + " " + mapsize.Height);
                for (int i = 0; i < mapsize.Height; ++i)
                {
                    string x="";
                    for (int j = 0; j < mapsize.Width; ++j)
                    {
                       x += map[j, i].X.ToString() + ' ' + map[j, i].Y.ToString() + ',';
                    }
                    writer.WriteLine(x);
                }
                writer.Close();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void radioButtonImport_CheckedChanged(object sender, EventArgs e)
        {
            if(radioButtonImport.Checked==true)
            {
                OpenFileDialog dlg = new OpenFileDialog();

                //Set the dialog filters
                dlg.Filter = "All Files|*.*|BMP Files|*.bmp|JPG Files|*.jpg";
                if (DialogResult.OK == dlg.ShowDialog())
                {
                    //Import the new bitmap
                    bitmap = new Bitmap(dlg.FileName);

                    //Set DPI
                    Graphics g = splitContainer1.Panel1.CreateGraphics();
                    //Readjust the scroll bars
                    bitmap.SetResolution(g.DpiX, g.DpiY);
                    g.Dispose();
                    graphicsPanel1.AutoScrollMinSize = bitmap.Size;
                    graphicsPanel2.AutoScrollMinSize = bitmap.Size;
                    //Invalidate the panel
                    graphicsPanel1.Invalidate();
                    graphicsPanel2.Invalidate();
                }





            }
        }

        private void splitContainer2_Panel2_Paint(object sender, PaintEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += splitContainer2.Panel2.AutoScrollPosition.X;
            offset.Y += splitContainer2.Panel2.AutoScrollPosition.Y;
        }

        private void importToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();

            //Set the dialog filters
            dlg.Filter = "All Files|*.*|BMP Files|*.bmp|JPG Files|*.jpg";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                //Import the new bitmap
                bitmap = new Bitmap(dlg.FileName);

                //Set DPI
                Graphics g = splitContainer1.Panel1.CreateGraphics();
                //Readjust the scroll bars
                bitmap.SetResolution(g.DpiX, g.DpiY);
                g.Dispose();
                graphicsPanel1.AutoScrollMinSize = bitmap.Size;
                graphicsPanel2.AutoScrollMinSize = bitmap.Size;
                //Invalidate the panel
                graphicsPanel1.Invalidate();
                graphicsPanel2.Invalidate();
            }
        }

        
        
       
    }
}
