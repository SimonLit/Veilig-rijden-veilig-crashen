using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Collections;
using Microsoft.Maps.MapControl.WPF;


namespace hulpdiensten_verzekering_xml
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Administration administration;
        public MainWindow()
        {
            administration = new Administration();
            try
            {
                string[] fileEntries = Directory.GetFiles(@"C:\\Users\\Gebruiker\\Documents\\Mobile dash\\InsuranceRapport");
                foreach (string f in fileEntries)
                {
                    using (StreamReader streamReader = new StreamReader(f))
                    {
                        while (!streamReader.EndOfStream)
                        {
                            string insuranceRapportString = streamReader.ReadLine();
                            InsuranceRapport insurancerapport = InsuranceRapportExtractor.CreateNewInsuranceRapportFromstring(insuranceRapportString);
                            administration.AddInsuranceRapport(insurancerapport);
                        }
                    }

                }
            }
            catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
            catch (FileNotFoundException exception) { MessageBox.Show(exception.Message); }
            catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
            catch (ArgumentOutOfRangeException exception) { MessageBox.Show(exception.Message); }
            try
            {
                string[] fileEntries = Directory.GetFiles(@"C:\\Users\\Gebruiker\\Documents\\Mobile dash\\PoliceRapport");
                foreach (string f in fileEntries)
                {
                    using (StreamReader streamReader = new StreamReader(f))
                    {
                        while (!streamReader.EndOfStream)
                        {
                            string policeRapportString = streamReader.ReadLine();
                            PoliceRapport policerapport = PoliceRapportExtractor.CreateNewPoliceRapportFromstring(policeRapportString);
                            administration.AddPoliceRapport(policerapport);
                        }
                    }

                }
            }
            catch (ArgumentNullException exception) { MessageBox.Show(exception.Message); }
            catch (FileNotFoundException exception) { MessageBox.Show(exception.Message); }
            catch (DirectoryNotFoundException exception) { MessageBox.Show(exception.Message); }
            catch (ArgumentOutOfRangeException exception) { MessageBox.Show(exception.Message); }
            InitializeComponent();
            myMap.Center = new Location(51.451793, 5.481469);
            myMap.ZoomLevel = 16;
            foreach (PoliceRapport p in administration.PoliceRapports) {
                listBox.Items.Add(p.PoliceRapportNumber);
            }

        }

        private void listBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            PoliceRapport policeRapport;
            policeRapport = administration.FindPoliceRapport(Convert.ToInt32(listBox.SelectedItem.ToString()));
            myMap.Center = new Location(policeRapport.locationxDouble, policeRapport.locationyDouble);
        }
    }
}
