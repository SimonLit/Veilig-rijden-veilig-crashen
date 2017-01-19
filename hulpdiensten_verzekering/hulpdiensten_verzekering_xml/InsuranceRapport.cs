using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering_xml
{
    public class InsuranceRapport : Rapport
    {
        public string InsuranceCompany { get; private set; }

        private int victimID;
        public override int VictimID
        {
            get
            {
                return victimID;
            }
            set
            {
                string stringvalue = Convert.ToString(value);
                if(stringvalue.Length == 9)
                {
                    int insuranceCompanyId;
                    victimID = Int32.Parse(stringvalue.Remove(0, 3));
                    insuranceCompanyId = Int32.Parse(stringvalue.Remove(3));
                    if(insuranceCompanyId == 111)
                    {
                        InsuranceCompany = "Ditzo";
                    }
                    else if(insuranceCompanyId == 112)
                    {
                        InsuranceCompany = "InShared";
                    }
                    else if(insuranceCompanyId == 113)
                    {
                        InsuranceCompany = "Univé";
                    }
                    else if(insuranceCompanyId == 114)
                    {
                        InsuranceCompany = "Centraal beheer Achmea";
                    }
                    else if(insuranceCompanyId == 115)
                    {
                        InsuranceCompany = "FBTO";
                    }
                }
            }
        }

        public int InsuranceRapportNumber { get; private set; }

        public string InsuranceDetails { get; private set; }

        public int ClaimNr { get;  set; }

        public InsuranceRapport(int InputVictimId, DateTime date, int insuranceRapportNumber, string insuranceDetails, int claimNr): base (date)
        {
            VictimID = InputVictimId;
            InsuranceDetails = insuranceDetails;
            InsuranceRapportNumber = insuranceRapportNumber;
            ClaimNr = claimNr;
        }

        public bool SaveFile(int InsuranceRapportNumber)
        {
            return true;
        }
        public override string ToString()
        {
            string victumid = "";
            if (InsuranceCompany == "Ditzo")
            {
                victumid = "111";
            }
            else if (InsuranceCompany == "InShared")
            {
                victumid = "112";
            }
            else if (InsuranceCompany == "Univé")
            {
                victumid = "113";
            }
            else if (InsuranceCompany == "Centraal beheer Achmea")
            {
                victumid = "114";  
            }
            else if (InsuranceCompany == "FBTO")
            {
                victumid = "115";
            }
            victumid = victumid + Convert.ToString(victimID);
            return string.Format("{0}, " + base.ToString() + ", {1}, {2}, {3}", victumid, InsuranceRapportNumber, InsuranceDetails, ClaimNr);
        }
    }
}
