using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using CSE445Assignment3.ServiceReference1;

namespace CSE445Assignment3
{
    class BankService
    {
        private static List<String> list = new List<string>();
        private static int count = 0;

        public int create()
        {
            int output;
            var chars = "123456789";
            var cardNumber = new char[4];
            var random = new Random();

            for (int i = 0; i < cardNumber.Length; i++)
            {
                cardNumber[i] = chars[random.Next(chars.Length)];
            }
            var result = new String(cardNumber);
            list.Add(result);
            count++;
            output = Convert.ToInt32(result);
            return output;
        }

        public bool validate(string input)
        {
            bool result = false;
            ServiceClient a = new ServiceClient();// card decrpyt
            input = a.Decrypt(input);

            for (int i = 0; i < count; i++)
            {
                if (input.Equals(list[i], StringComparison.Ordinal))
                {
                    result = true;
                }
            }
            return result;
        }
        /*
         Bank service is a class: It allows the travel agency to apply for a credit card number.
         The travel agency will use this number to purchase rooms from the hotel suppliers.
         The hotel suppliers will send the credit card number to the bank for validation.
         The bank will return the message “valid” or “not valid”. When the hotel suppliers send
         the credit card number to the bank, it will call the encryption service in ASU repository
         to encrypt the string number. If you use the .svc service, you should use "Add Service Reference".
         If you use the .asmx service, you must use "Add Web Reference". The recommendation is to
         use the .svc service, as it is the new standard. On the other hand, the bank will call ASU
         decryption service to decrypt the number before comparing with the valid credit card numbers.
         This question is for the three-member group projects only.
         */
    }
}
