using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using Iveonik.Stemmers;
using Google.Apis.Customsearch;
using Google.Apis;
using Google.Apis.Json;
using Google.Apis.Requests;
using Google.Apis.Util;
using Google.Apis.Services;
using Newtonsoft.Json;

// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
public class Service : IService
{
    string result;
    String query;
    public string[] i = new string[10];
    public string Stemming(string str)
    {
        IStemmer stemmer = new EnglishStemmer();
        char[] delimiter = { ' ', '\t' };
        string[] i = str.Split(delimiter);

        for (int j = 0; j < i.Length; j++)
        {
            if (String.IsNullOrEmpty(result))
            {
                result = stemmer.Stem(i[j]) + " ";
            }
            else
                result += stemmer.Stem(i[j]) + " ";
        }
        return result;
    }
    public string[] NewsFocus(string[] topics)
    {
        for (int j = 0; j < topics.Length; j++)
        {
            if (String.IsNullOrEmpty(query))
            {
                query = topics[j] + " ";
            }
            else
                query += topics[j] + " ";
        }

        string apiKey = "AIzaSyAdGYEvLJhlTZQ-Uxo_9IcoPuxwvbOcKV4";
        string cseKey = "018422199925324649720:fcnzsnkhzhu";
        var bcsi = new BaseClientService.Initializer { ApiKey = apiKey };
        var css = new Google.Apis.Customsearch.v1.CustomsearchService(bcsi);
        var listRequest = css.Cse.List(query);
        listRequest.Cx = cseKey;
        var search = listRequest.Execute();

        for (int k = 0; k < 10; k++)
        {
            i[k] = search.Items[k].Link;
        }
        return i;
    }
}
