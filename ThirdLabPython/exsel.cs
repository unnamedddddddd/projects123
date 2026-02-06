using OfficeOpenXml;
using System;
using System.IO;

class Program
{
    static void Main()
    {
        ExcelPackage.LicenseContext = LicenseContext.NonCommercial;

        string projectFolder = @"C:\Users\denis\source\repos\projects123";
        string filePath = Path.Combine(projectFolder, "exselTest.xlsx");

        try
        {
            if (!File.Exists(filePath))
            {
                Console.WriteLine($"Файл не найден: {filePath}");
                return;
            }

            using (var package = new ExcelPackage(new FileInfo(filePath)))
            {
                if (package.Workbook.Worksheets.Count == 0)
                {
                    Console.WriteLine("Файл не содержит листов");
                    return;
                }

                var worksheet = package.Workbook.Worksheets[0];

                if (worksheet.Dimension == null)
                {
                    Console.WriteLine("Лист пуст");
                    return;
                }

                Console.WriteLine("Содержимое файла:");
                Console.WriteLine($"Лист: {worksheet.Name}");

                int rows = worksheet.Dimension.Rows;
                int cols = worksheet.Dimension.Columns;

                for (int row = 1; row <= rows; row++)
                {
                    for (int col = 1; col <= cols; col++)
                    {
                        var value = worksheet.Cells[row, col].Value;
                        Console.Write($"{value?.ToString() ?? "[пусто]"}\t");
                    }
                    Console.WriteLine();
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("\nНажмите Enter...");
        Console.ReadLine();
    }
}