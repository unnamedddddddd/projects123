#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>

using namespace std;

vector<vector<int>> SplitArray(vector<int> &arr1, size_t &n){
	if (n == 0) throw invalid_argument("n cannot be zero");
	vector<vector<int>> res_arr(n);

	size_t totalSize = arr1.size();
	size_t chuntSize = totalSize / n;
	size_t remainder = totalSize % n;

	size_t index = 0;

	for (size_t i = 0; i < n; ++i)
	{
		size_t currentSize = chuntSize + (i < remainder ? 1 : 0);
		for (size_t j = 0; j < currentSize; ++j)
		{
			res_arr[i].push_back(arr1[index++]);
		}
	}

	return res_arr;
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
	try
	{
		size_t sizeMainArray,sizeArrays;
		cout << "Введите размер массива: ";
		while (!(cin >> sizeMainArray)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Ошибка: Неверный формат. Введите число: ";
		}

		cout << "Введите кол-во массивов: ";
		while (!(cin >> sizeArrays)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Ошибка: Неверный формат. Введите число: ";
		}

		vector<int> main_arr(sizeMainArray);

		auto splitArrays = SplitArray(main_arr,sizeArrays);
 		cout << "\nРезультат разделения:" << endl;
        for (size_t i = 0; i < splitArrays.size(); ++i) {
            cout << "Часть " << i + 1 << " (размер: " << splitArrays[i].size() << "): ";
            for (int num : splitArrays[i]) {
                cout << num << " ";
            }
            cout << endl;
        }
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	

	

	







	
	// int num_threads;
	
	// cout << "Введите число потоков(от 1 - 4): ";
	// while (!(cin >> num_threads) || (num_threads < 1 || num_threads > 4)) {
	// 	cin.clear();
	// 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// 	cerr << "Ошибка: Неверный формат. Введите число: ";
	// }

	// vector<int> arr(size_array);
	// for (int i = 0; i < 100; ++i)
	// {
	// 	arr[i] = i + 1;
	// }

	// auto parts = splitArray(arr, size_array);
	// vector<thread> threads;
	// threads.reserve(num_threads);

	// for (int i = 0; i < num_threads; ++i)
	// {
	// 	threads.emplace_back(TwoArrays, arr, arr);
	// }

	// for (auto& thread : threads) {
	// 	thread.join();
	//}
	return 0;
	
}