using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hulpdiensten_programma
{
    class PoliceRapportExtractor
    {
        public static PoliceRapport CreateNewPoliceRapportFromstring(string policeRapport)
        {
            string TypeCrash = PoliceRapportExtractor.ExtractTypeCrash(policeRapport);
            int VictimNumber = PoliceRapportExtractor.ExtractVictimNumber(policeRapport);
            DateTime Date = PoliceRapportExtractor.ExtractDate(policeRapport);
            int LocationX = PoliceRapportExtractor.ExtractLocationX(policeRapport);
            int LocationY = PoliceRapportExtractor.ExtractLocationY(policeRapport);
            int PoliceRapportNumber = PoliceRapportExtractor.ExtractPoliceRapportNumber(policeRapport);
            PoliceRapport newinsurancerapport = new PoliceRapport(TypeCrash, VictimNumber, Date, LocationX, LocationY, PoliceRapportNumber);
            return newinsurancerapport;
        }


        public static string ExtractTypeCrash(string policeRapport)
        {
            int endingIndex = policeRapport.IndexOf(",");
            return policeRapport.Substring(0, endingIndex);
        }

        public static int ExtractVictimNumber(string policeRapport)
        {
            string newString = Trimmer(policeRapport, 1);
            int endingIndex = newString.IndexOf(", ");
            string victimNumber = newString.Substring(0, endingIndex);
            return Convert.ToInt32(victimNumber);
        }
        public static DateTime ExtractDate(string policeRapport)
        {
            //31 - 12 - 2008 23:00:59
            string newString = Trimmer(policeRapport, 2);
            int endingIndex = newString.IndexOf(", ");
            string dateString = newString.Substring(0, endingIndex);
            return Convert.ToDateTime(dateString);
        }

        public static int ExtractLocationX(string policeRapport)
        {
            string newString = Trimmer(policeRapport, 3);
            int endingIndex = newString.IndexOf(", ");
            string locationX = newString.Substring(0, endingIndex);
            return Convert.ToInt32(locationX);
        }

        public static int ExtractLocationY(string policeRapport)
        {
            string newString = Trimmer(policeRapport, 4);
            int endingIndex = newString.IndexOf(", ");
            string locationY = newString.Substring(0, endingIndex);
            return Convert.ToInt32(locationY);
        }

        public static int ExtractPoliceRapportNumber(string policeRapport)
        {
            string newString = Trimmer(policeRapport, 5);
            return Convert.ToInt32(newString);
        }

        private static string Trimmer(string stringToTrim, int amountOfTimes)
        {
            //This method trims off certain parts of a string that has been given to it. It trims off 'blocks' that end with a ",".
            string newString = "";
            newString = stringToTrim;
            for (int i = 0; i < amountOfTimes; i++)
            {
                int endingIndexToRemove = newString.IndexOf(",");
                newString = newString.Remove(0, endingIndexToRemove + 2);
            }

            return newString;
        }
    }
}
