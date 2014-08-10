using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows;

namespace XilinxTester
{
    public class LogHelper
    {
        private string logPath;
        private StreamWriter streamWriter;

        public LogHelper(string logPath)
        {
            this.logPath = logPath;
//            if (!File.Exists(logPath))
//            {
//                try
//                {
//                    File.Create(logPath);
//                }
//                catch (Exception e)
//                {
//                    MessageBox.Show("无法创建日志文件，请检查");
//#if DEBUG
//                    System.Console.WriteLine(e.ToString());
//#endif
//                    return;
//                }
//            }

            // Create Log file definatelly, Append is true
            streamWriter = new StreamWriter(logPath,true);
            streamWriter.AutoFlush = true;
            
        }

        public void InLog(String message) {
            
            DateTime now = DateTime.Now;
            streamWriter.WriteLine(now.Year + "-" 
                + now.Month + "-" 
                + now.Day + " " 
                + now.Hour + ":"
                + now.Minute + ":"
                + now.Second + "'"
                + now.Millisecond + "\" ："
                + message);
        }

        static public void OpenLog(string program, string logPath)
        {
            System.Diagnostics.Process.Start("notepad.exe", logPath);
        }

        public void FlushLog()
        {
            streamWriter.Flush();
        }

        public void CloseLog()
        {
            
            streamWriter.Close();
        }

        public void OpenLog()
        {
            streamWriter.Close();
            streamWriter = new StreamWriter(logPath, true);
            streamWriter.AutoFlush = true;
        }

    }
}
