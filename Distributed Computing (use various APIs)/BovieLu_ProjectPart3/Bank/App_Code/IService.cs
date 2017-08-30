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
    [WebGet(ResponseFormat = WebMessageFormat.Json, UriTemplate = "/createCard/{name}")]
    newCard createCard(string name);
}

// Use a data contract as illustrated in the sample below to add composite types to service operations.
[DataContract]
public class newCard
{
    [DataMember]
    public int card
    {
        get;
        set;
    }
    [DataMember]
    public string name
    {
        get;
        set;
    }
}
