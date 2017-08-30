using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ProjectPart2Service;
using System.Net;
using System.IO;


public partial class TryIt : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void StemButton_Click(object sender, EventArgs e)
    {
        ProjectPart2Service.ServiceClient service = new ProjectPart2Service.ServiceClient();
        string input = StemText.Text;
        input = service.Stemming(input);
        StemLabel.Text = input;
    }
    protected void NewsButton_Click(object sender, EventArgs e)
    {
        ProjectPart2Service.ServiceClient service = new ProjectPart2Service.ServiceClient();
        string input = NewsText.Text;

        char delimiter = ' ';
        string[] output = input.Split(delimiter);
        output = service.NewsFocus(output);
        for (int k = 0; k < output.Length; k++)
        {
            NewsLabel.Text += "<br><br>" + output[k];
        }
    }
}