using System.Diagnostics;
using System.Net.Sockets;
using System.Text;

namespace gamen
{
    internal static class Program
    {
        //IPとportを設定（アプリ内で変更可能）
        private static string Ip_Address = "192.168.1.100";
        private static int port = 8080;

        [STAThread]
        private static void Main()
        {
            ApplicationConfiguration.Initialize();
            Application.Run(new win_app());
        }

        //アプリからデータを取得（LED）
        public static void SendData(int type, int LED_status)
        {
            SendDataInternal(Ip_Address, port, $"{type},{LED_status}");
        }

        //アプリからデータを取得（LCD）
        public static void SendData(int type, string LCD_status)
        {
            SendDataInternal(Ip_Address, port, $"{type},{LCD_status}");
        }

        //アプリからデータを取得（IPとport）
        public static void SendData(string IP, string IPport) //senddataの名前を変える
        {
            if (int.TryParse(IPport, out int parsedPort))
            {
                Ip_Address = IP;
                port = parsedPort;
                Console.WriteLine($"Updated connection details: IP = {Ip_Address}, Port = {port}");
            }
            //エラー処理
            else
            {
                Console.WriteLine("Error: Invalid port number.");
            }
        }

        //TCP通信
        private static void SendDataInternal(string ip, int port, string message)
        {
            try
            {
                using (TcpClient client = new TcpClient(ip, port))
                using (NetworkStream stream = client.GetStream())
                {
                    //データを送信
                    byte[] sendBytes = Encoding.UTF8.GetBytes(message);
                    stream.Write(sendBytes, 0, sendBytes.Length);

                    //データを受信 要確認
                    byte[] receiveBytes = new byte[1024];
                    int bytesRead = stream.Read(receiveBytes, 0, receiveBytes.Length);
                    string receivedMessage = Encoding.UTF8.GetString(receiveBytes, 0, bytesRead);
                    Console.WriteLine("Received: " + receivedMessage);
                }
            }
            //通信のエラー処理
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }
    }
}