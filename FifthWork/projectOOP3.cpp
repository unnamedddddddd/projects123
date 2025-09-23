#include <iostream>
#include <fstream>
#include <locale>
#include <Windows.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Product
{
protected:
	int m_Id = 0;
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
		ofstream input("data.json");
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

		ifstream out("data.json");
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
					cout << u8"Бюджет: " << m_j["budget"].get<float>() << endl << endl;
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
			cout << u8"Введите ФИО: ";  getline(cin, name);
			cout << u8"Место поездки: "; getline(cin, place);
			cout << u8"Начало поездки: ";  getline(cin, start);
			cout << u8"Конец поездки: ";  getline(cin, end);
			cout << u8"Бюджет: "; cin >> budget;
			cout << endl;
			if (cin.fail()) {
				cout << "Ошибка: не тот тип" << endl;
				cin.clear();
				continue;
			}

			Agency agent(name, place, start, end, budget);
			agent.InputFile();
			agent.OutputFile();

			cout << u8"Продолжить?(1 - да, 0 - нет)" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(32767, '\n');

		} while (choice != 0);
		return 0;
	}
	catch(exception &ex){
		cerr << ex.what() << endl;
	
	}
	
}
