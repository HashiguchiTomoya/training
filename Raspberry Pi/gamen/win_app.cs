using System.Diagnostics;

namespace gamen
{
    [DebuggerDisplay($"{{{nameof(GetDebuggerDisplay)}(),nq}}")]
    public partial class win_app : Form
    {
        int Type = 0;               //LEDかLCDのデータかを判定する変数
        int LED_Status = 0;         //LEDの変数
        string IP = "";             //入力されたIPを格納する変数
        string IP_Port = "";        //入力されたportを格納する変数
        string LCD_Status = "";     //入力されたLCDに出力する文字を格納する変数

        //ボタン等の呼び出し
        public win_app()
        {
            InitializeComponent();
            TextBox_Status_Display.MaxLength = 100;
        }

        //画面の呼び出し
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        //赤の点灯
        private void Button_Red_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 1;
            TextBox_Status_Display.AppendText("赤を点灯\r\n");
            Program.SendData(Type, LED_Status);
        }

        //青の点灯
        private void Button_Bule_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 2;
            TextBox_Status_Display.AppendText("青を点灯\r\n");
            Program.SendData(Type, LED_Status);
        }

        //緑の点灯
        private void Button_Green_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 3;
            TextBox_Status_Display.AppendText("緑を点灯\r\n");
            Program.SendData(Type, LED_Status);
        }

        //赤の点滅
        private void Button_Red_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 4;
            TextBox_Status_Display.AppendText("赤を点滅\r\n");
            Program.SendData(Type, LED_Status);
        }

        //青の点滅
        private void Button_Bule_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 5;
            TextBox_Status_Display.AppendText("青を点滅\r\n");
            Program.SendData(Type, LED_Status);
        }

        //緑の点滅
        private void Button_Green_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 6;
            TextBox_Status_Display.AppendText("緑を点滅\r\n");
            Program.SendData(Type, LED_Status);
        }

        //出力ボタン
        private void Button_Output_Click(object sender, EventArgs e)
        {
            Type = 2;
            string input = TextBox_String.Text;     // ユーザー入力を取得
            TextBox_Status_Display.AppendText($"{input}を表示\r\n");

            LCD_Status = input;     // 数値でも文字列として格納
            MessageBox.Show($"格納された文字列: {LCD_Status}");
            Program.SendData(Type, LCD_Status);     // 文字列として送信
        }

        //文字の入力
        private void TextBox_String_TextChanged(object sender, EventArgs e)
        {

        }

        private string GetDebuggerDisplay()
        {
            return ToString();
        }

        //接続ボタン
        private void Button_Connection_Click(object sender, EventArgs e)
        {
            string IP_Input = TextBox_IP.Text;      //ユーザーが入力したIPを取得
            string Port_Input = TextBox_Port.Text;  //ユーザーが入力したportを取得
            TextBox_Status_Display.AppendText($"IP:{IP_Input},port:{Port_Input}に接続");

            IP = IP_Input;
            IP_Port = Port_Input;

            Program.SendData(IP, IP_Port);

        }

        //状況表示
        private void TextBox_Status_Display_TextChanged(object sender, EventArgs e)
        {

        }
    }
}