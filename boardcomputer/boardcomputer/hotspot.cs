using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace boardcomputer
{
    class Hotspot
    {
        public string SSID { get; set; }
        public string KEY { get; set; }

        public Hotspot(string ssid, string key)
        {
            if(ssid == null)
            {
                throw new ArgumentNullException("Argument ssid is null.");
            }
            if(ssid == "")
            {
                throw new ArgumentException("The argument ssid is not allowed to be empty.");
            }
            if(ssid.Length < 6)
            {
                throw new ArgumentOutOfRangeException("The argument ssid needs to be atleast 6 char long.");
            }
            if(key == null)
            {
                throw new ArgumentNullException("Argument key is null.");
            }
            if(key == "")
            {
                throw new ArgumentException("The argument key is not allowed to be empty.");
            }
            if(key.Length <6)
            {
                throw new ArgumentOutOfRangeException("The argument ket needs to be atleast 6 char long.");
            }
            SSID = ssid;
            KEY = key;        
        }

        public void startHotSpot()
        {
            Zedfi_Hotspot(SSID, KEY, true);
        }
        public void stopHotSpot()
        {
            Zedfi_Hotspot(null, null, false);
        }

        private void Zedfi_Hotspot(string ssid, string key, bool status)
        {
            ProcessStartInfo processStartInfo = new ProcessStartInfo("cmd.exe");
            processStartInfo.RedirectStandardInput = true;
            processStartInfo.RedirectStandardOutput = true;
            processStartInfo.CreateNoWindow = true;
            processStartInfo.UseShellExecute = false;
            Process process = Process.Start(processStartInfo);

            if (process != null)
            {
                if (status)
                {
                    process.StandardInput.WriteLine("netsh wlan set hostednetwork mode=allow ssid = " + ssid + " key = " + key);
                    process.StandardInput.WriteLine("netsh wlan start hosted network");
                    process.StandardInput.Close();
                }
                else
                {
                    process.StandardInput.WriteLine("netsh wlan stop hostednetwork");
                    process.StandardInput.Close();
                }
            }
        }

    }
}
