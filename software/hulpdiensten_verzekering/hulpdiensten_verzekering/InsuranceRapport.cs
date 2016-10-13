using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering
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
            }
        }

        public int insuranceRapportNumber { get; private set; }

        public string InsuranceDetails { get; private set; }

        public int ClaimNr { get; private set; }
    }
}
