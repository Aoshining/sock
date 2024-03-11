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
    public partial class Form5 : Form
    {
        [DllImport("C++.dll")]
        private static extern void doubleCompute(string number1, string number2, string source, int compute, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void floatCompute(string number1, string number2, string source, int compute, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void decCompute(string number1, string number2, string source, int compute, StringBuilder output);

        public Form5()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }

        private void Form5_FormClosing(object sender, FormClosingEventArgs e)
        {
            Menu f = new Menu();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == String.Empty || textBox2.Text == String.Empty || textBox3.Text == String.Empty)
            {
                MessageBox.Show("数据不能为空", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Regex reg = new Regex("^-?[0-9]+(\\.[0-9]*(([Ee][-\\+]|[Ee])[0-9]+)?)?$");
            if (!reg.Match(textBox1.Text).Success || (!reg.Match(textBox2.Text).Success&&textBox2.Text!="float"&& textBox2.Text != "double") || !reg.Match(textBox3.Text).Success)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (comboBox1.SelectedIndex == 3 && double.Parse(textBox3.Text) == 0)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
                StringBuilder Double = new StringBuilder();
                StringBuilder Float = new StringBuilder();
                doubleCompute(textBox1.Text, textBox3.Text, textBox2.Text, comboBox1.SelectedIndex + 1, Double);
                floatCompute(textBox1.Text, textBox3.Text, textBox2.Text, comboBox1.SelectedIndex + 1, Float);
                label9.Text = Float.ToString().Substring(0, 1);
                label10.Text = Float.ToString().Substring(1, 8);
                label11.Text = Float.ToString().Substring(9, 23);
                label14.Text = Double.ToString().Substring(0, 1);
                label13.Text = Double.ToString().Substring(1, 11);
                label12.Text = Double.ToString().Substring(12, 52);
                StringBuilder dex = new StringBuilder();
                decCompute(textBox1.Text, textBox3.Text, textBox2.Text, comboBox1.SelectedIndex + 1, dex);
                label20.Text=dex.ToString();
        }
    }
}
