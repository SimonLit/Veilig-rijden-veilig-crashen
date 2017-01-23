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

namespace Communication_verzekering
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        AsynchronousSocketListener asynclisten;
        string data_received;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btn_connect_Click(object sender, RoutedEventArgs e)
        {

                BackgroundWorker bw = new BackgroundWorker();

                // this allows our worker to report progress during work
                bw.WorkerReportsProgress = true;

                // what to do in the background thread
                bw.DoWork += new DoWorkEventHandler(
                delegate (object o, DoWorkEventArgs args)
                {
                    asynclisten = new AsynchronousSocketListener();

                    AsynchronousSocketListener.MainSocketListen();
                    BackgroundWorker b = o as BackgroundWorker;

                    // do some simple processing for 10 seconds
                    for (int i = 1; i <= 10; i++)
                    {
                        // report the progress in percent
                        b.ReportProgress(i * 10);
                        Thread.Sleep(1000);
                    }

                });

                // what to do when progress changed (update the progress bar for example)
                bw.ProgressChanged += new ProgressChangedEventHandler(
                delegate (object o, ProgressChangedEventArgs args)
                {
                    data_received = string.Format("{0}% Completed", args.ProgressPercentage);
                });

                // what to do when worker completes its task (notify the user)
                bw.RunWorkerCompleted += new RunWorkerCompletedEventHandler(
                delegate (object o, RunWorkerCompletedEventArgs args)
                {
                    data_received = "Finished!";
                });

                bw.RunWorkerAsync();
                //TcpServer server = new TcpServer(5555);
                asynclisten = new AsynchronousSocketListener();

                AsynchronousSocketListener.MainSocketListen();
            
        }
    }
}
