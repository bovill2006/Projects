using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSE445Assignment3
{
    class Decoder
    {
       

        public OrderObject decode(string encoded)
        {
            OrderObject passed = new OrderObject();
            char[] delimiter = {' '};
            string[] code = encoded.Split(delimiter);
 
            byte[] s = Convert.FromBase64String(code[0]);
            passed.setSender(Encoding.UTF8.GetString(s));

            byte[] c = Convert.FromBase64String(code[1]);
            passed.setCard(Convert.ToInt32(Encoding.UTF8.GetString(c)));
      
            byte[] r = Convert.FromBase64String(code[2]);
            passed.setReceiver(Encoding.UTF8.GetString(r));

            byte[] a = Convert.FromBase64String(code[3]);
            passed.setAmount(Convert.ToInt32(Encoding.UTF8.GetString(a)));

            return passed;
        }
        /*
         Decoder is a class or a method in a class: The Decoder will convert the encoded string back into the OrderObject.
         */
    }
}
