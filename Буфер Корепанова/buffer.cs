using System;
using System.Windows.Forms;

namespace ConsoleApp7
{
    internal class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            int choice = 1;
            while (choice != 0)
            {
                Console.WriteLine("Выберите дейстивие(1 - вставить из буфера, 2 - копировать свой текст в буфер, 0 - выход)");
                choice = Convert.ToInt32(Console.ReadLine());
                switch (choice)
                {
                    case 1:
                        IDataObject text = Clipboard.GetDataObject();
                        if (text == null)
                        {
                            Console.WriteLine("Буфер обмена пуст или недоступен");
                            break;
                        }
                        if (text.GetDataPresent(DataFormats.Text))
                        {
                            string data = (String)text.GetData(DataFormats.Text);
                            Console.WriteLine(data);
                        }
                        else
                        {
                            Console.WriteLine("Тип данных не потдерживается");
                        }
                        break;
                    case 2:
                        Console.WriteLine("Вставьте свой текст");
                        string userText = Console.ReadLine();
                        Clipboard.SetText(userText);
                        break;
                    default:
                        Console.WriteLine("Конец");
                        break;
                }
            }
        }
    }
}
