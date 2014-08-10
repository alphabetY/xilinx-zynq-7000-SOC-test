using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Shapes;
using System.IO.Ports;

namespace XilinxTester
{
    /// <summary>
    /// ConfigWindow.xaml 的交互逻辑
    /// </summary>
    public partial class ConfigWindow : Window
    {
        #region Attributes
        // Attributes
        private SerialPortItem sp_Item;
        public SerialPortItem SP_Item
        {
            set
            {
                sp_Item = value;
            }
            get
            {
                return sp_Item;
            }
        }
        //public ObservableCollection<PortName> OC_PortNames 
        //{
        //    get
        //    {
        //        if (null == oc_PortNames)
        //        {
        //            oc_PortNames = new ObservableCollection<PortName>();
        //            // Get port na
        //            string[] portNames = System.IO.Ports.SerialPort.GetPortNames();
        //            oc_PortNames.Add(new PortName() { strPortName = "test" });
        //            foreach (string s in portNames)
        //            {
        //                oc_PortNames.Add(new PortName() { strPortName = s } );
        //            }
        //        }
        //        return oc_PortNames;
        //    }
        //    private set
        //    {
        //        oc_PortNames = value;
        //    }
        //}

        #endregion
        public ConfigWindow()
        {
            InitializeComponent();
            
            //TODO: Read config from file
            string[] portNames = System.IO.Ports.SerialPort.GetPortNames();
            //string[] portNames = SerialHelper.MulGetHardwareInfo(HardwareEnum.Win32_PnPEntity, "Name");


            //TODO: Using Binding
            //ComboBoxItem cbTemItem = new ComboBoxItem();
            //cbTemItem.Content = "Test";
            //CB_ProtName.Items.Add(cbTemItem);
            //CB_ProtName.SelectedIndex = 0;

            // Add portname to ComboBox
            foreach (string s in portNames)
            {
                ComboBoxItem cbItem = new ComboBoxItem();
                cbItem.Content = s;
                CB_ProtName.Items.Add(cbItem);
            }

            if (portNames.Length > 0)
            {
                CB_ProtName.SelectedIndex = 0;
            }

            sp_Item = new SerialPortItem();
        }

        private void OnClickOK(object sender, RoutedEventArgs e)
        {
            if (CB_ProtName.Items.Count > 0)
            {
                sp_Item.PPortName = (CB_ProtName.SelectedItem as ComboBoxItem).Content.ToString();
            }
            sp_Item.PBaudRate = Int32.Parse((CB_BaudRate.SelectedValue as ComboBoxItem).Content.ToString());
            
            // Parity
            switch (CB_Parity.SelectedIndex)
            {
                case 0: // null
                    sp_Item.PParity = Parity.None;
                    break;
                case 1: // odd
                    sp_Item.PParity = Parity.Odd;
                    break;
                case 2: // even
                    sp_Item.PParity = Parity.Even;
                    break;
                case 3: // Mark
                    sp_Item.PParity = Parity.Mark;
                    break;
                case 4: // Space
                    sp_Item.PParity = Parity.Space;
                    break;
            }
            sp_Item.PDataBits = Int32.Parse((CB_DataBits.SelectedItem as ComboBoxItem).Content.ToString());
            // StopBits
            switch (CB_StopBits.SelectedIndex)
            {
                case 0:
                    sp_Item.PStopBits = StopBits.One;
                    break;
                case 1:
                    sp_Item.PStopBits = StopBits.OnePointFive;
                    break;
                case 2:
                    sp_Item.PStopBits = StopBits.Two;
                    break;
                case 3:
                    sp_Item.PStopBits = StopBits.None;
                    break;
                default:
                    sp_Item.PStopBits = StopBits.None;
                    break;
            }
            this.DialogResult = true;
        }

    }
}
