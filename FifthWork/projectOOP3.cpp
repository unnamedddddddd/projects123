#include <iostream>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <string>
#include <limits>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Product
{
public:	
	virtual void InputFile() = 0;
};

class Agency : public Product
{
	string m_FIO;
	string m_Place;
	string m_Start;
	string m_End;
	float m_Budget = 0;
	json m_j;
 public:
	Agency(string FIO, string Place, string Start, string End, float Budget){
		m_j["name"] = FIO;
		m_j["place"] = Place;
		m_j["start"] = Start;
		m_j["end"] = End;
		m_j["budget"] = Budget;
	}

	void InputFile() override {
		ofstream input("data2.json");
		if (input.is_open())
		{
			input << m_j.dump(4);
		}
		else
		{
			cout << "Файл не был открыт\n";
		}
	}
	
	void OutputFile() {

		ifstream out("data2.json");
		if (out.is_open())
		{
			m_j = json::parse(out);
			if (m_j.is_object())
			{
				if (m_j.contains("name") && m_j["name"].is_string()) {
					cout << u8"Имя: " << m_j["name"].get<string>() << endl;
				}
				if (m_j.contains("place") && m_j["place"].is_string()) {
					cout << u8"Место: " << m_j["place"].get<string>() << endl;
				}
				if (m_j.contains("start") && m_j["start"].is_string()) {
					cout << u8"Начало поездки: " << m_j["start"].get<string>() << endl;
				}
				if (m_j.contains("end") && m_j["end"].is_string()) {
					cout << u8"Конец поездки: " << m_j["end"].get<string>() << endl;
				}
				if (m_j.contains("budget") && m_j["budget"].is_number_float()) {
					cout << u8"Бюджет: " << m_j["budget"].get<float>() << endl;
				}
			}
			out.close();
		}
		else
		{
			cout << "Файл не был открыт\n";
		}
	}
};

int main()
{
	try {
		setlocale(LC_ALL, "ru_RU.UTF-8");
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		int choice = 1;
		do {
			string name, place, start, end;
			float budget = 0.0;
			cout << u8"Введите ФИО: ";
			getline(cin, name);

			cout << u8"Место поездки: ";
			getline(cin, place);

			cout << u8"Начало поездки: ";
			getline(cin, start);
			stof(start);

			cout << u8"Конец поездки: ";
			getline(cin, end);
			stof(end);

			cout << u8"Бюджет: ";
			string budgetStr;
			getline(cin, budgetStr);
			try {
				budget = stof(budgetStr);
			}
			catch (...) {
				throw runtime_error(u8"Бюджет должен быть числом!");
			}

			Agency agent(name, place, start, end, budget);
			agent.InputFile();
			agent.OutputFile();

			cout << u8"Продолжить? (1 - да, 0 - нет): ";
			string choiceStr;
			getline(cin, choiceStr);
			try {
				choice = stoi(choiceStr);
			}
			catch (...) {
				throw runtime_error(u8"Ошибка: введите 0 или 1!");
			}

		} while (choice != 0);
		return 0;
	}
	catch (const std::invalid_argument& e) {
		cout << u8"Неверный формат числа";
	}
	catch(exception &ex){
		cerr << u8"Ошибка: " << ex.what() << endl;
	}
	
}
