namespace UI
{
    partial class Form6
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
            button1 = new Button();
            Output = new Label();
            textBox7 = new TextBox();
            textBox6 = new TextBox();
            textBox5 = new TextBox();
            textBox1 = new TextBox();
            label6 = new Label();
            label5 = new Label();
            label4 = new Label();
            label3 = new Label();
            label2 = new Label();
            label1 = new Label();
            textBox2 = new TextBox();
            label7 = new Label();
            label8 = new Label();
            comboBox1 = new ComboBox();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            button1.Location = new Point(140, 382);
            button1.Name = "button1";
            button1.Size = new Size(112, 34);
            button1.TabIndex = 26;
            button1.Text = "运算";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // Output
            // 
            Output.AutoSize = true;
            Output.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            Output.Location = new Point(140, 336);
            Output.Name = "Output";
            Output.Size = new Size(18, 20);
            Output.TabIndex = 25;
            Output.Text = "0";
            // 
            // textBox7
            // 
            textBox7.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            textBox7.Location = new Point(140, 191);
            textBox7.Name = "textBox7";
            textBox7.Size = new Size(205, 26);
            textBox7.TabIndex = 24;
            textBox7.Text = "10";
            // 
            // textBox6
            // 
            textBox6.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            textBox6.Location = new Point(140, 243);
            textBox6.Name = "textBox6";
            textBox6.Size = new Size(205, 26);
            textBox6.TabIndex = 23;
            textBox6.Text = "10";
            // 
            // textBox5
            // 
            textBox5.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            textBox5.Location = new Point(140, 289);
            textBox5.Name = "textBox5";
            textBox5.Size = new Size(113, 26);
            textBox5.TabIndex = 22;
            textBox5.Text = "0";
            // 
            // textBox1
            // 
            textBox1.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            textBox1.Location = new Point(140, 50);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(205, 26);
            textBox1.TabIndex = 21;
            textBox1.Text = "0";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label6.Location = new Point(33, 195);
            label6.Name = "label6";
            label6.Size = new Size(54, 20);
            label6.TabIndex = 20;
            label6.Text = "原进制";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label5.Location = new Point(33, 243);
            label5.Name = "label5";
            label5.Size = new Size(69, 20);
            label5.TabIndex = 19;
            label5.Text = "目标进制";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label4.Location = new Point(33, 289);
            label4.Name = "label4";
            label4.Size = new Size(69, 20);
            label4.TabIndex = 18;
            label4.Text = "扩展位至";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label3.Location = new Point(61, 336);
            label3.Name = "label3";
            label3.Size = new Size(39, 20);
            label3.TabIndex = 17;
            label3.Text = "输出";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label2.Location = new Point(258, 292);
            label2.Name = "label2";
            label2.Size = new Size(108, 20);
            label2.TabIndex = 16;
            label2.Text = "（填0不扩展）";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(33, 55);
            label1.Name = "label1";
            label1.Size = new Size(78, 20);
            label1.TabIndex = 15;
            label1.Text = "输入整数1";
            // 
            // textBox2
            // 
            textBox2.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            textBox2.Location = new Point(140, 138);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(205, 26);
            textBox2.TabIndex = 28;
            textBox2.Text = "0";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label7.Location = new Point(33, 143);
            label7.Name = "label7";
            label7.Size = new Size(78, 20);
            label7.TabIndex = 27;
            label7.Text = "输入整数2";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label8.Location = new Point(33, 103);
            label8.Name = "label8";
            label8.Size = new Size(54, 20);
            label8.TabIndex = 29;
            label8.Text = "运算符";
            // 
            // comboBox1
            // 
            comboBox1.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            comboBox1.FormattingEnabled = true;
            comboBox1.Items.AddRange(new object[] { "+", "-", "*", "/" });
            comboBox1.Location = new Point(140, 95);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(121, 28);
            comboBox1.TabIndex = 30;
            // 
            // Form6
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(390, 444);
            Controls.Add(comboBox1);
            Controls.Add(label8);
            Controls.Add(textBox2);
            Controls.Add(label7);
            Controls.Add(button1);
            Controls.Add(Output);
            Controls.Add(textBox7);
            Controls.Add(textBox6);
            Controls.Add(textBox5);
            Controls.Add(textBox1);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Form6";
            Text = "整数运算";
            FormClosing += Form6_FormClosing;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private Label Output;
        private TextBox textBox7;
        private TextBox textBox6;
        private TextBox textBox5;
        private TextBox textBox1;
        private Label label6;
        private Label label5;
        private Label label4;
        private Label label3;
        private Label label2;
        private Label label1;
        private TextBox textBox2;
        private Label label7;
        private Label label8;
        private ComboBox comboBox1;
    }
}