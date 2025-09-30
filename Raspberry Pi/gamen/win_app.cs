using System.Diagnostics;

namespace gamen
{
    [DebuggerDisplay($"{{{nameof(GetDebuggerDisplay)}(),nq}}")]
    public partial class win_app : Form
    {
        int Type = 0;               //LED��LCD�̃f�[�^���𔻒肷��ϐ�
        int LED_Status = 0;         //LED�̕ϐ�
        string IP = "";             //���͂��ꂽIP���i�[����ϐ�
        string IP_Port = "";        //���͂��ꂽport���i�[����ϐ�
        string LCD_Status = "";     //���͂��ꂽLCD�ɏo�͂��镶�����i�[����ϐ�

        //�{�^�����̌Ăяo��
        public win_app()
        {
            InitializeComponent();
            TextBox_Status_Display.MaxLength = 100;
        }

        //��ʂ̌Ăяo��
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        //�Ԃ̓_��
        private void Button_Red_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 1;
            TextBox_Status_Display.AppendText("�Ԃ�_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�̓_��
        private void Button_Bule_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 2;
            TextBox_Status_Display.AppendText("��_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�΂̓_��
        private void Button_Green_Lit_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 3;
            TextBox_Status_Display.AppendText("�΂�_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�Ԃ̓_��
        private void Button_Red_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 4;
            TextBox_Status_Display.AppendText("�Ԃ�_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�̓_��
        private void Button_Bule_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 5;
            TextBox_Status_Display.AppendText("��_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�΂̓_��
        private void Button_Green_Blinking_Click(object sender, EventArgs e)
        {
            Type = 1;
            LED_Status = 6;
            TextBox_Status_Display.AppendText("�΂�_��\r\n");
            Program.SendData(Type, LED_Status);
        }

        //�o�̓{�^��
        private void Button_Output_Click(object sender, EventArgs e)
        {
            Type = 2;
            string input = TextBox_String.Text;     // ���[�U�[���͂��擾
            TextBox_Status_Display.AppendText($"{input}��\��\r\n");

            LCD_Status = input;     // ���l�ł�������Ƃ��Ċi�[
            MessageBox.Show($"�i�[���ꂽ������: {LCD_Status}");
            Program.SendData(Type, LCD_Status);     // ������Ƃ��đ��M
        }

        //�����̓���
        private void TextBox_String_TextChanged(object sender, EventArgs e)
        {

        }

        private string GetDebuggerDisplay()
        {
            return ToString();
        }

        //�ڑ��{�^��
        private void Button_Connection_Click(object sender, EventArgs e)
        {
            string IP_Input = TextBox_IP.Text;      //���[�U�[�����͂���IP���擾
            string Port_Input = TextBox_Port.Text;  //���[�U�[�����͂���port���擾
            TextBox_Status_Display.AppendText($"IP:{IP_Input},port:{Port_Input}�ɐڑ�");

            IP = IP_Input;
            IP_Port = Port_Input;

            Program.SendData(IP, IP_Port);

        }

        //�󋵕\��
        private void TextBox_Status_Display_TextChanged(object sender, EventArgs e)
        {

        }
    }
}