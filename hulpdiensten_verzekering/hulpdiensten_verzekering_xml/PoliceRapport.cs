using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering_xml
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

        public double locationxDouble { get; private set; }

        private int LocationXint = 0;
        private int LocationYint = 0;
        public int LocationX
        {
            get
            {
                return LocationXint;
            }
            set
            {
                string stringvalue = Convert.ToString(value);
                if (stringvalue.Length == 9)
                {
                    string locationx;
                    string locationxAfterKomma = (stringvalue.Remove(0, 3));
                    locationx = Convert.ToString(stringvalue.Remove(3));
                    locationx = locationx + "," + locationxAfterKomma;
                    locationxDouble = Convert.ToDouble(locationx);
                }
                else if (stringvalue.Length == 8)
                {
                    string locationx;
                    string locationxAfterKomma = (stringvalue.Remove(0, 2));
                    locationx = Convert.ToString(stringvalue.Remove(2));
                    locationx = locationx + "," + locationxAfterKomma;
                    locationxDouble = Convert.ToDouble(locationx);
                }
                else if (stringvalue.Length == 7)
                {
                    string locationx;
                    string locationxAfterKomma = (stringvalue.Remove(0, 1));
                    locationx = Convert.ToString(stringvalue.Remove(1));
                    locationx = locationx + "," + locationxAfterKomma;
                    locationxDouble = Convert.ToDouble(locationx);
                }
            }
        }

        public double locationyDouble { get; private set; }

        public int LocationY
        {
            get
            {
                return LocationYint;
            }
            set
            {
                string stringvalue = Convert.ToString(value);
                if (stringvalue.Length == 9)
                {
                    string locationy;
                    string locationyAfterKomma = (stringvalue.Remove(0, 3));
                    locationy = Convert.ToString(stringvalue.Remove(3));
                    locationy = locationy + "." + locationyAfterKomma;
                    locationyDouble = Convert.ToDouble(locationy);
                }
                else if (stringvalue.Length == 8)
                {
                    string locationy;
                    string locationyAfterKomma = (stringvalue.Remove(0, 2));
                    locationy = Convert.ToString(stringvalue.Remove(2));
                    locationy = locationy + "." + locationyAfterKomma;
                    locationyDouble = Convert.ToDouble(locationy);
                }
                else if (stringvalue.Length == 7)
                {
                    string locationy;
                    string locationyAfterKomma = (stringvalue.Remove(0, 1));
                    locationy = Convert.ToString(stringvalue.Remove(1));
                    locationy = locationy + "," + locationyAfterKomma;
                    locationyDouble = Convert.ToDouble(locationy);
                }
            }
        }

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
