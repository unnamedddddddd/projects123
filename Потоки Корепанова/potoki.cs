using System;
using System.Net.Http;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using OfficeOpenXml;

class Program
{
    static async Task Main()
    {
        string urlFirst = "https://go.microsoft.com/fwlink/?LinkID=521962";
        string urlSecond = "https://raw.githubusercontent.com/datasets/gdp/master/data/gdp.csv";

        string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);

        string localFilePath1 = Path.Combine(desktopPath, "data1.xlsx");

        string localFilePath2 = Path.Combine(desktopPath, "data2.xlsx");

        using (HttpClient client = new HttpClient())
        {
            client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");

            try
            {
                Console.WriteLine("Скачиваю первый файл...");
                byte[] fileBytes1 = await client.GetByteArrayAsync(urlFirst);
                await File.WriteAllBytesAsync(localFilePath1, fileBytes1);
                Console.WriteLine($"Первый файл скачан: {localFilePath1}\n");
            }
            catch (HttpRequestException ex)
            {
                Console.WriteLine($"Ошибка скачивания первого файла: {ex.Message}");
                return;
            }

            try
            {
                Console.WriteLine("Скачиваю второй файл...");
                string csvContent = await client.GetStringAsync(urlSecond);

                ExcelPackage.License.SetNonCommercialPersonal("test");
                using (var package = new ExcelPackage())
                {
                    var worksheet = package.Workbook.Worksheets.Add("Данные");

                    var lines = csvContent.Split(new[] { '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
                    for (int i = 0; i < lines.Length; i++)
                    {
                        var cells = lines[i].Split(',');
                        for (int j = 0; j < cells.Length && j < 20; j++)
                        {
                            worksheet.Cells[i + 1, j + 1].Value = cells[j].Trim('\"');
                        }
                    }

                    await package.SaveAsAsync(new FileInfo(localFilePath2));
                }
                Console.WriteLine($"Второй файл скачан и сконвертирован: {localFilePath2}\n");
            }
            catch (HttpRequestException ex)
            {
                Console.WriteLine($"Ошибка скачивания второго файла: {ex.Message}");
                return;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка обработки второго файла: {ex.Message}");
                return;
            }
        }

        Thread thread1 = new Thread(() => ReadExcelSheet(localFilePath1, 0, 1, "Файл1"));
        Thread thread2 = new Thread(() => ReadExcelSheet(localFilePath2, 0, 2, "Файл2"));

        thread1.Name = "Поток-Файл1";
        thread2.Name = "Поток-Файл2";

        PrintThreadInfo(thread1);
        PrintThreadInfo(thread2);

        Console.WriteLine("\n ЗАПУСК ПОТОКОВ ");

        thread1.Start();
        Console.WriteLine($"{thread1.Name} запущен");

        Thread.Sleep(100);

        thread2.Start();
        Console.WriteLine($"{thread2.Name} запущен");

        PrintThreadInfo(thread1);
        PrintThreadInfo(thread2);

        thread1.Join();
        thread2.Join();

        Console.WriteLine("\n Все потоки завершили работу ");
        Console.ReadKey();
    }

    static void ReadExcelSheet(string filePath, int sheetIndex, int threadId, string fileName)
    {
        Thread currentThread = Thread.CurrentThread;
        Console.WriteLine($"\n[{currentThread.Name}] Начало чтения {fileName}");
        Console.WriteLine($"[{currentThread.Name}] ID потока: {currentThread.ManagedThreadId}");

        if (threadId == 1)
        {
            Thread.Sleep(3000);
        }

        try
        {
            ExcelPackage.License.SetNonCommercialPersonal("test");

            using (var package = new ExcelPackage(new FileInfo(filePath)))
            {
                if (sheetIndex >= package.Workbook.Worksheets.Count)
                {
                    Console.WriteLine($"[{currentThread.Name}] Лист #{sheetIndex + 1} не найден. Всего листов: {package.Workbook.Worksheets.Count}");
                    return;
                }

                var worksheet = package.Workbook.Worksheets[sheetIndex];

                Console.WriteLine($"[{currentThread.Name}] Имя листа: {worksheet.Name}");
                Console.WriteLine($"[{currentThread.Name}] Статус: {currentThread.ThreadState}");

                int rowCount = worksheet.Dimension?.Rows ?? 0;
                int colCount = worksheet.Dimension?.Columns ?? 0;

                Console.WriteLine($"[{currentThread.Name}] Всего строк: {rowCount}, колонок: {colCount}");

                int rowsToShow = Math.Min(10, rowCount);
                int colsToShow = Math.Min(6, colCount);

                Console.WriteLine($"\n[{currentThread.Name}] СОДЕРЖИМОЕ:");
                Console.WriteLine($"[{currentThread.Name}] {new string('=', 70)}");

                string header = "";
                for (int col = 1; col <= colsToShow; col++)
                {
                    string value = worksheet.Cells[1, col].Value?.ToString() ?? "";
                    header += (value.Length > 18 ? value.Substring(0, 15) + "..." : value).PadRight(20);
                }
                Console.WriteLine($"[{currentThread.Name}] {header}");
                Console.WriteLine($"[{currentThread.Name}] {new string('-', 70)}");

                for (int row = 2; row <= rowsToShow; row++)
                {
                    string rowText = "";
                    for (int col = 1; col <= colsToShow; col++)
                    {
                        var cellValue = worksheet.Cells[row, col].Value;
                        string valueStr = cellValue?.ToString() ?? "";

                        if (valueStr.Length > 18)
                            valueStr = valueStr.Substring(0, 15) + "...";

                        rowText += valueStr.PadRight(20);
                    }
                    Console.WriteLine($"[{currentThread.Name}] {rowText}");

                    Thread.Sleep(50);
                }

                Console.WriteLine($"[{currentThread.Name}] {new string('=', 70)}");
                Console.WriteLine($"[{currentThread.Name}] Показаны первые {rowsToShow} из {rowCount} строк");
                Console.WriteLine($"[{currentThread.Name}] Чтение завершено");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{currentThread.Name}] ОШИБКА: {ex.Message}");
        }
    }

    static void PrintThreadInfo(Thread thread)
    {
        Console.WriteLine($"Имя: {thread.Name ?? "Без имени"}");
        Console.WriteLine($"ID: {thread.ManagedThreadId}");
        Console.WriteLine($"Статус: {thread.ThreadState}");
        Console.WriteLine($"Приоритет: {thread.Priority}");
        Console.WriteLine($"Живой: {thread.IsAlive}");
        Console.WriteLine(new string('-', 35));
    }
}