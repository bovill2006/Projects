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
    newCard temp = new newCard();
    public newCard createCard(string name)
    {
        
        var chars = "123456789";
        var cardNumber = new char[4];
        var random = new Random();

        for (int i = 0; i < cardNumber.Length; i++)
        {
            cardNumber[i] = chars[random.Next(chars.Length)];
        }
        var result = new String(cardNumber);
        temp.card = Convert.ToInt32(result);
        temp.name = name;
        return temp;
    }
}
