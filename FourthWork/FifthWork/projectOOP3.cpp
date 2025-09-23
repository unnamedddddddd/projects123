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
					cout << "Имя: " << m_j["name"].get<string>() << endl;
				}
				if (m_j.contains("place") && m_j["place"].is_string()) {
					cout << "Place: " << m_j["place"].get<string>() << endl;
				}
				if (m_j.contains("start") && m_j["start"].is_string()) {
					cout << "Start: " << m_j["start"].get<string>() << endl;
				}
				if (m_j.contains("end") && m_j["end"].is_string()) {
					cout << "End: " << m_j["end"].get<string>() << endl;
				}
				if (m_j.contains("budget") && m_j["budget"].is_number_float()) {
					cout << "Budget: " << m_j["budget"].get<float>() << endl;
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
	locale::global(locale(""));
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	/*
	ifstream out("data.json");
	if (out.is_open())
	{
		j = json::parse(out);
		if (j.is_object())
		{
            if (j.contains("name") && j["name"].is_string()) {
				cout << "Имя: " << j["name"].get<string>() << endl;
            }
			if (j.contains("age") && j["age"].is_number_integer()) {
				cout << "Age: " << j["age"].get<int>() << endl;
			}
		}
		out.close();*/
	

	Agency agent("Denis папап ","Russia","21.09.2025","27.09.2025",23324.4);
	agent.InputFile();
	agent.OutputFile();


	return 0;
}
