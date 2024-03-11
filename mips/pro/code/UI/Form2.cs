using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Common;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Win32;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;


namespace UI
{
    public partial class Form2 : Form
    {
        bool run = false;

        [DllImport("C++.dll")]
        private static extern void assembl(string strin, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void disassembl(string strin, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void Register(int i, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern void intCompute(string number1, string number2, int source, int target, int expand, int compute, StringBuilder output);

        [DllImport("C++.dll")]
        private static extern bool Operate(string input);

        [DllImport("C++.dll")]
        private static extern void Clear();

        [DllImport("C++.dll")]
        private static extern void InitPC();


        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            Initlist();
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            Menu f = new Menu();
            f.Show();
        }

        private void 反汇编ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            if (run)
                return;
            dataGridView2.EndEdit();
            RemoveNullCell(1);
            for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
            {
                StringBuilder mips = new StringBuilder();
                disassembl(dataGridView2.Rows[i].Cells[1].Value.ToString(), mips);
                if (mips.ToString() == "++")
                {
                    dataGridView2.Rows[i].Cells[0].Value = "Error";
                }
                else
                {
                    dataGridView2.Rows[i].Cells[0].Value = mips.ToString();
                }
            }
            dataGridView2.Update();
        }

        private void 汇编ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            if (run)
                return;
            dataGridView2.EndEdit();
            RemoveNullCell(0);
            for (int i = 0; i < dataGridView2.RowCount - 1; i++)
            {
                StringBuilder mips = new StringBuilder();
                assembl(dataGridView2.Rows[i].Cells[0].Value.ToString(), mips);
            }
            InitPC();
            for (int i = 0; i < dataGridView2.RowCount - 1; i++)
            {
                StringBuilder mips = new StringBuilder();
                assembl(dataGridView2.Rows[i].Cells[0].Value.ToString(), mips);
                if (mips.ToString() == "++")
                {
                    dataGridView2.Rows[i].Cells[1].Value = "Error";
                }
                else
                {
                    dataGridView2.Rows[i].Cells[1].Value = mips.ToString();
                }
            }
            InitPC();
            dataGridView2.Update();
        }

        private void 运行ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            if (run)
                return;
            dataGridView2.EndEdit();
            RemoveNullCell(0);
            for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                dataGridView2.Rows[i].Selected = false;
            for (int i = 0; i < dataGridView2.RowCount - 1; i++)
            {
                StringBuilder mips = new StringBuilder();
                assembl(dataGridView2.Rows[i].Cells[0].Value.ToString(), mips);
            }
            InitPC();
            for (int i = 0; i < dataGridView2.RowCount - 1; i++)
            {
                StringBuilder mips = new StringBuilder();
                assembl(dataGridView2.Rows[i].Cells[0].Value.ToString(), mips);
                if (mips.ToString() == "++")
                {
                    dataGridView2.Rows[i].Cells[1].Value = "Error";
                }
                else
                {
                    dataGridView2.Rows[i].Cells[1].Value = mips.ToString();
                }
            }
            InitPC();
            dataGridView2.Update();
            Clear();
            UpdaeRegister();
            run = true;
            Running.Show();
            Run();
        }

        private void 停止ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!run)
                return;
            run = false;
            Running.Hide();
        }

        private void 下一步ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!run)
                return;
            Run();
        }

        private void 返回ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            this.Close();
        }


        private void RemoveNullRows()
        {
            bool isNullRow = true;
            for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
            {
                foreach (DataGridViewCell cell in dataGridView2.Rows[i].Cells)
                {
                    if (cell.Value != null && string.IsNullOrEmpty(cell.Value.ToString()) == false)
                    {
                        isNullRow = false;
                        break;
                    }
                }
                if (isNullRow == true)
                {
                    dataGridView2.Rows.RemoveAt(i);
                }
                isNullRow = true;
            }
            dataGridView2.Update();
        }

        private void RemoveNullCell(int column)
        {
            bool isNullRow = true;
            for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
            {
                DataGridViewCell cell = dataGridView2.Rows[i].Cells[column];
                if (cell.Value != null && string.IsNullOrEmpty(cell.Value.ToString()) == false)
                {
                    isNullRow = false;
                }
                if (isNullRow == true)
                {
                    dataGridView2.Rows.RemoveAt(i);
                }
                isNullRow = true;
            }
            dataGridView2.Update();
        }

        private void Run()
        {
            StringBuilder p = new StringBuilder();
            intCompute(dataGridView1.Rows[32].Cells[2].Value.ToString().Substring(2, 8), "00400000", 16, 10, 0, 2, p);
            int PCline = int.Parse(p.ToString()) / 4;
            if (PCline >= dataGridView2.Rows.Count - 1 || PCline < 0)
            {
                run = false;
                Running.Hide();
                for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                    dataGridView2.Rows[i].Selected = false;
                dataGridView2.Rows[dataGridView2.RowCount - 1].Selected = true;
                return;
            }
            for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                dataGridView2.Rows[i].Selected = false;
            dataGridView2.Rows[PCline].Selected = true;
            if (!Operate(dataGridView2.Rows[PCline].Cells[0].Value.ToString()))
            {
                MessageBox.Show("运行错误", "错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                run = false;
                Running.Hide();
                return;
            }
            UpdaeRegister();
        }

        private void Initlist()
        {
            string[] row1 = new string[] { "$zero", "0", "0x00000000" };
            string[] row2 = new string[] { "$at", "1", "0x20000000" };
            string[] row3 = new string[] { "$v0", "2", "0x00000000" };
            string[] row4 = new string[] { "$v1", "3", "0x00000000" };
            string[] row5 = new string[] { "$a0", "4", "0x00000000" };
            string[] row6 = new string[] { "$a1", "5", "0x00000000" };
            string[] row7 = new string[] { "$a2", "6", "0x00000000" };
            string[] row8 = new string[] { "$a3", "7", "0x00000000" };
            string[] row9 = new string[] { "$t0", "8", "0x00000000" };
            string[] row10 = new string[] { "$t1", "9", "0x00000000" };
            string[] row11 = new string[] { "$t2", "10", "0x00000000" };
            string[] row12 = new string[] { "$t3", "11", "0x00000000" };
            string[] row13 = new string[] { "$t4", "12", "0x00000000" };
            string[] row14 = new string[] { "$t5", "13", "0x00000000" };
            string[] row15 = new string[] { "$t6", "14", "0x00000000" };
            string[] row16 = new string[] { "$t7", "15", "0x00000000" };
            string[] row17 = new string[] { "$s0", "16", "0x00000000" };
            string[] row18 = new string[] { "$s1", "17", "0x00000000" };
            string[] row19 = new string[] { "$s2", "18", "0x00000000" };
            string[] row20 = new string[] { "$s3", "19", "0x00000000" };
            string[] row21 = new string[] { "$s4", "20", "0x00000000" };
            string[] row22 = new string[] { "$s5", "21", "0x00000000" };
            string[] row23 = new string[] { "$s6", "22", "0x00000000" };
            string[] row24 = new string[] { "$s7", "23", "0x00000000" };
            string[] row25 = new string[] { "$t8", "24", "0x00000000" };
            string[] row26 = new string[] { "$t9", "25", "0x00000000" };
            string[] row27 = new string[] { "$k0", "26", "0x00000000" };
            string[] row28 = new string[] { "$k1", "27", "0x00000000" };
            string[] row29 = new string[] { "$gp", "28", "0x10008000" };
            string[] row30 = new string[] { "$sp", "29", "0x7ffffffc" };
            string[] row31 = new string[] { "$fp", "30", "0xffffffff" };
            string[] row32 = new string[] { "$ra", "31", "0x00000000" };
            string[] row33 = new string[] { "pc", "", "0x00400000" };
            string[] row34 = new string[] { "hi", "", "0x00000000" };
            string[] row35 = new string[] { "lo", "", "0x00000000" };
            string[] row36 = new string[] { "mem0", "", "0x00001000" };
            string[] row37 = new string[] { "mem1", "", "0x00001000" };
            string[] row38 = new string[] { "mem2", "", "0x00001000" };
            string[] row39 = new string[] { "mem3", "", "0x00001000" };
            string[] row40 = new string[] { "mem4", "", "0x00001000" };
            object[] rows = new object[] { row1, row2, row3, row4, row5, row6, row7, row8, row9, row10, row11, row12, row13, row14, row15, row16, row17, row18, row19, row20, row21, row22, row23, row24, row25, row26, row27, row28, row29, row30, row31, row32, row33, row34, row35, row36, row37, row38, row39, row40 };
            foreach (string[] i in rows)
            {
                dataGridView1.Rows.Add(i);
            }
        }

        private void UpdaeRegister()
        {
            for (int i = 0; i < 33; i++)
            {
                StringBuilder value = new StringBuilder();
                Register(i, value);
                dataGridView1.Rows[i].Cells[2].Value = "0x" + value.ToString();
            }
            for (int i = 33; i < 38; i++)
            {
                StringBuilder value = new StringBuilder();
                Register(i, value);
                dataGridView1.Rows[i + 2].Cells[2].Value = "0x" + value.ToString();
            }
            dataGridView1.Update();
        }

        private void 打开asm文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;
            dialog.Title = "打开asm文件";
            dialog.Filter = "asm文件(*.asm)|*.asm";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string file = dialog.FileName;
                StreamReader sr = new StreamReader(file, Encoding.Default);
                String line;
                for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                    dataGridView2.Rows.RemoveAt(i);
                int j = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    dataGridView2.Rows.Add(line);
                }
            }
            else
                return;
        }

        private void 打开bin文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;
            dialog.Title = "打开bin文件";
            dialog.Filter = "bin文件(*.bin)|*.bin";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string file = dialog.FileName;
                FileStream sr = new FileStream(file, FileMode.Open, FileAccess.Read);
                BinaryReader br = new BinaryReader(sr);
                for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                    dataGridView2.Rows.RemoveAt(i);
                long length = sr.Length;
                byte[] byt = new byte[length];
                br.Read(byt, 0, byt.Length);
                for (int i = 0; i < byt.Length; i += 4)
                {
                    string strResult = "";
                    for (int j = i; j < 4; j++)
                    {
                        string strTemp = System.Convert.ToString(byt[j], 2);
                        strTemp = strTemp.Insert(0, new string('0', 8 - strTemp.Length));
                        strResult += strTemp;
                    }
                    string[] str = { "", strResult };
                    dataGridView2.Rows.Add(str);
                }
                RemoveNullCell(1);
            }
            else
                return;
        }

        private void 从asm文件导入机器码ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;
            dialog.Title = "打开asm文件";
            dialog.Filter = "asm文件(*.asm)|*.asm";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string file = dialog.FileName;
                StreamReader sr = new StreamReader(file, Encoding.Default);
                String line;
                for (int i = dataGridView2.RowCount - 2; i >= 0; i--)
                    dataGridView2.Rows.RemoveAt(i);
                int j = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    string[] Line = { "", line };
                    dataGridView2.Rows.Add(Line);
                }
            }
            else
                return;

        }
    }
}
