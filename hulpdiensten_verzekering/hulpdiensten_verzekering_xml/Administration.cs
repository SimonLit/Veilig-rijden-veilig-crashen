using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering_xml
{
    public class Administration
    {
        public List<PoliceRapport> PoliceRapports { get; private set; }
        public List<InsuranceRapport> InsuranceRapports { get; private set; }

        public Administration()
        {
            PoliceRapports = new List<PoliceRapport>();
            InsuranceRapports = new List<InsuranceRapport>();
        }
        
        public void AddPoliceRapport(PoliceRapport rapport)
        {
            PoliceRapports.Add(rapport);
        }

        public void AddInsuranceRapport(InsuranceRapport rapport)
        {
            InsuranceRapports.Add(rapport);
        }

        public void SplitStringsRapport(string joinedstring)
        {
            int count = 0;
            int split = 0;
            for (int i = 0; i < joinedstring.Length; i++)
            {
                if (joinedstring[i] == ',')
                {
                    count++;
                    if (count == 6)
                    {
                        split = i;
                    }
                }
            }
            if(split == 0)
            { throw new ArgumentOutOfRangeException("could not split string"); }
            string policeRapportString = joinedstring.Substring(0, split);
            string insuranceRapportString = joinedstring.Substring((split + 1), (joinedstring.Length - (split+1)));

            PoliceRapport policerapport = PoliceRapportExtractor.CreateNewPoliceRapportFromstring(policeRapportString);
            AddPoliceRapport(policerapport);
            InsuranceRapport insurancerapport = InsuranceRapportExtractor.CreateNewInsuranceRapportFromstring(insuranceRapportString);
            AddInsuranceRapport(insurancerapport);
        }

        public PoliceRapport FindPoliceRapport(int policeRapportNumber)
        {
            PoliceRapport policeRapportToReturn = null;

            if (policeRapportNumber < 0)
            {
                throw new ArgumentOutOfRangeException("Could not find a police rapport with that number");
            }
            foreach (PoliceRapport element in PoliceRapports)
            {
                if (element.PoliceRapportNumber == policeRapportNumber)
                {
                    policeRapportToReturn = element;
                    break;
                }
            }


            return policeRapportToReturn;
        }

        public InsuranceRapport FindInsuranceRapport(int insuranceRapportNumber)
        {
            InsuranceRapport insuranceRapportToReturn = null;

            if (insuranceRapportNumber < 0)
            {
                throw new ArgumentOutOfRangeException("Could not find a insurance rapport with that number");
            }
            foreach (InsuranceRapport element in InsuranceRapports)
            {
                if (element.InsuranceRapportNumber == insuranceRapportNumber)
                {
                    insuranceRapportToReturn = element;
                    break;
                }
            }


            return insuranceRapportToReturn;
        }


    }
}
