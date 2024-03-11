namespace UI
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            dataGridView1 = new DataGridView();
            Column1 = new DataGridViewTextBoxColumn();
            Column2 = new DataGridViewTextBoxColumn();
            Column3 = new DataGridViewTextBoxColumn();
            tableLayoutPanel1 = new TableLayoutPanel();
            dataGridView2 = new DataGridView();
            Column4 = new DataGridViewTextBoxColumn();
            Column5 = new DataGridViewTextBoxColumn();
            panel1 = new Panel();
            menuStrip1 = new MenuStrip();
            打开文件ToolStripMenuItem = new ToolStripMenuItem();
            打开asm文件ToolStripMenuItem = new ToolStripMenuItem();
            打开bin文件ToolStripMenuItem = new ToolStripMenuItem();
            汇编ToolStripMenuItem = new ToolStripMenuItem();
            反汇编ToolStripMenuItem = new ToolStripMenuItem();
            运行ToolStripMenuItem = new ToolStripMenuItem();
            停止ToolStripMenuItem = new ToolStripMenuItem();
            下一步ToolStripMenuItem = new ToolStripMenuItem();
            返回ToolStripMenuItem = new ToolStripMenuItem();
            Running = new Label();
            从asm文件导入机器码ToolStripMenuItem = new ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            panel1.SuspendLayout();
            menuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.AllowUserToResizeColumns = false;
            dataGridView1.AllowUserToResizeRows = false;
            dataGridView1.BackgroundColor = SystemColors.ButtonHighlight;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Column1, Column2, Column3 });
            dataGridView1.Dock = DockStyle.Fill;
            dataGridView1.Location = new Point(1243, 46);
            dataGridView1.Margin = new Padding(5, 4, 5, 4);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersVisible = false;
            dataGridView1.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.AutoSizeToDisplayedHeaders;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.Size = new Size(289, 918);
            dataGridView1.TabIndex = 0;
            // 
            // Column1
            // 
            Column1.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Column1.FillWeight = 30F;
            Column1.HeaderText = "Name";
            Column1.MinimumWidth = 8;
            Column1.Name = "Column1";
            Column1.ReadOnly = true;
            // 
            // Column2
            // 
            Column2.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Column2.FillWeight = 30F;
            Column2.HeaderText = "Num";
            Column2.MinimumWidth = 8;
            Column2.Name = "Column2";
            Column2.ReadOnly = true;
            // 
            // Column3
            // 
            Column3.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Column3.FillWeight = 60F;
            Column3.HeaderText = "Value";
            Column3.MinimumWidth = 8;
            Column3.Name = "Column3";
            Column3.ReadOnly = true;
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 2;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 80.59888F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 19.40112F));
            tableLayoutPanel1.Controls.Add(dataGridView2, 0, 1);
            tableLayoutPanel1.Controls.Add(dataGridView1, 1, 1);
            tableLayoutPanel1.Controls.Add(panel1, 0, 0);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Margin = new Padding(5, 4, 5, 4);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 2;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 42F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.Size = new Size(1537, 968);
            tableLayoutPanel1.TabIndex = 3;
            // 
            // dataGridView2
            // 
            dataGridView2.BackgroundColor = SystemColors.ButtonHighlight;
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Columns.AddRange(new DataGridViewColumn[] { Column4, Column5 });
            dataGridView2.Dock = DockStyle.Fill;
            dataGridView2.Location = new Point(5, 46);
            dataGridView2.Margin = new Padding(5, 4, 5, 4);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.RowHeadersWidth = 62;
            dataGridView2.RowTemplate.Height = 25;
            dataGridView2.Size = new Size(1228, 918);
            dataGridView2.TabIndex = 2;
            // 
            // Column4
            // 
            Column4.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Column4.HeaderText = "mips码";
            Column4.MinimumWidth = 8;
            Column4.Name = "Column4";
            // 
            // Column5
            // 
            Column5.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Column5.HeaderText = "机器码";
            Column5.MinimumWidth = 8;
            Column5.Name = "Column5";
            // 
            // panel1
            // 
            tableLayoutPanel1.SetColumnSpan(panel1, 2);
            panel1.Controls.Add(menuStrip1);
            panel1.Dock = DockStyle.Fill;
            panel1.Location = new Point(5, 4);
            panel1.Margin = new Padding(5, 4, 5, 4);
            panel1.Name = "panel1";
            panel1.Size = new Size(1527, 34);
            panel1.TabIndex = 3;
            // 
            // menuStrip1
            // 
            menuStrip1.BackColor = SystemColors.ControlLight;
            menuStrip1.Dock = DockStyle.Fill;
            menuStrip1.ImageScalingSize = new Size(24, 24);
            menuStrip1.Items.AddRange(new ToolStripItem[] { 打开文件ToolStripMenuItem, 汇编ToolStripMenuItem, 反汇编ToolStripMenuItem, 运行ToolStripMenuItem, 停止ToolStripMenuItem, 下一步ToolStripMenuItem, 返回ToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Padding = new Padding(9, 3, 0, 3);
            menuStrip1.RenderMode = ToolStripRenderMode.System;
            menuStrip1.Size = new Size(1527, 34);
            menuStrip1.TabIndex = 2;
            menuStrip1.Text = "menuStrip1";
            // 
            // 打开文件ToolStripMenuItem
            // 
            打开文件ToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { 打开asm文件ToolStripMenuItem, 从asm文件导入机器码ToolStripMenuItem, 打开bin文件ToolStripMenuItem });
            打开文件ToolStripMenuItem.Name = "打开文件ToolStripMenuItem";
            打开文件ToolStripMenuItem.Size = new Size(98, 28);
            打开文件ToolStripMenuItem.Text = "打开文件";
            // 
            // 打开asm文件ToolStripMenuItem
            // 
            打开asm文件ToolStripMenuItem.Name = "打开asm文件ToolStripMenuItem";
            打开asm文件ToolStripMenuItem.Size = new Size(297, 34);
            打开asm文件ToolStripMenuItem.Text = "从asm文件导入MIPS码";
            打开asm文件ToolStripMenuItem.Click += 打开asm文件ToolStripMenuItem_Click;
            // 
            // 打开bin文件ToolStripMenuItem
            // 
            打开bin文件ToolStripMenuItem.Name = "打开bin文件ToolStripMenuItem";
            打开bin文件ToolStripMenuItem.Size = new Size(297, 34);
            打开bin文件ToolStripMenuItem.Text = "从bin文件导入机器码";
            打开bin文件ToolStripMenuItem.Click += 打开bin文件ToolStripMenuItem_Click;
            // 
            // 汇编ToolStripMenuItem
            // 
            汇编ToolStripMenuItem.Name = "汇编ToolStripMenuItem";
            汇编ToolStripMenuItem.Size = new Size(62, 28);
            汇编ToolStripMenuItem.Text = "汇编";
            汇编ToolStripMenuItem.Click += 汇编ToolStripMenuItem_Click_1;
            // 
            // 反汇编ToolStripMenuItem
            // 
            反汇编ToolStripMenuItem.Name = "反汇编ToolStripMenuItem";
            反汇编ToolStripMenuItem.Size = new Size(80, 28);
            反汇编ToolStripMenuItem.Text = "反汇编";
            反汇编ToolStripMenuItem.Click += 反汇编ToolStripMenuItem_Click_1;
            // 
            // 运行ToolStripMenuItem
            // 
            运行ToolStripMenuItem.Name = "运行ToolStripMenuItem";
            运行ToolStripMenuItem.Size = new Size(62, 28);
            运行ToolStripMenuItem.Text = "运行";
            运行ToolStripMenuItem.Click += 运行ToolStripMenuItem_Click_1;
            // 
            // 停止ToolStripMenuItem
            // 
            停止ToolStripMenuItem.Name = "停止ToolStripMenuItem";
            停止ToolStripMenuItem.Size = new Size(62, 28);
            停止ToolStripMenuItem.Text = "停止";
            停止ToolStripMenuItem.Click += 停止ToolStripMenuItem_Click;
            // 
            // 下一步ToolStripMenuItem
            // 
            下一步ToolStripMenuItem.Name = "下一步ToolStripMenuItem";
            下一步ToolStripMenuItem.Size = new Size(80, 28);
            下一步ToolStripMenuItem.Text = "下一步";
            下一步ToolStripMenuItem.Click += 下一步ToolStripMenuItem_Click;
            // 
            // 返回ToolStripMenuItem
            // 
            返回ToolStripMenuItem.Name = "返回ToolStripMenuItem";
            返回ToolStripMenuItem.Size = new Size(80, 28);
            返回ToolStripMenuItem.Text = "主菜单";
            返回ToolStripMenuItem.Click += 返回ToolStripMenuItem_Click_1;
            // 
            // Running
            // 
            Running.AutoSize = true;
            Running.BackColor = Color.Red;
            Running.ForeColor = SystemColors.ButtonHighlight;
            Running.Location = new Point(643, 6);
            Running.Name = "Running";
            Running.Size = new Size(64, 24);
            Running.TabIndex = 4;
            Running.Text = "运行中";
            Running.Visible = false;
            // 
            // 从asm文件导入机器码ToolStripMenuItem
            // 
            从asm文件导入机器码ToolStripMenuItem.Name = "从asm文件导入机器码ToolStripMenuItem";
            从asm文件导入机器码ToolStripMenuItem.Size = new Size(297, 34);
            从asm文件导入机器码ToolStripMenuItem.Text = "从asm文件导入机器码";
            从asm文件导入机器码ToolStripMenuItem.Click += 从asm文件导入机器码ToolStripMenuItem_Click;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(11F, 24F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1537, 968);
            Controls.Add(Running);
            Controls.Add(tableLayoutPanel1);
            Margin = new Padding(5, 4, 5, 4);
            Name = "Form2";
            Text = "汇编/反汇编";
            FormClosing += Form2_FormClosing;
            Load += Form2_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        public DataGridView dataGridView1;
        private TableLayoutPanel tableLayoutPanel1;
        private Panel panel1;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem 汇编ToolStripMenuItem;
        private ToolStripMenuItem 反汇编ToolStripMenuItem;
        private ToolStripMenuItem 运行ToolStripMenuItem;
        private ToolStripMenuItem 下一步ToolStripMenuItem;
        private ToolStripMenuItem 返回ToolStripMenuItem;
        private DataGridView dataGridView2;
        private DataGridViewTextBoxColumn Column4;
        private DataGridViewTextBoxColumn Column5;
        private DataGridViewTextBoxColumn Column1;
        private DataGridViewTextBoxColumn Column2;
        private DataGridViewTextBoxColumn Column3;
        private Label Running;
        private ToolStripMenuItem 停止ToolStripMenuItem;
        private ToolStripMenuItem 打开文件ToolStripMenuItem;
        private ToolStripMenuItem 打开asm文件ToolStripMenuItem;
        private ToolStripMenuItem 打开bin文件ToolStripMenuItem;
        private ToolStripMenuItem 从asm文件导入机器码ToolStripMenuItem;
    }
}