using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hulpdiensten_programma
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

        public int LocationX { get; private set; }

        public int LocationY { get; private set; }

        public PoliceRapport(string typeCrash, int victim, DateTime date, int locationX, int locationY, int policeRapportNumber): base (date)
        {
            victimID = victim;
            TypeCrash = typeCrash;
            LocationX = locationX;
            LocationY = locationY;
            PoliceRapportNumber = policeRapportNumber;
        }

        public override string ToString()
        {
            return string.Format("{0}, {1}, " + base.ToString() + ", {2}, {3}, {4}", TypeCrash, VictimID, LocationX, LocationY, PoliceRapportNumber);
        }
    }
}
