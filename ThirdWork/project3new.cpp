#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

vector<vector<int>> splitArray(const vector<int>& arr, size_t n) {
    vector<vector<int>> result;
    
    if (n > arr.size()) n = arr.size();
   
    float base_size = arr.size() / n;
    float remainder = arr.size() % n;
    size_t start_index = 0;
    
    for (int i = 0; i < n; ++i) {
        size_t current_size = base_size + (i < remainder ? 1 : 0);
        vector<int> part(arr.begin() + start_index, arr.begin() + start_index + current_size);
        result.push_back(part);
        start_index += current_size;
    }
    
    return result;
}

void File(int res_arr[]) {
	ofstream input("data.txt");

	if (input.is_open())
	{
		for (int i = 0; i < 250000000; ++i)
		{
			input << res_arr[i] << " ";
		}
	}
	else
	{
		cout << "Файл не был открыт";
	}
}

void TwoArrays(vector<int> arr1, vector<int> arr2) {
	auto start = chrono::high_resolution_clock::now();

	vector<int> res_arr;
	res_arr.reserve(arr1.size());

	for (int i = 0; i < arr1.size(); ++i)
	{
		res_arr.push_back((arr1[i]) * (arr2[i]));
	}

	auto end = chrono::high_resolution_clock::now();
	auto res_time = chrono::duration_cast<chrono::milliseconds>(end - start);

	for (auto num : res_arr)
	{
		cout << num << " ";
		if (num == 10)
		{
			break;
		}
	}
	
	cout << " time: " << res_time.count() << " ms" << endl;
}

int main() {
	int num_threads;
	size_t size_array;
	cout << "Введите размер массива: ";
	while (!(cin >> size_array)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "Ошибка: Неверный формат. Введите число: ";
	}

	cout << "Введите число потоков(от 1 - 4): ";
	while (!(cin >> num_threads) || (num_threads < 1 || num_threads > 4)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "Ошибка: Неверный формат. Введите число: ";
	}

	vector<int> arr(size_array);
	for (int i = 0; i < 100; ++i)
	{
		arr[i] = i + 1;
	}

	auto parts = splitArray(arr, size_array);
	vector<thread> threads;
	threads.reserve(num_threads);

	for (int i = 0; i < num_threads; ++i)
	{
		threads.emplace_back(TwoArrays, arr, arr);
	}

	for (auto& thread : threads) {
		thread.join();
	}
	
}