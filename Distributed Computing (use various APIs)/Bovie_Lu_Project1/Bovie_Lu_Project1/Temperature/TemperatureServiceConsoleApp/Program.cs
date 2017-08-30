using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemperatureServiceConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            myServiceRef.Service1Client myClient = new myServiceRef.Service1Client();
            Int32 ce = 20;
            Int32 fa = 80;
            Int32 ctof = myClient.c2f(ce);
            Int32 ftoc = myClient.f2c(fa);
            Console.WriteLine("C to F is {0}", ctof);
            Console.WriteLine("F to C is {0}", ftoc);
            myClient.Close();
        }
    }
}
