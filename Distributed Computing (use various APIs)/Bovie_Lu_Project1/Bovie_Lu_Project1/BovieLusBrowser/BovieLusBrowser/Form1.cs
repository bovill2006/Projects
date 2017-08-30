using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BovieLusBrowser
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnGo_Click(object sender, EventArgs e)
        {
            webBrowser1.Navigate(txtUrl.Text);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            EncrypDecryp.Service encrypt = new EncrypDecryp.Service();
            label1.Text = encrypt.Encrypt(textBox1.Text);
            label2.Text = encrypt.Decrypt(label1.Text);
        }

        private void btnStock_Click(object sender, EventArgs e)
        {
            stockQuote.Service stock = new stockQuote.Service();
            stockLabel.Text = stock.getStockquote(stockBox.Text);

        }
    }
}
