#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>

using namespace std;

class Operations
{
public:

	int Add(int a,int b) {
		int res = a + b;
		return res;
	}

	float Add(float a, float b) {
		float res = a + b;
		return res;

	}
		
	int Add(int a, int b, int c) {
		int res = a + b;
		return res;
	}

	double Average(const vector<double>& values) {
		double res = 0;
		int i = 0;

		for (double value : values)
		{
			res += value;
			i++;
		}
		double res_value = res / i;

		return res_value;
	}

	string Concat(const string& a, const string& b) {
		string res = a + b;
		return res;
	}
			
	string Concat(const vector<string>& strs) {
		string res_string;
		int i = 0;

		for (string value : strs)
		{
			res_string += value;
		}

		return res_string;
	}
};

void Menu() {
	cout << "1 - Сложение двух целых чисел" << endl
		<< "2 - Сложение двух вещественных чисел" << endl
		<< "3 - Сумма трёх целых" << endl
		<< "4 - Среднее арифметическое любого количества вещественных значений (передаётся вектор)" << endl
		<< "5 - Конкатенация двух строк" << endl
		<< "6 - Конкатенация произвольного количества строк (передаётся вектор)" << endl;
}

void CLear() {
	int clear;
	cout << "Очистить консоль?(1- да, 0 - нет): "; cin >> clear;
	if (clear == 1)
	{
		system("cls");
	}
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	Operations oper;
	ofstream input("data.txt");
	int choice;
	string res;

	do {
		Menu();
		cout << "Введите операцию: "; cin >> choice;
		switch (choice) {

		case 1: {
			int a, b;
			cout << "Введи первое число:"; cin >> a;
			cout << "Введи второе число:"; cin >> b;
			res = to_string(oper.Add(a, b));

			if (input.is_open())
			{
				input << "Сложение двух целых чисел: " << endl;
				input << "Первое число: " << a << endl;
				input << "Второе число: " << b << endl;
				input << "Результат: " << res << endl;
				input << endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
			break;
		}
		case 2:
		{
			float a, b;
			cout << "Введи первое число:"; cin >> a;
			cout << "Введи второе число:"; cin >> b;
			res = to_string(oper.Add(a, b));

			if (input.is_open())
			{
				input << "Сложение двух вещественных чисел: " << std::endl;
				input << "Первое число: " << a << std::endl;
				input << "Второе число: " << b << std::endl;
				input << "Результат: " << res << std::endl;
				input << std::endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
		}
		break;

		case 3:;
		{
			int a, b, c;
			cout << "Введи первое число:"; cin >> a;
			cout << "Введи второе число:"; cin >> b;
			cout << "Введи третье число:"; cin >> c;

			res = to_string(oper.Add(a, b, c));

			if (input.is_open())
			{
				input << "Сумма трёх целых: " << std::endl;
				input << "Первое число: " << a << std::endl;
				input << "Второе число: " << b << std::endl;
				input << "Третье число: " << b << std::endl;
				input << "Результат: " << res << std::endl;
				input << std::endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
			break;
		}

		case 4: {
			vector<double> values;
			int add = 1;
			while (add == 1) {
				double value = 0;

				cout << "Введите число: "; cin >> value;
				values.push_back(value);
				cout << "Добавить еще?(1 - да, 0 - нет)"; cin >> add;
			}

			res = to_string(oper.Average(values));

			if (input.is_open())
			{
				input << "Среднее арифметическое любого количества вещественных значений (передаётся вектор): " << std::endl;
				input << "Содержимое вектора: ";
				for (double value : values)
				{
					input << value << " ";
				}
				input << std::endl;
				input << "Результат: " << res << std::endl;
				input << std::endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
			break;
		}
		case 5:
		{
			string a, b;
			cout << "Введи первую строку:"; cin >> a;
			cout << "Введи вторую строку:"; cin >> b;
			

			res = oper.Concat(a, b);

			if (input.is_open())
			{
				input << "Конкатенация двух строк: " << std::endl;
				input << "Первая строка: " << a << std::endl;
				input << "Вторая строка: " << b << std::endl;
				input << "Результат: " << res << std::endl;
				input << std::endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
			break;
		}
		case 6: {
			vector<string> values;
			int add = 1;
			while (add == 1) {
				string value ;
				cout << "Введите строку: "; cin >> value;
				values.push_back(value);
				cout << "Добавить еще?(1 - да, 0 - нет)"; cin >> add;
			}

			res = oper.Concat(values);

			if (input.is_open())
			{
				input << "Среднее арифметическое любого количества вещественных значений (передаётся вектор): " << std::endl;
				input << "Содержимое вектора: ";
				for (string value : values)
				{
					input << value << ", ";
				}
				input << std::endl;
				input << "Результат: " << res << std::endl;
				input << std::endl;
			}
			else
			{
				cout << "Файл не был открыт\n";
			}
			CLear();
			break;
		}

		case 0:
			break;
		break;

		default:
			cout << "Такого варианта нет" << endl;
			CLear();
			break;
		}



	} while (choice != 0);






	return 0;
}