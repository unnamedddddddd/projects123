using System;
using System.Net.Http;
using System.IO;
using System.Threading.Tasks;
using OfficeOpenXml;

class Program
{
    static async Task Main()
    {
        string url = "https://go.microsoft.com/fwlink/?LinkID=521962";
        string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
        string localFilePath = Path.Combine(desktopPath, "data.xlsx");

        using (HttpClient client = new HttpClient())
        {
            client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");

            try
            {
                Console.WriteLine("Скачиваю файл...");
                byte[] fileBytes = await client.GetByteArrayAsync(url);
                await File.WriteAllBytesAsync(localFilePath, fileBytes);
                Console.WriteLine($"Файл скачан: {localFilePath}");
            }
            catch (HttpRequestException ex)
            {
                Console.WriteLine($"Ошибка скачивания: {ex.Message}");
                return;
            }
        }

        Console.WriteLine("\nЧитаю Excel файл...");
        ReadExcelFile(localFilePath);
    }

    static void ReadExcelFile(string filePath)
    {
        ExcelPackage.License.SetNonCommercialPersonal("test");

        using (var package = new ExcelPackage(new FileInfo(filePath)))
        {
            var worksheet = package.Workbook.Worksheets[0];

            Console.WriteLine($"Лист: {worksheet.Name}");
            Console.WriteLine(new string('=', 50));

            int rowCount = worksheet.Dimension?.Rows ?? 0;
            int colCount = worksheet.Dimension?.Columns ?? 0;

            Console.WriteLine($"Всего строк: {rowCount}, колонок: {colCount}");
            Console.WriteLine(new string('=', 50));

            int rowsToShow = Math.Min(20, rowCount);
            int colsToShow = Math.Min(8, colCount);

            for (int row = 1; row <= rowsToShow; row++)
            {
                string rowText = "";
                for (int col = 1; col <= colsToShow; col++)
                {
                    var cellValue = worksheet.Cells[row, col].Value;
                    string valueStr = cellValue?.ToString() ?? "";

                    if (valueStr.Length > 15)
                        valueStr = valueStr.Substring(0, 12) + "...";

                    rowText += valueStr.PadRight(18);
                }
                Console.WriteLine(rowText);

                if (row == 1)
                    Console.WriteLine(new string('-', 50));
            }

            Console.WriteLine(new string('=', 50));
            Console.WriteLine($"Показаны первые {rowsToShow} из {rowCount} строк");
            Console.WriteLine($"Размер файла: {new FileInfo(filePath).Length} байт");
        }
    }
}