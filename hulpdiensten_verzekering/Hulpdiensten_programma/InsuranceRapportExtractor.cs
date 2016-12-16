using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hulpdiensten_programma
{
    class InsuranceRapportExtractor
    {
        public static InsuranceRapport CreateNewInsuranceRapportFromstring(string insuranceRapport)
        {
            int VictimId = InsuranceRapportExtractor.ExtractVictimId(insuranceRapport);
            DateTime Date = InsuranceRapportExtractor.ExtractDate(insuranceRapport);
            int InsuranceRapportNumber = InsuranceRapportExtractor.ExtractInsuranceRapportNumber(insuranceRapport);
            string InsuranceDetails = InsuranceRapportExtractor.ExtractInsuranceDetails(insuranceRapport);
            int ClaimNr = InsuranceRapportExtractor.ExtractClaimNumber(insuranceRapport);
            InsuranceRapport newinsurancerapport = new InsuranceRapport(VictimId, Date, InsuranceRapportNumber, InsuranceDetails, ClaimNr);
            return newinsurancerapport;
        }


        public static int ExtractVictimId(string insuranceRapport)
        {
            int endingIndex = insuranceRapport.IndexOf(",");
            string victimIdString = insuranceRapport.Substring(0, endingIndex);
            return Convert.ToInt32(victimIdString);
        }

        public static DateTime ExtractDate(string insuranceRapport)
        {
            //31 - 12 - 2008 23:00:59
            string newString = Trimmer(insuranceRapport, 1);
            int endingIndex = newString.IndexOf(", ");
            string dateString = newString.Substring(0, endingIndex);
            dateString = dateString.Remove(0, 1);
            return Convert.ToDateTime(dateString);
       }

        public static int ExtractInsuranceRapportNumber(string insuranceRapport)
        {
            string newString = Trimmer(insuranceRapport, 2);
            int endingIndex = newString.IndexOf(", ");
            string insuranceRapportNumber = newString.Substring(0, endingIndex);
            return Convert.ToInt32(insuranceRapportNumber);
        }

        public static string ExtractInsuranceDetails(string insuranceRapport)
        {
                string newString = Trimmer(insuranceRapport, 3);
                int endingIndex = newString.IndexOf(", ");
                return newString.Substring(0, endingIndex);
        }

        public static int ExtractClaimNumber(string insuranceRapport)
        {
            string newString = Trimmer(insuranceRapport, 4);
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
