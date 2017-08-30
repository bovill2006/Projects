using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
    public string encode(int amount, string id, int cardNo)
    {
        string a = Convert.ToString(amount);
        byte[] aa = Encoding.UTF8.GetBytes(a);
        string result = Convert.ToBase64String(aa);

        byte[] i = Encoding.UTF8.GetBytes(id);
        result += " " + Convert.ToBase64String(i);

        string c = Convert.ToString(cardNo);
        byte[] cc = Encoding.UTF8.GetBytes(c);
        result += " " + Convert.ToBase64String(cc);



        return result;

    }

    public DecryptObject decode(string encoded)
    {
        char[] delimiter = { ' ' };
        string[] code = encoded.Split(delimiter);
        byte[] a = Convert.FromBase64String(code[0]);
        byte[] i = Convert.FromBase64String(code[1]);
        byte[] c = Convert.FromBase64String(code[2]);


        DecryptObject result = new DecryptObject(Convert.ToInt32(Encoding.UTF8.GetString(a)),
                             Encoding.UTF8.GetString(i), Convert.ToInt32(Encoding.UTF8.GetString(c)));
        return result;
    }

}
