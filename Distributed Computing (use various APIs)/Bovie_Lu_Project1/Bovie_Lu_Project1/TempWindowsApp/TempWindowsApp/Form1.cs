using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TempWindowsApp.localhost;

namespace TempWindowsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Service1 CtoF = new Service1();
            int number = Convert.ToInt32(this.textBox1.Text);
            int result = CtoF.c2f(number);
            this.label1.Text = result.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Service1 FtoC = new Service1();
            int number = Convert.ToInt32(this.textBox1.Text);
            int result = FtoC.f2c(number);
            this.label1.Text = result.ToString();
        }

        
    }
}
