using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
        protected void Button1_Click(Object sender, EventArgs e)
        {
            TempReference.Service1Client ctof = new TempReference.Service1Client();
            int number;
            number = ctof.c2f(Convert.ToInt32(TextBox1.Text)); 
            try { Label1.Text = number.ToString(); }
            catch (Exception ec) { Label1.Text = ec.Message.ToString(); }

        }
    protected void Button2_Click(Object sender, EventArgs e)
        {
            TempReference.Service1Client ftoc = new TempReference.Service1Client();
            int number;
            number = ftoc.f2c(Convert.ToInt32(TextBox1.Text));
            try { Label1.Text = number.ToString(); }
            catch (Exception ec) { Label1.Text = ec.Message.ToString(); }
        }

 }
