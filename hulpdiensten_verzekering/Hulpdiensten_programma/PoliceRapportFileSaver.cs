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
    public partial class PoliceRapportFileSaver : Form
    {
        public PoliceRapportFileSaver()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SaveFileDialog exportToText = new SaveFileDialog();
            exportToText.Filter = "Text Files (*.txt) | *.txt";
            DateTime datum = datetimePolDate.Value.Date + datetimePolTime.Value.TimeOfDay;
            PoliceRapport policerapport = new PoliceRapport(txtPolTypeCrash.Text, Convert.ToInt32(txtPolVicId.Text), datum, Convert.ToInt32(txtPolLocX.Text), Convert.ToInt32(txtPolLocY.Text), Convert.ToInt32(txtPolRapNumber.Text));

            if (exportToText.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    using (StreamWriter streamWriter = new StreamWriter(exportToText.FileName))
                    {                      
                        streamWriter.WriteLine(policerapport.ToString());
                    }
                }
                catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
                catch (UnauthorizedAccessException exception) { MessageBox.Show(exception.Message); }
                catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
                catch (PathTooLongException exception) { MessageBox.Show(exception.Message); }
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void datetimePolDate_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
