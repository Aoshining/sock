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

    public partial class Form6 : Form
    {
        [DllImport("C++.dll")]
        private static extern void intCompute(string number1, string number2, int source, int target, int expand, int compute, StringBuilder output);

        public Form6()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }

        private void Form6_FormClosing(object sender, FormClosingEventArgs e)
        {
            Menu f = new Menu();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == String.Empty || textBox2.Text == String.Empty || textBox7.Text == String.Empty || textBox6.Text == String.Empty || textBox5.Text == String.Empty)
            {
                MessageBox.Show("数据不能为空", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Regex reg = new Regex("^-?[0-9]\\d*$");
            if (!reg.Match(textBox1.Text).Success || !reg.Match(textBox2.Text).Success || !reg.Match(textBox7.Text).Success || !reg.Match(textBox6.Text).Success || !reg.Match(textBox5.Text).Success)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int source = int.Parse(textBox7.Text);
            int target=int.Parse(textBox6.Text);
            int expand=int.Parse(textBox5.Text);
            if (source <= 0||target<=0||expand<0)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (comboBox1.SelectedIndex == 3 && int.Parse(textBox2.Text) == 0)
            {
                MessageBox.Show("无效数据", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            StringBuilder result = new StringBuilder();
            intCompute(textBox1.Text,textBox2.Text,source,target,expand,comboBox1.SelectedIndex+1,result);
            Output.Text=result.ToString();
        }
    }
}
