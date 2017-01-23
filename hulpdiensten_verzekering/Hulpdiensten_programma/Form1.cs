using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Hulpdiensten_programma
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog importFromText = new OpenFileDialog();
            importFromText.Filter = "Text Files (*.txt) | *.txt";
            if (importFromText.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    using (StreamReader streamReader = new StreamReader(importFromText.FileName))
                    {
                        while (!streamReader.EndOfStream)
                        {
                            string insuranceRapportString = streamReader.ReadLine();
                            InsuranceRapport insurancerapport = InsuranceRapportExtractor.CreateNewInsuranceRapportFromstring(insuranceRapportString);
                            InsuranceFileViewerForm viewInsuranceRapport = new InsuranceFileViewerForm();
                            viewInsuranceRapport.lblInsClaimNbr.Text = Convert.ToString(insurancerapport.ClaimNr);
                            viewInsuranceRapport.lblInsComp.Text = insurancerapport.InsuranceCompany;
                            viewInsuranceRapport.lblInsDate.Text = Convert.ToString(insurancerapport.Date);
                            viewInsuranceRapport.lblInsInsDet.Text = insurancerapport.InsuranceDetails;
                            viewInsuranceRapport.lblInsRapNumber.Text = Convert.ToString(insurancerapport.InsuranceRapportNumber);
                            viewInsuranceRapport.lblInsVictId.Text = Convert.ToString(insurancerapport.VictimID);
                            viewInsuranceRapport.ShowDialog();
                        }
                    }
                    
                }
                catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
                catch (FileNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (ArgumentOutOfRangeException exception) { MessageBox.Show(exception.Message); }
            }
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            DateTime datum = new DateTime(2015, 6, 26);
            PoliceRapport iets = new PoliceRapport("frontaal", 523697845, datum, 10, 20, 56);
            
        }

        private void btnSaveInsFile_Click(object sender, EventArgs e)
        {
            InsuranceFileSaver saveInsuranceRapport = new InsuranceFileSaver();
            saveInsuranceRapport.ShowDialog();
        }

        private void btnOpenPolRap_Click(object sender, EventArgs e)
        {
            OpenFileDialog importFromText = new OpenFileDialog();
            importFromText.Filter = "Text Files (*.txt) | *.txt";
            if (importFromText.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    using (StreamReader streamReader = new StreamReader(importFromText.FileName))
                    {
                        while (!streamReader.EndOfStream)
                        {
                            string policeRapportString = streamReader.ReadLine();
                            PoliceRapport policerapport = PoliceRapportExtractor.CreateNewPoliceRapportFromstring(policeRapportString);
                            PoliceFileViewerForm viewPoliceRapport = new PoliceFileViewerForm();
                            viewPoliceRapport.lblPolRapNumber.Text = Convert.ToString(policerapport.PoliceRapportNumber);
                            viewPoliceRapport.lblPolVictId.Text = Convert.ToString(policerapport.VictimID);
                            viewPoliceRapport.lblPolDate.Text = Convert.ToString(policerapport.Date);
                            viewPoliceRapport.lblPolCrashType.Text = policerapport.TypeCrash;
                            viewPoliceRapport.lblPolLocX.Text = Convert.ToString(policerapport.LocationX);
                            viewPoliceRapport.lblPolLocY.Text = Convert.ToString(policerapport.LocationY);
                            viewPoliceRapport.ShowDialog();

                        }
                    }

                }
                catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
                catch (FileNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (ArgumentOutOfRangeException exception) { MessageBox.Show(exception.Message); }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            PoliceRapportFileSaver savePoliceRapport = new PoliceRapportFileSaver();
            savePoliceRapport.ShowDialog();
        }
    }
}
