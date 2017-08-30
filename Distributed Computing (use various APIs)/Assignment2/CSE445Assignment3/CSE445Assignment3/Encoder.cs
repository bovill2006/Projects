using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSE445Assignment3
{
    class Encoder
    {

        private OrderObject passed;

        public string encode(OrderObject item)
        {
            passed = item;
            byte[] s = Encoding.UTF8.GetBytes(passed.getSender());
            string result = Convert.ToBase64String(s);

            string cc = Convert.ToString(passed.getCard());
            byte[] c = Encoding.UTF8.GetBytes(cc);
            result += " " + Convert.ToBase64String(c);

            byte[] r = Encoding.UTF8.GetBytes(passed.getRec());
            result += " " + Convert.ToBase64String(r);

            string aa = Convert.ToString(passed.getAmount());
            byte[] a = Encoding.UTF8.GetBytes(aa);
            result += " " + Convert.ToBase64String(a);

            return result;
        }
        /*
         Encoder is a class or a method in a class: The Encoder class will convert an OrderObject into a string.
         You can choose any way to encode the values into a string, as long as you can decode the string to the
         original order object. You can use a class or a method to implement the Encoder.
         */
        
    }
}
