using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace boardcomputer_project
{
    class TCPControl
    {
        public IPAddress ServerIP;
        public int serverport;
        public TcpListener Server;

        private Thread commthread;
        public bool islistinging;

        private TcpClient client;
        private StreamReader clientData;

        public TCPControl()
        {
            ServerIP = new IPAddress(long.Parse("192.168.1.253"));
            serverport = 64555;
            Server = new TcpListener(ServerIP, serverport);
            islistinging = true;
        }

        public void StartServer()
        {
            Server.Start();
            commthread = new Thread(new ThreadStart(Listening));
            commthread.Start();
        }
        private void Listening()
        {
            do
            {
                //Accept incoming connections
                if(Server.Pending())
                {
                    client = Server.AcceptTcpClient();
                    clientData = new StreamReader(client.GetStream());
                }

                try
                {
                    
                

                }catch(Exception e)
                {
                    // Do something usefull
                }

                Thread.Sleep(100);
            } while (islistinging == true);   
        }
        public void MessageReceived(sender TCPControl, Data string)
        {

        }
    }
}
