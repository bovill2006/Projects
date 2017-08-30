using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Net; 
using System.IO;
using System.Xml;
using System.Runtime.Serialization.Json;

public partial class BankService : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void createBut_Click(object sender, EventArgs e)
    {
        string url = @"http://10.1.11.159:8003/Service.svc/createCard/" + nameText.Text;
        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
        WebResponse response = request.GetResponse();
        Stream responseStream = response.GetResponseStream();

        StreamReader reader = new StreamReader(responseStream);
        string i = reader.ReadToEnd();
        cardLabel.Text = i; 
    }
}