namespace UI
{
    partial class Menu
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            button5 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft YaHei UI", 15F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(86, 30);
            label1.Name = "label1";
            label1.Size = new Size(122, 27);
            label1.TabIndex = 0;
            label1.Text = "Mips编译器";
            // 
            // button1
            // 
            button1.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point);
            button1.Location = new Point(86, 98);
            button1.Name = "button1";
            button1.Size = new Size(122, 31);
            button1.TabIndex = 1;
            button1.Text = "汇编/反汇编";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point);
            button2.Location = new Point(86, 135);
            button2.Name = "button2";
            button2.Size = new Size(122, 31);
            button2.TabIndex = 2;
            button2.Text = "整数转换";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point);
            button3.Location = new Point(86, 246);
            button3.Name = "button3";
            button3.Size = new Size(122, 31);
            button3.TabIndex = 3;
            button3.Text = "浮点数运算";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point);
            button4.Location = new Point(86, 209);
            button4.Name = "button4";
            button4.Size = new Size(122, 31);
            button4.TabIndex = 4;
            button4.Text = "浮点数转换";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // button5
            // 
            button5.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point);
            button5.Location = new Point(86, 172);
            button5.Name = "button5";
            button5.Size = new Size(122, 31);
            button5.TabIndex = 5;
            button5.Text = "整数运算";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // Menu
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(285, 293);
            Controls.Add(button5);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(label1);
            Name = "Menu";
            Text = "Mips编译器";
            FormClosed += Menu_FormClosed;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private Button button5;
    }
}