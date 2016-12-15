using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace boardcomputer
{
    class boardcomputer
    {
        static ConsoleEventDelegate handler;   // Keeps it from getting garbage collected
        private delegate bool ConsoleEventDelegate(int eventType);
        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool SetConsoleCtrlHandler(ConsoleEventDelegate callback, bool add);
        private static Hotspot hotspotboardcomputer;

        static void Main(string[] args)
        {
            if (IsAdmin() == false)
            {
                RestartElevated();
                Environment.Exit(0);
            }
            handler = new ConsoleEventDelegate(ConsoleEventCallback);
            SetConsoleCtrlHandler(handler, true);
            createHotspot();
            Console.WriteLine("Press enter to start the hotsport.");
            Console.ReadKey();
            hotspotboardcomputer.startHotSpot();
            startUpServer();
            Console.WriteLine("Hotspot started, press enter to stop the hotspot.");
            Console.ReadKey();
            hotspotboardcomputer.stopHotSpot();
            Console.WriteLine("Hotspot stopped.");
            Console.ReadLine();
        }
        public static bool IsAdmin()
        {
            WindowsIdentity id = WindowsIdentity.GetCurrent();
            WindowsPrincipal p = new WindowsPrincipal(id);
            return p.IsInRole(WindowsBuiltInRole.Administrator);
        }
        public static void RestartElevated()
        {
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.UseShellExecute = true;
            startInfo.CreateNoWindow = true;
            startInfo.WorkingDirectory = Environment.CurrentDirectory;
            startInfo.FileName = System.Reflection.Assembly.GetExecutingAssembly().Location;
            startInfo.Verb = "runas";
            try
            {
                Process p = Process.Start(startInfo);
            }
            catch (ObjectDisposedException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (Win32Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
        static bool ConsoleEventCallback(int eventType)
        {    
            if (eventType == 2)
            {
                hotspotboardcomputer.stopHotSpot();
                Console.WriteLine("Console window closing, death imminent");
            }
            return false;
        }
        public static void createHotspot()
        {
            string namenetwork = "";
            string keynetwork = "";
            Console.WriteLine("Enter ssid name and press enter : ");
            namenetwork = Console.ReadLine();
            Console.WriteLine("Enter key to network and press enter : ");
            keynetwork = Console.ReadLine();
            try
            {
                hotspotboardcomputer = new Hotspot(namenetwork, keynetwork);
            }catch(ArgumentNullException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (ArgumentOutOfRangeException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (ArgumentException e)
            {
                Console.WriteLine(e.Message);
            }
        }
        public static void startUpServer()
        {
            transferserver server = new transferserver();
            server.SetupServer("192.168.173.1");
        }
    }
}
