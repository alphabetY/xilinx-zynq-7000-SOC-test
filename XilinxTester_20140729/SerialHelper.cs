using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;
using System.Management;

namespace XilinxTester
{
    class SerialHelper
    {
        private SerialPort serialPort;


        #region Constructors
        public SerialHelper()
        {
            // Default Config
            serialPort = new SerialPort();
            serialPort.ReadTimeout = 3000;
            serialPort.WriteTimeout = 3000;
        }

        public SerialHelper(SerialPortItem spItem)
        {
            serialPort = new SerialPort(spItem.PPortName, spItem.PBaudRate, spItem.PParity,spItem.PDataBits,spItem.PStopBits);
        }
        #endregion

        /// <summary>
        /// Store settings of posts
        /// </summary>
        /// <param name="spItem">Store new paras </param>
        public void setPort(SerialPortItem spItem)
        {
            if (serialPort == null)
            {
                serialPort = new SerialPort(spItem.PPortName, spItem.PBaudRate, spItem.PParity, spItem.PDataBits, spItem.PStopBits);
            }
            else
            {
                if (spItem.PPortName != null)
                {
                    serialPort.PortName = spItem.PPortName;
                }
                serialPort.BaudRate = spItem.PBaudRate;
                serialPort.Parity = spItem.PParity;
                serialPort.DataBits = spItem.PDataBits;
                serialPort.StopBits = spItem.PStopBits;
            }
        }

        public void setReadTimeout(int timeout)
        {
            serialPort.ReadTimeout = timeout;
        }

        /// <summary>
        /// Open SerialPort
        /// </summary>
        /// <returns> If port is opened </returns>
        public bool OpenPort()
        {
            if (!serialPort.IsOpen)
            {
                try { serialPort.Open(); return true; }
                catch (Exception e)
                {
#if DEBUG
                    System.Console.WriteLine(e.ToString());
#endif
                    return false;
                }
            }
            else
            {
                return true;
            }
        }

        public bool ClosePort()
        {
            if (serialPort.IsOpen)
            {
                try { serialPort.Close(); return true; }
                catch (Exception e)
                {
#if DEBUG
                    System.Console.WriteLine(e.ToString());
#endif
                    return false;
                }
            }
            else
            {
                return true;
            }
        }

        /// <summary>
        ///  SendCommand belongs to one thread, All Controls is in this one.
        /// </summary>
        /// <param name="command"> Defined Protocols </param>
        /// <returns> If send successfully </returns>
        public void sendCommand(byte command)
        {
            //System.Console.WriteLine("Sending");
            serialPort.Write(new byte[] { command }, 0, 1);
        }

        /// <summary>
        /// Receive Outputs from serial port and record
        /// Belong to one single thread
        /// </summary>
        /// <returns></returns>
        public byte[] receiveData()
        {
            byte[] buffer = new byte[20];
            try
            {
                serialPort.Read(buffer, 0, 20);
            }
            catch (Exception e)
            {
#if DEBUG
                System.Console.WriteLine(e.ToString());
#endif
                buffer[0] = 0xFF;
                return buffer;
            }
            return buffer;
        }

        public string recviveStringData()
        {
            return serialPort.ReadExisting();
        }

        /// <summary>
        /// Collect Info of Hardwares with MWI
        /// </summary>
        /// <param name="hardType">Hardware Types</param>
        /// <param name="propKey">We need Name here</param>
        /// <returns></returns>
        public static string[] MulGetHardwareInfo(HardwareEnum hardType, string propKey)
        {
            List<string> strs = new List<string>();
            try
            {
                using (ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from " + hardType))
                {
                    var hardInfos = searcher.Get();
                    foreach (var hardInfo in hardInfos)
                    {
                        if (hardInfo.Properties[propKey].Value.ToString().Contains("COM"))
                        {
                            strs.Add(hardInfo.Properties[propKey].Value.ToString());
                        }
 
                    }
                    searcher.Dispose();
                }
                return strs.ToArray();
            }
            catch(Exception e)
            { 
#if DEBUG
                System.Console.WriteLine(e.ToString());
#endif
                return null; 
            }
            finally
            { strs = null; }
        }

        public void DiscardInBuffer()
        {
            serialPort.DiscardInBuffer();
        }

        public void DiscardOutBuffer()
        {
            serialPort.DiscardOutBuffer();
        }
    }


}
