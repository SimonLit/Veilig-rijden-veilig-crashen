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
    public partial class InsuranceFileSaver : Form
    {
        public InsuranceFileSaver()
        {
            InitializeComponent();
        }

        private void InsuranceFileSaver_Load(object sender, EventArgs e)
        {

        }

        private void btnSaveInsRap_Click(object sender, EventArgs e)
        {
            SaveFileDialog exportToText = new SaveFileDialog();
            exportToText.Filter = "Text Files (*.txt) | *.txt";
            DateTime datum = datetimeInsDate.Value.Date + datetimeInsTime.Value.TimeOfDay;
            InsuranceRapport insurancerapport = new InsuranceRapport(Convert.ToInt32(txtInsVicId.Text), datum, Convert.ToInt32(txtInsRapNumber.Text), txtInsDetails.Text, Convert.ToInt32(txtInsClaimNbr.Text));

            if (exportToText.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    using (StreamWriter streamWriter = new StreamWriter(exportToText.FileName))
                    {
                        streamWriter.WriteLine(insurancerapport.ToString());
                    }
                }
                catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
                catch (UnauthorizedAccessException exception) { MessageBox.Show(exception.Message); }
                catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (PathTooLongException exception) { MessageBox.Show(exception.Message); }
            }
        }
    }
}
