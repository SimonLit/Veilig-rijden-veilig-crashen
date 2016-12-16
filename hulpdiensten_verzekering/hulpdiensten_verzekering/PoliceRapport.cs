using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering
{
    class PoliceRapport : Rapport
    {
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
        public int PoliceRapportNumber { get; private set; }

        public string TypeCrash { get; private set; }

        public double LocationX { get; private set; }

        public double LocationY { get; private set; }

        public PoliceRapport(string typeCrash, int victim, DateTime date, double locationX, double locationY, int policeRapportNumber): base (date)
        {
            victimID = victim;
            TypeCrash = typeCrash;
            LocationX = locationX;
            LocationY = locationY;
            PoliceRapportNumber = policeRapportNumber;
        }
    }
}
