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
using System.Threading;


namespace XilinxTester
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        /* testItem Definations
         * 0: Beats
         * 1: CPU
         * 2: Cache
         * 3: FPU
         * 4: ALU
         * 5: Memory
         * 6: Periferal
         * 7: PS
         */ 
        static private bool[] testItems;    // Store test items
        static private bool isTesting;      // Indicate if is in testing
        static private int[] testTimes;     // Record times needed by each testing
        static private bool isByTimes;      // False when by pencentage
        
        // Just In UI thread
        private string strConfigPath;       // Filepath of configFile 
        private SerialHelper serialHelper;  // Operations about ports encapsulated in 
        private ConfigWindow configWindow;  // ConfigWindow
        //private Thread sendThread;        // Record sendThread
        //private Thread recvThread;        // Record recvThread
        private Thread sendRecvThread;      // Record sendRecvThread    
        private LogHelper log;              // Operations about log

        public delegate void UpdateTB_OutputCallback(string message);   // Update Output TextBlock

        public MainWindow()
        {
            // Initialization
            isTesting = false;
            testTimes = new int[] { 0, 0, 0, 0, 0, 0, 0 };
            testItems = new bool[] { false, false, false, false, false, false, false };
            isByTimes = true;

            serialHelper = new SerialHelper();
            //sendThread = null;
            //recvThread = null;
            sendRecvThread = null;
            strConfigPath = "errorlog.txt";
            log = new LogHelper(strConfigPath);

            // Initialize components
            InitializeComponent();

           
        }

        /// <summary>
        /// Open Configuration Dialog
        /// </summary>
        private void OnClickConfig(object sender, RoutedEventArgs e)
        {
            configWindow = new ConfigWindow();
            // return true when click OK
            if ((bool)configWindow.ShowDialog())
            {
                serialHelper.setPort(configWindow.SP_Item);
            }
        }

        /// <summary>
        /// Begin Testing
        /// </summary>
        private void OnClickStart(object sender, RoutedEventArgs e)
        {
            if (!CheckInput())
                return;

            // MessageBox uesd for testing
#if DEBUG
            //log.InLog("Test");
           // MessageBox.Show("OK");
#endif
            if (serialHelper.OpenPort())
            {
                // Already in testing
                if (isTesting)
                {
                    MessageBox.Show("测试运行中");
                    return;
                }

                log.OpenLog();

                isTesting = true;
                Btn_Start.IsEnabled = false;
                Btn_Stop.IsEnabled = true;

                //Start send and recv thread;
                //sendThread = new Thread(new ThreadStart(SendThread));
                //recvThread = new Thread(new ThreadStart(ReceiveThread));

                sendRecvThread = new Thread(new ThreadStart(SendRecvThread));
                log.InLog("TestStart...");

                sendRecvThread.Start();
                //sendThread.Start();
                //recvThread.Start();
            }
            else // Can't open serial port
            {
                MessageBox.Show("无法打开串口，请检查配置");
            }
        }

        /// <summary>
        /// Stop Testing
        /// </summary>
        private void OnClickStop(object sender, RoutedEventArgs e)
        {
            if (isTesting)
            {
                // Send and Recv Threads will end by themselves
                isTesting = false;
                
                Thread.Sleep(1000); // Wait threads to end

                if (sendRecvThread.IsAlive)
                {
                    sendRecvThread.Abort();
                }


                Btn_Stop.IsEnabled = false;
                Btn_Start.IsEnabled = true;
                if (!serialHelper.ClosePort())
                {
                    MessageBox.Show("关闭端口失败");
                }
                log.FlushLog();
                Thread.Sleep(500); 
                log.CloseLog();
            }
        }

        /// <summary>
        ///  Exit
        /// </summary>
        private void OnClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Before closing, we should save the config
        /// </summary>
        protected override void OnClosed(EventArgs e)
        {
            // TODO Store the config
            
            
            if (isTesting)
            {
                
                isTesting = false;
                // Waiting threads to end
                Thread.Sleep(1000);
                /*
                if (!serialHelper.ClosePort())
                {
                    MessageBox.Show("关闭端口失败");
                }
                 * */
                if (sendRecvThread.IsAlive)
                {
                    sendRecvThread.Abort();
                }

                log.FlushLog();
                Thread.Sleep(500);
                log.CloseLog();
            }
            base.OnClosed(e);
        }

        /// <summary>
        /// Used in Async mode
        /// </summary>
        private void SendThread()
        {
            while (isTesting)
            {
                //TODO: SendCommand to port by setting
                Thread.Sleep(2000);
                System.Console.WriteLine("Sending Commands");
            }
        }

        /// <summary>
        ///  Used in Async mode
        /// </summary>
        private void ReceiveThread()
        {
            //TODO: Receive data, log and show
            while(isTesting)
            {
                Thread.Sleep(1000);

                TB_Output.Dispatcher.Invoke(
                    new UpdateTB_OutputCallback(this.UpdateTB_OutputText),"Test"
                );
            }
        }

        /// <summary>
        /// Used in Sync Mode
        /// </summary>
        private void SendRecvThread()
        {
            int testingTypeBase = 11;
            serialHelper.DiscardInBuffer();
            serialHelper.DiscardOutBuffer();

            if (isByTimes)
            {
               // 根据需要，可能增加 while（true）或 while（isTesting）
                while (isTesting)
                {
                    for (int i = 0; i < testItems.Length; i++)
                    {
                        if (testItems[i])   // testing that item
                        {
                            for (int j = testTimes[i]; j > 0; j--)
                            {
                                serialHelper.sendCommand((byte)(testingTypeBase + i));
                                if (!AnalyzeData(testingTypeBase + i))
                                    Thread.Sleep(15000);    // Wait restarting
                            }
                        }
                        if (!isTesting)
                        {
                            break;
                        }
                    }
                    TB_Output.Dispatcher.Invoke(
                     new UpdateTB_OutputCallback(this.UpdateTB_OutputText), "Testing End");
                }
                        
            }
            else    // By percentage
            {
            while (isTesting)
                {
                    Random rand = new Random();
                    int randNum = rand.Next(1000);
                    for (int i = 0; i < testItems.Length; i++)
                    {
                        if (randNum < testTimes[i]) // Test this item
                        {
                            serialHelper.sendCommand((byte)(testingTypeBase + i));
                            if (!AnalyzeData(testingTypeBase + i))
                                Thread.Sleep(15000);    // Wait restarting 

                            break;
                        }
                    }
                }
            }
        }

        /// <summary>
        ///  Update TextBlock
        /// </summary>
        /// <param name="message"></param>
        public void UpdateTB_OutputText(string message)
        {
            if(TB_Output.Text.Length > 2000)
            {
                TB_Output.Text = null;
            }
            //TB_Output.Text += message + "\n";
            TB_Output.Text = message + "\n" + TB_Output.Text;
        }

#if DEBUG
        /// <summary>
        /// Used for testing code
        /// </summary>
        private void OnClickTest(object sender, RoutedEventArgs e)
        {
            if (isTesting == false)
            {
                isTesting = true;
                Thread receiveThread = new Thread(new ThreadStart(ReceiveThread));
                receiveThread.Start();
            }
            else
            {
                isTesting = false;
            }
        }
#endif
        /// <summary>
        /// Checked means enable this test
        /// </summary>
        private void OnCKB_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox testCBX = sender as CheckBox;
            TextBox testTBX = VisualTreeHelper.GetChild(
                VisualTreeHelper.GetParent(testCBX) as DependencyObject, 2) as TextBox;
            
            if ((bool)testCBX.IsChecked)
            {
                testTBX.Visibility = Visibility.Visible;
                testTBX.IsEnabled = true;
                testTBX.Clear();
            }
            else
            {
                testTBX.Visibility = Visibility.Hidden;
                testTBX.IsEnabled = false;
            }

        }

        /// <summary>
        /// By times or by percentage
        /// </summary>
        private void OnRBtnChecked(object sender, RoutedEventArgs e)
        {
            if ((sender as RadioButton).Name.Equals("RBtn_Times"))
            {
                isByTimes = true;
                if (RBtn_Pencent != null)
                {
                    RBtn_Pencent.IsChecked = false;
                }
            }
            else
            {
                isByTimes = false;
                if (null != RBtn_Times)
                {
                    RBtn_Times.IsChecked = false;
                }
            }

            CKB_Default.IsChecked = false;
            OnCKB_Default_Clicked(CKB_Default, new RoutedEventArgs());
        }

        /// <summary>
        /// Use default setting
        /// </summary>
        private void OnCKB_Default_Clicked(object sender, RoutedEventArgs e)
        {
            // Enable Default checked
            UIElementCollection docks = STKPL_Test.Children;
            if ((bool)(sender as CheckBox).IsChecked)
            {
                foreach (DockPanel dp in docks)
                {
                    // Skip default setting
                    (dp.Children[1] as CheckBox).IsChecked = true;
                    TextBox tb = dp.Children[2] as TextBox;
                    tb.Visibility = Visibility.Visible;
                    tb.IsEnabled = true;
                    if (isByTimes)
                    {
                        tb.Text = "1";
                    }
                    else
                    {
                        tb.Text = "143";
                    }
                }
                DockPanel lastDP = docks[docks.Count - 1] as DockPanel;
               if(!isByTimes)
                (lastDP.Children[2] as TextBox).Text = "142";
            }
            else
            {
                foreach (DockPanel dp in docks)
                {
                    // Skip default setting
                    (dp.Children[1] as CheckBox).IsChecked = false;
                    TextBox tb = dp.Children[2] as TextBox;
                    tb.IsEnabled = false;
                    tb.Visibility = Visibility.Hidden;
                    tb.Clear();
                }
            }
        }
        
        /// <summary>
        /// Iteratively receive data until coming into end signal
        /// </summary>
        /// <param name="inputBytes">Bytes read from serial port</param>
        /// <returns> True when testing not </returns>
        private bool AnalyzeData(int TestingType)
        {
            string strTestType;
            bool noError = true;
            switch (TestingType)
            {
                case 0:
                    strTestType = "心跳测试";
                    break;
                case 10:
                    strTestType = "全部测试";
                    break;
                case 11:
                    strTestType = "CPU测试";
                    break;
                case 12:
                    strTestType = "Cache测试";
                    break;
                case 13:
                    strTestType = "FPU测试";
                    break;
                case 14:
                    strTestType = "ALU测试";
                    break;
                case 15:
                    strTestType = "Memory测试";
                    break;
                case 16:
                    strTestType = "外设测试";
                    break;
                case 17:
                    strTestType = "PL测试";
                    break;
                default:
                    strTestType = "异常错误";
                    break;
            }

            bool isEnd = false;
            byte[] recvBytes = new byte[20];
            while (!isEnd)
            {
                Thread.Sleep(300);
                recvBytes = serialHelper.receiveData();
                string strLog = "";
                switch (recvBytes[0])
                {
                    case 1:    // Watchdog restart
                        strLog = "看门狗重启";
                        break;
                    case 2:     // Testing end;
                        strLog = strTestType + "结束";
                        isEnd = true;   // Stop Reading Data;
                        break;
                    case 11:  // Testing CPU
                        if (1 == recvBytes[1])
                        {
                            strLog = "CPUTesting OK";
                        }
                        else
                        {
                            strLog = "CPUError:";
                            strLog += "R" + recvBytes[3];
                            strLog += "期望:" + BitConverter.ToUInt32(recvBytes, 4);
                            strLog += "实际:" + BitConverter.ToUInt32(recvBytes, 8);
                            log.InLog(strLog);
                            noError = false;
                        }
                        break;
                    case 12:    // Testing Cache
                        if (1 == recvBytes[1])
                        {
                            strLog = "CacheTesting OK";
                        }
                        else
                        {
                            strLog = "CacheError:";
                            strLog += "期望:" + BitConverter.ToUInt32(recvBytes, 3);
                            strLog += "实际:" + BitConverter.ToUInt32(recvBytes, 7);
                            noError = false;
                        }
                        break;
                    case 13:    // Testing FPU
                        if (1 == recvBytes[1])
                        {
                            strLog = "FPUTesting OK";
                        }
                        else
                        {
                            strLog = "FPUError:";
                            strLog += "期望:" + BitConverter.ToDouble(recvBytes, 3);
                            strLog += "实际:" + BitConverter.ToDouble(recvBytes, 11);
                            noError = false;
                        }
                        break;
                    case 14:    // Testing ALU
                        if (1 == recvBytes[1])
                        {
                            strLog = "ALUTesting OK";
                        }
                        else
                        {
                            strLog = "ALUError:";
                            strLog += "期望:" + BitConverter.ToInt32(recvBytes, 3);
                            strLog += "实际:" + BitConverter.ToUInt32(recvBytes, 7);
                            noError = false;
                        }
                        break;
                    case 15:    // Testing Memory
                        if (1 == recvBytes[1])
                        {
                            strLog = "MemoryTesting OK";
                        }
                        else
                        {
                            strLog = "MemoryError:";
                            strLog += "地址:" + BitConverter.ToInt32(recvBytes, 3);
                            strLog += "期望:" + BitConverter.ToInt32(recvBytes, 7);
                            strLog += "实际:" + BitConverter.ToInt32(recvBytes, 11);
                            noError = false;
                        }
                        break;
                    case 16:    // Testing Peripheral
                        if (1 == recvBytes[1])
                        {
                            strLog = "PeripheralTesting 设备类型:";
                            switch (recvBytes[3])
                            {
                                case 0:
                                    strLog += "GIC";
                                    break;
                                case 1:
                                    strLog += "DMA";
                                    break;
                                case 2:
                                    strLog += "QSPI";
                                    break;
                                default:
                                    strLog += "未知";
                                    break;
                            }
                            strLog += " OK";
                        }
                        else
                        {
                            strLog = "PeripheralError:设备类型:";
                            switch (recvBytes[3])
                            {
                                case 0:
                                    strLog += "GIC";
                                    break;
                                case 1:
                                    strLog += "DMA";
                                    strLog += "频道:" + recvBytes[4];
                                    strLog += "源地址:" + BitConverter.ToUInt32(recvBytes, 6);
                                    strLog += "目的地址:" + BitConverter.ToUInt32(recvBytes, 10);
                                    break;
                                case 2:
                                    strLog += "QSPI";
                                    break;
                                default :
                                    strLog += "未知";
                                    break;
                            }
                            noError = false;
                        }
                        break;
                    case 17:    // Testing PL
                        if (1 == recvBytes[1])
                        {
                            strLog = "PLTesting OK";
                        }
                        else
                        {
                            UInt32 temp = BitConverter.ToUInt32(recvBytes, 3);
                            strLog = "PSError:";
                            strLog += "待定";
                            noError = false;
                        }
                        break;
                    case 0xFF:
                        log.InLog("读取串口失败，等待设备重启");
                        return false;
                    default:
                        log.InLog("返回未知数据, 等待设备重启");
                        return false;
                }

                log.InLog(strLog);  // Record log
               // if (!noError)       // Remind Errors
                {
                    TB_Output.Dispatcher.Invoke(
                     new UpdateTB_OutputCallback(this.UpdateTB_OutputText), strLog);
                }
            }
            return true;
        }

        /// <summary>
        /// Check each inputs and set testing variables
        /// </summary>
        /// <returns>true when all checks are ok</returns>
        private bool CheckInput()
        {
            // Initialize
            for(int i=0 ; i < testTimes.Length; i++)
            {
                testTimes[i] = 0;
            }

            UIElementCollection docks = STKPL_Test.Children;

            bool isSeted = false;
            // Set testItems and get settings
            for (int i = 0; i < docks.Count; i++)
            {
                DockPanel dp = docks[i] as DockPanel;
                if ((bool)(dp.Children[1] as CheckBox).IsChecked)
                {
                    isSeted = true;
                    testItems[i] = true;
                    try
                    {
                        testTimes[i] = Int32.Parse((dp.Children[2] as TextBox).Text);
                    }
                    catch (Exception e)
                    {
#if DEBUG
                        System.Console.WriteLine( e.ToString() );
#endif
                        MessageBox.Show("第" + (i+2) + "个输入应为整数");
                        return false;
                    }
                }
                else
                {
                    testItems[i] = false;
                }
            }

            if (!isSeted)
            {
                MessageBox.Show("请先进行设置");
                return false;
            }

            if (!isByTimes) // By Percentage
            {
                for (int i = 1; i < testTimes.Length; i++)
                {
                    testTimes[i] += testTimes[i - 1];
                }
                if (testTimes[testTimes.Length - 1] != 1000)
                {
                    MessageBox.Show("输入总和应为1000");
                    return false;
                }
                
            }
            return true;
        }

        /// <summary>
        /// Open logfile with a program
        /// </summary>
        private void OnClickLog(object sender, RoutedEventArgs e)
        {
            LogHelper.OpenLog("notepad.exe", strConfigPath);
        }

    }
}
