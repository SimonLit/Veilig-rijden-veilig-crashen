using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hulpdiensten_verzekering
{
    public abstract class Rapport : IRapport
    {
        public DateTime Date { get; set; }

        public abstract int VictimID { get; set; }

        public Rapport(DateTime date)
        {
            Date = date;
        }
        public override string ToString()
        {
            string datum = Convert.ToString(Date.Date);
            return datum;
            
        }
    }
}
