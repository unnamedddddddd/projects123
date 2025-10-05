#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Figure {
protected:
    int m_Wigth = 0;
    int m_Heigth = 0;
public:
    Figure() = default;

    virtual int getArea() = 0;

    void setWidth(int w) { 
        m_Wigth = w;
    }

    void setHeight(int h) {
        m_Heigth = h;
    }

    virtual ~Figure() {
        cout << "Destructor Figure" << endl;
    };

};

class Triangle : public Figure
{
public:
    Triangle(int wigth, int heigth) {
        setWidth(wigth);
        setHeight(heigth);
    }

    int getArea() {
        return (m_Wigth * m_Heigth);
    }  

    ~Triangle() override {
        cout << "Destructor Triangle" << endl;
    };
};

class Parallelogram : public Figure
{
public:
    Parallelogram(int wigth, int heigth) {
        setWidth(wigth);
        setHeight(heigth);
    }

    int getArea() {
        return (m_Wigth * m_Heigth);
    }

    ~Parallelogram() override{
        cout << "Destructor Parallelogram" << endl;
    };
};


unique_ptr<Figure> Factory(string& figure, const int &wigth, const int &heigth) {

    if (figure == "треугольник")
    {
        cout << "Создался объект треугольник" << endl;
        return make_unique<Triangle>(wigth, heigth);
        
    }
    else if(figure == "параллелограмм")
    {
        cout << "Создался объект параллелограмм" << endl;
        return make_unique<Parallelogram>(wigth, heigth);
    }
    else
    {
        cout << "Неверная фигура" << endl;
        return nullptr;
    }
    return nullptr;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        vector<unique_ptr<Figure>> figures;

        int choice = 0;
        do
        { 
            string figure;
            cout << "Выберите фигуру(треугольник, параллелограмм): "; cin >> figure;

            int wigth;
            cout << "Введите ширину: "; cin >> wigth;
            
            int heigth;
            cout << "Введите высоту: "; cin >> heigth;
            cout << endl;

            figures.push_back(move(Factory(figure, wigth, heigth)));
            cout << endl;

            cout << "Добавить еще? (1 - да, 0 - нет): ";
            cin >> choice;
            cout << endl;

        } while (choice == 1);

        return 0;
    }
    catch (const invalid_argument& ex) {
        cerr << ex.what();
    }
    catch (const exception& ex) {
        cerr << ex.what();
    }
}

