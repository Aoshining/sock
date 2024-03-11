using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI
{
    public partial class Form4 : Form
    {
        [DllImport("C++.dll")]
        private static extern void intDouble(string number, string source, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void intFloat(string number, string source, StringBuilder output);
        
        [DllImport("C++.dll")]
        private static extern void myInt(string number, int source, int target, int expand, StringBuilder output);

        [DllImport("C++.dll")]
          private static extern void intDec(string number,string source, StringBuilder output);

        public Form4()
        {
            InitializeComponent();
        }

        private void Form4_FormClosing(object sender, FormClosingEventArgs e)
        {
            Menu f = new Menu();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == String.Empty || textBox2.Text == String.Empty)
            {
                MessageBox.Show("数据不能为空", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Regex reg = new Regex("^-?[0-9]+(\\.[0-9]*(([Ee][-\\+]|[Ee])[0-9]+)?)?$");
            if (!reg.Match(textBox1.Text).Success || (!reg.Match(textBox2.Text).Success && textBox2.Text != "float" && textBox2.Text != "double"))
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
                StringBuilder Float = new StringBuilder();
                StringBuilder Double = new StringBuilder();
                intFloat(textBox1.Text, textBox2.Text, Float);
                intDouble(textBox1.Text, textBox2.Text, Double);
                label9.Text = Float.ToString().Substring(0, 1);
                label10.Text = Float.ToString().Substring(1, 8);
                label11.Text = Float.ToString().Substring(9, 23);
                label14.Text = Double.ToString().Substring(0, 1);
                label13.Text = Double.ToString().Substring(1, 11);
                label12.Text = Double.ToString().Substring(12, 52);
                StringBuilder dec = new StringBuilder();
                intDec(textBox1.Text,textBox2.Text, dec);
                label7.Text = dec.ToString();
        }
    }
}
