using System;
using System.IO;
using System.IO.Pipes;

namespace NamedPipe
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Выберите режим(1 - Сервер, 2 - Клиент): ");
			string choice = Console.ReadLine();

			if (choice == "2")
				RunClient();
			else
				RunServer();
		}

		static void RunServer()
		{
			try
			{
				Console.WriteLine("СЕРВЕР");

				NamedPipeServerStream pipestream = new("MyChannale123");

				Console.WriteLine("Сервер запущен. Жду клиента");
				pipestream.WaitForConnection();

				Console.WriteLine("Клиент подключен\n");

				StreamReader reader = new(pipestream);
				StreamWriter writer = new(pipestream)
				{
					AutoFlush = true
				};

				string message = "";
				bool myTurn = true;

				while (message != "ВСЕ")
				{
					if (myTurn)
					{
						Console.Write("Вы (сервер): ");
						message = Console.ReadLine();
						writer.WriteLine(message);
						myTurn = false;
					}
					else
					{
						Console.Write("Жду ответ");
						message = reader.ReadLine();
						Console.WriteLine($"\rКлиент: {message}");
						myTurn = true;
					}
				}

				Console.WriteLine("\nКонец");
				pipestream.Close();
				Console.ReadLine();
			}
			catch (IOException ex)
			{
				Console.WriteLine($"Ошибка: {ex.Message}");
				Console.ReadLine();
			}
		}

		static void RunClient()
		{
			try
			{
				Console.WriteLine("КЛИЕНТ");
				Console.WriteLine("Подключаюсь к серверу");

				NamedPipeClientStream pipestream = new("MyChannale123");

				pipestream.Connect(5000);
				Console.WriteLine("Подключено \n");

				StreamReader reader = new(pipestream);
				StreamWriter writer = new(pipestream)
				{
					AutoFlush = true
				};

				string message = "";
				bool myTurn = false;

				do
				{
					if (!myTurn)
					{
						Console.Write("Жду сообщение");
						message = reader.ReadLine();
						Console.WriteLine($"\rСервер: {message}");
						myTurn = true;
					}
					else
					{
						Console.Write("Вы (клиент): ");
						message = Console.ReadLine();
						writer.WriteLine(message);
						myTurn = false;
					}
				}
				while (message != "ВСЕ");

				Console.WriteLine("\nКонец");
				pipestream.Close();
				Console.ReadLine();
			}
			catch (IOException ex)
			{
				Console.WriteLine($"Ошибка: {ex.Message}");
				Console.ReadLine();
			}
		}
	}
}