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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace UI
{
    public partial class Form3 : Form
    {
        private readonly FontStyle fontStyle = FontStyle.Regular;
        private readonly float fontSize = 0;
        private readonly int lblWidth = 0;

        [DllImport("C++.dll")]
        private static extern void myInt(string number, int source, int target, int expand, StringBuilder output);
        
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            Menu f = new Menu();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == String.Empty || textBox7.Text == String.Empty|| textBox6.Text == String.Empty|| textBox5.Text == String.Empty)
            {
                MessageBox.Show("数据不能为空", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Regex reg = new Regex("^-?[0-9]\\d*$");
            if (!reg.Match(textBox1.Text).Success || !reg.Match(textBox7.Text).Success || !reg.Match(textBox6.Text).Success || !reg.Match(textBox5.Text).Success)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int source = int.Parse(textBox7.Text),target= int.Parse(textBox6.Text),expand= int.Parse(textBox5.Text);
            if (source <= 0||target<=0||expand<0)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            StringBuilder result = new StringBuilder();
            myInt(textBox1.Text,source,target,expand,result);
            Output.Text = result.ToString();
        }
    }
}
