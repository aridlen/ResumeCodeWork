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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Charactor c = new Charactor();
            string n1 = c.FirstName;
            c.FirstName = "Frank";
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Name_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Charactor c = new Charactor();
            c.FirstName = textBoxName.Text;
            c.LastName = textBoxLname.Text;
            c.Age = numericUpDownAge.Value;
            //Enum x;

             c.x.Race = (Charactor.CharactorSkills.RaceNames)comboBox1.SelectedIndex;

            c.x.strength = numericUpDownStrength.Value;
            c.x.dexterity = numericUpDownDexterity.Value;
            c.x.stealth = numericUpDownStealth.Value;
            c.x.constitution = numericUpDownConst.Value;
            c.x.demolitions = numericUpDownDemo.Value;
            c.x.survival = numericUpDownSurv.Value;
            c.x.intelligence = numericUpDownInt.Value;
            c.x.charisma = numericUpDownChar.Value;
            listBox1.Items.Add(c);

        }
        private void listBox1_SelectedIndexChanged(object sender,EventArgs e)
        {
            if (listBox1.SelectedIndex <= -1)
                return;
            
            Charactor c = (Charactor)listBox1.Items[listBox1.SelectedIndex];

            textBoxName.Text = c.FirstName;
            textBoxLname.Text = c.LastName;
            numericUpDownAge.Value = c.Age;
            comboBox1.SelectedIndex = (int)c.x.Race;
             numericUpDownStrength.Value=c.x.strength;
             numericUpDownDexterity.Value=c.x.dexterity;
             numericUpDownStealth.Value=c.x.stealth;
             numericUpDownConst.Value=c.x.constitution;
             numericUpDownDemo.Value=c.x.demolitions;
             numericUpDownSurv.Value=c.x.survival;
             numericUpDownInt.Value = c.x.intelligence;
             numericUpDownChar.Value = c.x.charisma;
        }
        private void RandButton_Click(object sender, EventArgs e)
        {
            Random randx = new Random();
            

            numericUpDownStrength.Value = randx.Next(21);
            numericUpDownDexterity.Value=randx.Next(21);
            numericUpDownStealth.Value = randx.Next(21);
            numericUpDownConst.Value = randx.Next(21);
            numericUpDownDemo.Value = randx.Next(21);
            numericUpDownSurv.Value = randx.Next(21);
            numericUpDownInt.Value = randx.Next(21);
            numericUpDownChar.Value = randx.Next(21);
        }
        private void Panel1_Click(object sender,EventArgs e)
        {
            if (listBox1.SelectedIndex <= -1)
                return;
            listBox1.SelectedIndex = -1;
            textBoxName.Clear();
            textBoxLname.Clear();
            numericUpDownAge.Value=0;
            //comboBox1.Items.Clear();
            comboBox1.SelectedIndex = -1;
            numericUpDownStrength.Value=0;
            numericUpDownDexterity.Value=0;
            numericUpDownStealth.Value=0;
            numericUpDownConst.Value=0;
            numericUpDownDemo.Value = 0;
            numericUpDownSurv.Value = 0;
            numericUpDownInt.Value = 0;
            numericUpDownChar.Value = 0;
        }

        private void removeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex <= -1)
                return;
            listBox1.Items.RemoveAt(listBox1.SelectedIndex);
            listBox1.SelectedIndex = -1;
            textBoxName.Clear();
            textBoxLname.Clear();
            numericUpDownAge.Value = 0;
            //comboBox1.Items.Clear();
            comboBox1.SelectedIndex = -1;
            numericUpDownStrength.Value = 0;
            numericUpDownDexterity.Value = 0;
            numericUpDownStealth.Value = 0;
            numericUpDownConst.Value = 0;
            numericUpDownDemo.Value = 0;
            numericUpDownSurv.Value = 0;
            numericUpDownInt.Value = 0;
            numericUpDownChar.Value = 0;
        }
        private void updateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex <= -1)
                return;
            Charactor c = (Charactor)listBox1.Items[listBox1.SelectedIndex];
            c.FirstName = textBoxName.Text;
            c.LastName = textBoxLname.Text;
            c.Age = numericUpDownAge.Value;
            //Enum x;

            c.x.Race = (Charactor.CharactorSkills.RaceNames)comboBox1.SelectedIndex;

            c.x.strength = numericUpDownStrength.Value;
            c.x.dexterity = numericUpDownDexterity.Value;
            c.x.stealth = numericUpDownStealth.Value;
            c.x.constitution = numericUpDownConst.Value;
            c.x.demolitions = numericUpDownDemo.Value;
            c.x.survival = numericUpDownSurv.Value;
            c.x.intelligence = numericUpDownInt.Value;
            c.x.charisma = numericUpDownChar.Value;
            listBox1.Items[listBox1.SelectedIndex] = listBox1.Items[listBox1.SelectedIndex];

        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Create an open file dialog
            OpenFileDialog dlg = new OpenFileDialog();
            // Set the filter strings
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.myf)|*.myf";
            // Display the dialog to the user
            if (DialogResult.OK == dlg.ShowDialog())
            {
                // Open a stream for reading
                
                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);
                while (!reader.EndOfStream)
                {
         // To get a filename from the user use the OpenFileDialog class. 
         //  To read the file use StreamReader. 
         //   If you retrieve each whole line as a string use the String class’s 
         // Split method to separate the individual values. 
         //To convert a CharacterRace enumeration value from a string to the enumeration 
         //           value itself use Enum.Parse.


                    String s = reader.ReadLine();

                    Charactor c = new Charactor();

                   // s.Split(new char[] {' ',' ' });
                    string[] words = s.Split(' ');
                    //foreach (string word in words)
                    {
                        c.FirstName = words[0];
                        c.LastName = words[1];
                       c.Age=Decimal.Parse(words[2]);
                       c.x.Race = (Charactor.CharactorSkills.RaceNames)Enum.Parse(typeof(Charactor.CharactorSkills.RaceNames), words[3]);
                        c.x.strength=Decimal.Parse(words[4]);
                        c.x.dexterity=Decimal.Parse(words[5]);
                        c.x.demolitions=Decimal.Parse(words[6]);
                        c.x.stealth=Decimal.Parse(words[7]);
                        c.x.constitution=Decimal.Parse(words[8]);
                        c.x.intelligence=Decimal.Parse(words[9]);
                        c.x.survival=Decimal.Parse(words[10]);
                        c.x.charisma = Decimal.Parse(words[11]);
                    }
                    
                    //c.x.intelligence = s.Split();
                    listBox1.Items.Add(c);
                  
                }

                //textBox1.Text = reader.ReadLine();
                // Close the stream
                reader.Close();
            }
        }
        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Create a size file dialog
            SaveFileDialog dlg = new SaveFileDialog();
            // Set the filter strings
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.myf)|*.myf";
            // Set the default extension
            dlg.DefaultExt = "myf";
            // Display the dialog to the user
            if (DialogResult.OK == dlg.ShowDialog())
            {
                // Open a stream for writing
                System.IO.StreamWriter writer = new System.IO.StreamWriter(dlg.FileName);
                // Write the string
                for (int i = 0; i < listBox1.Items.Count;++i )
                {
                    Charactor c = (Charactor)listBox1.Items[i];
                    String ans = c.FirstName + ' '+c.LastName +' '+ c.Age + ' '+c.x.Race+' '+c.x.strength +' '+ c.x.dexterity +' '+ c.x.demolitions +' '+ c.x.stealth +' '+ c.x.constitution +' '+ c.x.intelligence +' '+ c.x.survival+' '+c.x.charisma;

                    writer.WriteLine(ans);
                }
                    
                // Close the stream
                writer.Close();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label12_Click(object sender, EventArgs e)
        {
            Panel1_Click(null, null);
            listBox1.Items.Clear();
            
        }
    }
}
