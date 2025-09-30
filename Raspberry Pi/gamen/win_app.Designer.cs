namespace gamen
{
    partial class win_app
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
            Button_Red_Lit = new Button();
            Button_Bule_Lit = new Button();
            Button_Green_Lit = new Button();
            Button_Red_Blinking = new Button();
            Button_Bule_Blinking = new Button();
            Button_Green_Blinking = new Button();
            TextBox_String = new TextBox();
            Button_Output = new Button();
            TextBox_Status_Display = new TextBox();
            TextBox_IP = new TextBox();
            TextBox_Port = new TextBox();
            Button_Connection = new Button();
            SuspendLayout();
            // 
            // Button_Red_Lit(赤の点灯)
            // 
            Button_Red_Lit.BackColor = Color.Red;
            Button_Red_Lit.ForeColor = Color.White;
            Button_Red_Lit.Location = new Point(168, 315);
            Button_Red_Lit.Name = "Button_Red_Lit";
            Button_Red_Lit.Size = new Size(94, 29);
            Button_Red_Lit.TabIndex = 0;
            Button_Red_Lit.Text = "点灯・赤";
            Button_Red_Lit.UseVisualStyleBackColor = false;
            Button_Red_Lit.Click += Button_Red_Lit_Click;
            // 
            // Button_Bule_Lit(青の点灯)
            // 
            Button_Bule_Lit.BackColor = Color.Blue;
            Button_Bule_Lit.ForeColor = Color.White;
            Button_Bule_Lit.Location = new Point(332, 315);
            Button_Bule_Lit.Name = "Button_Bule_Lit";
            Button_Bule_Lit.Size = new Size(94, 29);
            Button_Bule_Lit.TabIndex = 2;
            Button_Bule_Lit.Text = "点灯・青";
            Button_Bule_Lit.UseVisualStyleBackColor = false;
            Button_Bule_Lit.Click += Button_Bule_Lit_Click;
            // 
            // button_Green_Lit(緑の点灯)
            // 
            Button_Green_Lit.BackColor = Color.Lime;
            Button_Green_Lit.ForeColor = Color.White;
            Button_Green_Lit.Location = new Point(492, 315);
            Button_Green_Lit.Name = "Button_Green_Lit";
            Button_Green_Lit.Size = new Size(94, 29);
            Button_Green_Lit.TabIndex = 3;
            Button_Green_Lit.Text = "点灯・緑";
            Button_Green_Lit.UseVisualStyleBackColor = false;
            Button_Green_Lit.Click += Button_Green_Lit_Click;
            // 
            // Button_Red_Blinking(赤の点滅)
            // 
            Button_Red_Blinking.BackColor = Color.Red;
            Button_Red_Blinking.ForeColor = Color.White;
            Button_Red_Blinking.Location = new Point(168, 384);
            Button_Red_Blinking.Name = "Button_Red_Blinking";
            Button_Red_Blinking.Size = new Size(94, 29);
            Button_Red_Blinking.TabIndex = 4;
            Button_Red_Blinking.Text = "点滅・赤";
            Button_Red_Blinking.UseVisualStyleBackColor = false;
            Button_Red_Blinking.Click += Button_Red_Blinking_Click;
            // 
            // Button_Bule_Blinking(青の点滅)
            // 
            Button_Bule_Blinking.BackColor = Color.Blue;
            Button_Bule_Blinking.ForeColor = Color.White;
            Button_Bule_Blinking.Location = new Point(332, 384);
            Button_Bule_Blinking.Name = "Button_Bule_Blinking";
            Button_Bule_Blinking.Size = new Size(94, 29);
            Button_Bule_Blinking.TabIndex = 5;
            Button_Bule_Blinking.Text = "点滅・青";
            Button_Bule_Blinking.UseVisualStyleBackColor = false;
            Button_Bule_Blinking.Click += Button_Bule_Blinking_Click;
            // 
            // Button_Green_blinking(緑の点滅)
            // 
            Button_Green_Blinking.BackColor = Color.Lime;
            Button_Green_Blinking.ForeColor = Color.White;
            Button_Green_Blinking.Location = new Point(492, 384);
            Button_Green_Blinking.Name = "Button_Green_Blinking";
            Button_Green_Blinking.Size = new Size(94, 29);
            Button_Green_Blinking.TabIndex = 6;
            Button_Green_Blinking.Text = "点滅・緑";
            Button_Green_Blinking.UseVisualStyleBackColor = false;
            Button_Green_Blinking.Click += Button_Green_Blinking_Click;
            // 
            // TextBox_String(LCDの入力)
            // 
            TextBox_String.ForeColor = Color.Gray;
            TextBox_String.Location = new Point(175, 236);
            TextBox_String.Name = "TextBox_String";
            TextBox_String.Size = new Size(310, 27);
            TextBox_String.TabIndex = 7;
            TextBox_String.Text = "LCDに出力する文字を入力してください。";
            TextBox_String.TextChanged += TextBox_String_TextChanged;
            // 
            // Button_Output(LCDの出力)
            // 
            Button_Output.Location = new Point(491, 236);
            Button_Output.Name = "Button_Output";
            Button_Output.Size = new Size(94, 29);
            Button_Output.TabIndex = 8;
            Button_Output.Text = "出力";
            Button_Output.UseVisualStyleBackColor = true;
            Button_Output.Click += Button_Output_Click;
            // 
            // TextBox_Status_display(状況表示)
            // 
            TextBox_Status_Display.ForeColor = Color.Gray;
            TextBox_Status_Display.Location = new Point(55, 12);
            TextBox_Status_Display.Multiline = true;
            TextBox_Status_Display.Name = "TextBox_Status_Display";
            TextBox_Status_Display.Size = new Size(267, 110);
            TextBox_Status_Display.TabIndex = 9;
            TextBox_Status_Display.TextChanged += TextBox_Status_Display_TextChanged;
            // 
            // TextBox_IP(IP)
            // 
            TextBox_IP.ForeColor = Color.Gray;
            TextBox_IP.Location = new Point(178, 148);
            TextBox_IP.Name = "TextBox_IP";
            TextBox_IP.Size = new Size(307, 27);
            TextBox_IP.TabIndex = 10;
            TextBox_IP.Text = "IPを入力してください。";
            // 
            // TextBox_Port(port)
            // 
            TextBox_Port.ForeColor = Color.Gray;
            TextBox_Port.Location = new Point(178, 190);
            TextBox_Port.Name = "TextBox_Port";
            TextBox_Port.Size = new Size(304, 27);
            TextBox_Port.TabIndex = 11;
            TextBox_Port.Text = "portをを入力してください。";
            // 
            // Button_Connection(接続)
            // 
            Button_Connection.Location = new Point(491, 193);
            Button_Connection.Name = "Button_Connection";
            Button_Connection.Size = new Size(94, 29);
            Button_Connection.TabIndex = 12;
            Button_Connection.Text = "接続";
            Button_Connection.UseVisualStyleBackColor = true;
            Button_Connection.Click += Button_Connection_Click;
            // 
            // win_app(ボタン定義)
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.White;
            ClientSize = new Size(800, 450);
            Controls.Add(Button_Connection);
            Controls.Add(TextBox_Port);
            Controls.Add(TextBox_IP);
            Controls.Add(TextBox_Status_Display);
            Controls.Add(Button_Output);
            Controls.Add(TextBox_String);
            Controls.Add(Button_Green_Blinking);
            Controls.Add(Button_Bule_Blinking);
            Controls.Add(Button_Red_Blinking);
            Controls.Add(Button_Green_Lit);
            Controls.Add(Button_Bule_Lit);
            Controls.Add(Button_Red_Lit);
            Name = "win_app";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        //アプリの画面設定
        private Button Button_Red_Lit;          //赤の点灯
        private Button Button_Bule_Lit;         //青の点灯
        private Button Button_Green_Lit;        //緑の点灯
        private Button Button_Red_Blinking;     //赤の点滅
        private Button Button_Bule_Blinking;    //青の点滅
        private Button Button_Green_Blinking;   //緑の点滅
        private TextBox TextBox_String;         //テキストボックス（LCDに表示する文字）
        private Button Button_Output;           //テキストボックスを入力された文字を出力
        private TextBox TextBox_Status_Display; //状況を表示
        private TextBox TextBox_IP;             //IPを入力
        private TextBox TextBox_Port;           //portを入力
        private Button Button_Connection;       //入力されたIPとportに接続
    }
}
