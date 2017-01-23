using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.ComponentModel;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Net;
using System.Threading;
using System.Net.Sockets;
using System.IO.Packaging;
using System.Collections;
using System.Windows.Threading;
using Microsoft.Maps.MapControl.WPF;


namespace hulpdiensten_verzekering_xml
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool connected = false;
        Administration administration;
        string data_received;
        
        //Server myServer = new Server();
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
                string[] fileEntries = Directory.GetFiles(@"C:\Users\Gebruiker\Documents\Mobile dash\PoliceRapport", "*.txt");
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
            foreach (InsuranceRapport i in administration.InsuranceRapports)
            {
                listBox_insurance.Items.Add(i.InsuranceRapportNumber);
            }

        }

        private void listBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            PoliceRapport policeRapport;
            policeRapport = administration.FindPoliceRapport(Convert.ToInt32(listBox.SelectedItem.ToString()));
            myMap.Center = new Location(policeRapport.locationxDouble, policeRapport.locationyDouble);
        }


        private void dtClockTime_Tick(object sender, EventArgs e)
        {

        }

        private void listBox_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            ___Grid2_.Visibility = Visibility.Visible;
            PoliceRapport policeRapport;
            policeRapport = administration.FindPoliceRapport(Convert.ToInt32(listBox.SelectedItem.ToString()));
            lbl_police_date.Content = Convert.ToString(policeRapport.Date);
            lbl_police_rapport_number.Content = Convert.ToString(policeRapport.PoliceRapportNumber);
            lbl_police_x.Content = Convert.ToString(policeRapport.locationxDouble);
            lbl_police_y.Content = Convert.ToString(policeRapport.locationyDouble);
            lbl_police_detail.Content = policeRapport.TypeCrash;
            btn_remove_image_police.IsEnabled = true;
        }

        private void listBox_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            
        }

        private void listBox_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void btn_remove_image_police_Click(object sender, RoutedEventArgs e)
        {
            ___Grid2_.Visibility = Visibility.Hidden;
            ___Grid3_.Visibility = Visibility.Hidden;
            btn_remove_image_police.IsEnabled = false;
        }

        private void listBox_insurance_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            ___Grid3_.Visibility = Visibility.Visible;
            InsuranceRapport insuranceRapport;
            insuranceRapport = administration.FindInsuranceRapport(Convert.ToInt32(listBox_insurance.SelectedItem.ToString()));
            lbl_insurance_date.Content = Convert.ToString(insuranceRapport.Date);
            lbl_insurance_rapport_number.Content = Convert.ToString(insuranceRapport.InsuranceRapportNumber);
            lbl_claim_nr.Content = Convert.ToString(insuranceRapport.ClaimNr);
            lbl_details.Content = insuranceRapport.InsuranceDetails;
            lbl_victim_id.Content = Convert.ToString(insuranceRapport.VictimID);
            btn_remove_image_police.IsEnabled = true;
        }

        private void button_connect_Click(object sender, RoutedEventArgs e)
        {

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                foreach (string file in Directory.EnumerateFiles(@"C:\Users\Gebruiker\Documents\Visual Studio 2015\Projects\Communication_verzekering\Communication_verzekering\bin\debug", "*.txt"))
                {
                    string contents = File.ReadAllText(file);
                    if(contents.Substring(10, 3) == "PDA")
                    {
                        DateTime datum = new DateTime();
                        datum = DateTime.Now;
                        InsuranceRapport insurancerapport = new InsuranceRapport(112883899, datum, 23, "dik hard gecrasht", 54);
                        insurancerapport = administration.FindInsuranceRapport(Convert.ToInt32(contents.Substring(0, 9)));
                        insurancerapport.ClaimNr = insurancerapport.ClaimNr + Convert.ToInt32(contents.Substring(18, contents.Length - 18));
                    }
                    if (contents.Substring(10, 3) == "DAT")
                    {
                        DateTime datum = new DateTime();
                        datum = DateTime.Now;
                        int victimid = Convert.ToInt32(contents.Substring(0, 9));
                        int count = 0;
                        int i = 0;
                        string crashdata = "";
                        string contenthalfway = "";
                        foreach (char c in contents)
                        {

                            if (c == '|') 
                            { count++;
                                if (count == 8)
                                {
                                    crashdata = contents.Substring(14, i - 14);
                                    contenthalfway = contents.Substring(i + 1, (contents.Length - i - 1));
                                }
                                /*if (count == 9)
                                {
                                    
                                }*/
                            };
                            i++;
                        }
                        int claimnr = Convert.ToInt32(contenthalfway.Substring(4, contenthalfway.IndexOf('|') - 4));
                        contenthalfway = contenthalfway.Substring(10, contenthalfway.Length - 10);
                        double xloc = Convert.ToDouble(contenthalfway.Substring(0, contenthalfway.IndexOf(':')));
                        int xgps = Convert.ToInt32(xloc);
                        contenthalfway = contenthalfway.Substring(contenthalfway.IndexOf(':')+1, contenthalfway.Length - contenthalfway.IndexOf(':') - 1);
                        double yloc = Convert.ToDouble(contenthalfway.Substring(0, contenthalfway.Length-2));
                        int ygps = Convert.ToInt32(yloc);
                        contenthalfway = contenthalfway.Substring(0, contenthalfway.Length - 4);
                        Random rand = new Random();
                        InsuranceRapport insurancerapport = new InsuranceRapport(victimid, datum, rand.Next(142034), crashdata, rand.Next(142034));
                        PoliceRapport policerapoort = new PoliceRapport(crashdata, victimid, datum, xgps, ygps, rand.Next(142034));
                        //insurancerapport = administration.FindInsuranceRapport(Convert.ToInt32(contents.Substring(0, 9)));
                        administration.AddPoliceRapport(policerapoort);
                        administration.AddInsuranceRapport(insurancerapport);
                        listBox.Items.Clear();
                        foreach (PoliceRapport p in administration.PoliceRapports)
                        {
                            listBox.Items.Add(p.PoliceRapportNumber);
                            
                        }
                        listBox_insurance.Items.Clear();
                        foreach (InsuranceRapport z in administration.InsuranceRapports)
                        {
                            listBox_insurance.Items.Add(z.InsuranceRapportNumber);
                        }

                    }

                    //administration.SplitStringsRapport(contents);
                }
            }
            catch(Exception zzz)
            {
                Console.WriteLine(zzz.ToString());
            }
        }
    }
}
