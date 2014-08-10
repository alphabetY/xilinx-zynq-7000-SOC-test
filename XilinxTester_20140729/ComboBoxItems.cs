using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XilinxTester
{
    // TestItem CB
    public class TestItems
    {
        int id; // Index;
        public int ID
        {
            get { return id; }
            set { id = value; }
        }

        String testInfo;
        public String TestInfo
        {
            get { return testInfo; }
            set { testInfo = value; }
        }
    }

    public class PortName
    {
        public string strPortName { set; get; }
    }

}
