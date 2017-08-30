using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class TryIt : System.Web.UI.Page
{
    ServiceReference.ServiceClient service = new ServiceReference.ServiceClient();

    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void EncodeBut_Click(object sender, EventArgs e)
    {
        
        EncryptedLabel.Text =service.encode(Convert.ToInt32(AmountText.Text), Convert.ToString(IdText.Text), Convert.ToInt32(CardText.Text));
    }
    protected void DecodeBut_Click(object sender, EventArgs e)
    {
       ServiceReference.DecryptObject Obj = service.decode(EncryptedLabel.Text);

       DecodeLabel.Text = "Amount: "+Obj.Amount.ToString()+"<br>";
       DecodeLabel.Text += "ID: " + Obj.Id.ToString() +"<br>";
       DecodeLabel.Text += "CardNo: " + Obj.CardNo.ToString() +"<br>";
       
    }
}