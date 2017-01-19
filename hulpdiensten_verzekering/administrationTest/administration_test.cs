using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using hulpdiensten_verzekering_xml;

namespace administrationTest
{
    [TestClass]
    public class administration_test
    {
        [TestMethod]
        public void AddNormalPoliceRapport()
        {
            Administration admin = new Administration();
            DateTime datum = new DateTime();
            datum = DateTime.Now;
            PoliceRapport policerapport = new PoliceRapport("rechts achter", 6666666, datum, 88765465, 8775098, 67);
            admin.AddPoliceRapport(policerapport);
            Assert.AreEqual(policerapport, admin.FindPoliceRapport(67));
        }

        [TestMethod]
        public void FindNonExcistingPoliceRapport()
        {
            Administration admin = new Administration();
            DateTime datum = new DateTime();
            datum = DateTime.Now;
            PoliceRapport policerapport = new PoliceRapport("rechts achter", 6666666, datum, 88765465, 8775098, 67);
            admin.AddPoliceRapport(policerapport);
            Assert.AreEqual(null, admin.FindPoliceRapport(77));
        }

        [TestMethod]
        public void AddNormalInsuranceRapport()
        {
            Administration admin = new Administration();
            DateTime datum = new DateTime();
            datum = DateTime.Now;
            InsuranceRapport insurancerapport = new InsuranceRapport(112883899, datum, 23, "dik hard gecrasht", 54);
            admin.AddInsuranceRapport(insurancerapport);
            Assert.AreEqual(insurancerapport, admin.FindInsuranceRapport(23));
        }

        [TestMethod]
        public void FindNonExcistingInsuranceRapport()
        {
            Administration admin = new Administration();
            DateTime datum = new DateTime();
            datum = DateTime.Now;
            InsuranceRapport insurancerapport = new InsuranceRapport(112883899, datum, 23, "dik hard gecrasht", 54);
            admin.AddInsuranceRapport(insurancerapport);
            Assert.AreEqual(null, admin.FindInsuranceRapport(22));
        }

        [TestMethod]
        public void SplitStringNormal()
        {
            Administration admin = new Administration();
            DateTime datum = new DateTime();
            datum = DateTime.Now;
            InsuranceRapport insurancerapport = new InsuranceRapport(112883899, datum, 23, "dik hard gecrasht", 54);
            PoliceRapport policerapport = new PoliceRapport("rechts achter", 6666666, datum, 88765465, 8775098, 67);
            policerapport = PoliceRapportExtractor.CreateNewPoliceRapportFromstring("dsrf, 22578, 25-05-1998 03:16:20, 84546780, -90123456, 43");
            insurancerapport = InsuranceRapportExtractor.CreateNewInsuranceRapportFromstring("0, 25 - 12 - 2016 00:00:00, 554, Schuld van de bestuurder, 13");
            admin.SplitStringsRapport("dsrf, 22578, 25-05-1998 03:16:20, 84546780, -90123456, 43,0, 25-12-2016 00:00:00, 554, Schuld van de bestuurder, 13");
            Assert.AreEqual(insurancerapport.InsuranceRapportNumber, admin.FindInsuranceRapport(554).InsuranceRapportNumber);
            Assert.AreEqual(policerapport.PoliceRapportNumber, admin.FindPoliceRapport(43).PoliceRapportNumber);
        }

    }
}
