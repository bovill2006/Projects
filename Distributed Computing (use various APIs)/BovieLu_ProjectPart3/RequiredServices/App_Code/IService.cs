using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using Iveonik.Stemmers;
using Google.Apis.Customsearch;
using Google.Apis.Json;
using Google.Apis.Requests;
using Google.Apis.Util;
using Google.Apis.Discovery;
using Google.Apis;
using Newtonsoft.Json;
// NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService" in both code and config file together.
[ServiceContract]
public interface IService
{
    [OperationContract]
    string Stemming(string str);

    [OperationContract]
    string[] NewsFocus(string[] topics);

}
