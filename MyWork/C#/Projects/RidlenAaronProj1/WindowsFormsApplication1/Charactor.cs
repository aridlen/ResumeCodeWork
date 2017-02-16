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
    public class Charactor
    {

        private string Fname;
        private string Lname;
        
        public CharactorSkills x;
        
        public string FirstName
        {
            get
            {
                return Fname;
            }
            set
            {
                Fname = value;

            }


        }
        public string LastName
        {
            get
            {
                return Lname;
            }
            set
            {
                Lname = value;

            }


        }
     public struct CharactorSkills
        {
           public enum RaceNames
            { Hunter,Scavenger,Soldier,Watchmen,Engineer,Mechanic,Chemist};

           public decimal strength, dexterity, stealth, constitution, intelligence, survival, demolitions, charisma;

           public decimal Charisma
           {
               get { return charisma; }
               set { charisma = value; }
           }

            public decimal Demolitions
            {
                get { return demolitions; }
                set { demolitions = value; }
            }

            public decimal Survival
            {
                get { return survival; }
                set { survival = value; }
            }

            public decimal Intelligence
            {
                get { return intelligence; }
                set { intelligence = value; }
            }

            public decimal Constitution
            {
                get { return constitution; }
                set { constitution = value; }
            }

            public decimal Stealth
            {
                get { return stealth; }
                set { stealth = value; }
            }

            public decimal Dexterity
            {
                get { return dexterity; }
                set { dexterity = value; }
            }

            public decimal Strength
            {
                get { return strength; }
                set { strength = value; }
            }

            RaceNames race;

            public RaceNames Race
            {
                get { return race; }
                set { race = value; }
            }
        }
     
        decimal age;
        
        public decimal Age
        {
            get { return age; }
            set { age = value; }
        }
        public Charactor()
        {

        }
        public override string ToString()
        {
            

            return this.Fname+' '+ this.Lname ;
        }
        
    }
}
