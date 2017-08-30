using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService" in both code and config file together.
[ServiceContract]
public interface IService
{

    [OperationContract]
    string encode(int amount, string id, int cardNo);

    [OperationContract]
    DecryptObject decode(string item);

    // TODO: Add your service operations here
}
[DataContract]
public class DecryptObject
{
    private int am, card;
    private string ID;

    public DecryptObject(int amount, string id, int cardn)
    {
        am = amount;
        ID = id;
        card = cardn;
    }
    [DataMember]
    public int Amount
    {
        get { return am; }
        set { am = value; }
    }
    [DataMember]
    public int CardNo
    {
        get { return card; }
        set { card = value; }
    }

    [DataMember]
    public string Id
    {
        get { return ID; }
        set { ID = value; }
    }
}
// Use a data contract as illustrated in the sample below to add composite types to service operations.

