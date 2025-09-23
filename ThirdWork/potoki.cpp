#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>
#include <mutex>


using namespace std;
using namespace chrono;

void SplitArray(const vector<long long>& arr1, const vector<long long>& arr2,
    vector<vector<long long>>& res_arr1, vector<vector<long long>>& res_arr2, int n) {
    if (n <= 0) throw invalid_argument("Число потоков должно быть положительным");

    size_t totalSize = arr1.size();
    if (totalSize == 0) return;

    size_t chunkSize = totalSize / n;
    size_t remainder = totalSize % n;

    size_t start = 0;
    for (int i = 0; i < n; ++i) {
        size_t currentSize = chunkSize + (i < remainder ? 1 : 0);

        vector<long long> part1(arr1.begin() + start, arr1.begin() + start + currentSize);
        vector<long long> part2(arr2.begin() + start, arr2.begin() + start + currentSize);

        res_arr1[i] = move(part1);
        res_arr2[i] = move(part2);

        start += currentSize;
    }
}

vector<long long> global_result;
mutex mtx;

void FileInput(const vector<long long>& res_arr) {
    ofstream input("result.txt");
    if (input.is_open()) {
        for (size_t i = 0; i < res_arr.size(); ++i) {
            input << res_arr[i];
            if (i < res_arr.size() - 1) input << " ";
        }
        input.close();
        cout << "Файл успешно записан" << endl;
    }
    else {
        throw runtime_error("Ошибка при открытии файла для записи");
    }
}

void TwoArrays(const vector<long long>& arr1, const vector<long long>& arr2) {
    auto multi_start = high_resolution_clock::now();

    {
        lock_guard<mutex> lock(mtx);
        for (size_t i = 0; i < arr1.size(); ++i) {
            global_result.push_back(arr1[i] * arr2[i]);
        }
    }

    auto multi_end = high_resolution_clock::now();
    auto multi_time = duration_cast<milliseconds>(multi_end - multi_start);
    cout << "\nВремя потока с id: " << this_thread::get_id() << " : " << multi_time.count() << " мс" << endl;
}

void TwoSingleArrays(const vector<long long>& arr1, const vector<long long>& arr2) {
    for (size_t i = 0; i < arr1.size(); ++i) {
        global_result.push_back(arr1[i] * arr2[i]);
    }
}

int main() {
    try {
        setlocale(LC_ALL, "");
        long long sizeMainArray;

        cout << "Введите размер массива: ";
        while (!(cin >> sizeMainArray) || sizeMainArray == 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Ошибка: Неверный формат. Введите положительное число: ";
        }

        int num_threads;
        cout << "Введите число потоков (от 1 до 4): ";
        while (!(cin >> num_threads) || num_threads > 4 || num_threads < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Ошибка: Введите число от 1 до 4: ";
        }

        vector<long long> FirstMainArr(sizeMainArray);
        vector<long long> SecondMainArr(sizeMainArray);

        for (size_t i = 0; i < sizeMainArray; ++i) {
            FirstMainArr[i] = i + 1;
            SecondMainArr[i] = i + 1;
        }

        vector<vector<long long>> res_arr1(num_threads);
        vector<vector<long long>> res_arr2(num_threads);

        SplitArray(FirstMainArr, SecondMainArr, res_arr1, res_arr2, num_threads);

        auto single_start = high_resolution_clock::now();

        TwoSingleArrays(FirstMainArr, SecondMainArr);

        auto single_end = high_resolution_clock::now();
        auto single_time = duration_cast<milliseconds>(single_end - single_start);
        cout << "\nОднопоточное время: " << single_time.count() << " мс" << endl;

        global_result.clear();
        vector<thread> threads;
        threads.reserve(num_threads);

        auto multi_start = high_resolution_clock::now();

        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(TwoArrays, ref(res_arr1[i]), ref(res_arr2[i]));
        }

        for (auto& t : threads) {
            t.join();
        }

        auto multi_end = high_resolution_clock::now();
        auto multi_time = duration_cast<milliseconds>(multi_end - multi_start);
        cout << "\nМногопоточное время: " << multi_time.count() << " мс" << endl;

        // FileInput(global_result);

        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
}