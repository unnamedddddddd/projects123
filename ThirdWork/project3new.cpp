#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>
#include <mutex>

using namespace std;
using namespace chrono;

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

vector<int> global_result;
mutex mtx;

void File(vector<int> &res_arr) {
	lock_guard<mutex> lg();
	ofstream input("result.txt");
	if (input.is_open())
	{
		for (int i = 0; i < res_arr.size(); ++i)
		{
			input << res_arr[i] << " ";
			
		}
	}
	else
	{
		throw runtime_error("Ошибка в открытие файла");
	}
	
}
	
void TwoArrays(const vector<int>& arr1, const vector<int>& arr2,int startIndex) {
    auto start = high_resolution_clock::now();
    
    vector<int> local_result;
    local_result.reserve(min(arr1.size(), arr2.size()));
    
    for (size_t i = 0; i < min(arr1.size(), arr2.size()); ++i) {
        local_result.push_back(arr1[i] * arr2[i]);
    }
    
    {
        lock_guard<mutex> lock(mtx);
        
        for (size_t i = 0; i < local_result.size(); ++i) {
            global_result.push_back(local_result[i]);
        }
    }
    
    auto end = high_resolution_clock::now();
    auto res_time = duration_cast<milliseconds>(end - start);
	mtx.lock();
	cout << "Поток с id: " << this_thread::get_id() << " закончил работу за : " << res_time.count() <<" c"<< endl;
	mtx.unlock();
	File(global_result);
}

int main() {
	try
	{
		size_t sizeMainArray,sizeArrays;
		cout << "Введите размер массива: ";
		while (!(cin >> sizeMainArray || sizeMainArray == 0)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Ошибка: Неверный формат. Введите число: ";
		}

		cout << "Введите кол-во массивов: ";
		while (!(cin >> sizeArrays || sizeArrays == 0)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Ошибка: Неверный формат. Введите число: ";
		}

		int num_threads;
		cout << "Введите число потоков(от 1 - 4): ";
		while (!(cin >> num_threads)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Ошибка: Неверный формат. Введите число: ";
		}

		vector<int> main_arr(sizeMainArray);
		for (int i = 0; i < sizeMainArray; ++i)
		{
			main_arr[i] = i;
		}

		auto splitArrays = SplitArray(main_arr,sizeArrays);
		vector<thread> threads {};
		threads.reserve(num_threads);

		size_t arrays_available = splitArrays.size();
        if (arrays_available < 2) {
            cerr << "Ошибка: нужно как минимум 2 массива для умножения" << endl;
            return 0;
        }

		for (int i = 0; i < num_threads; ++i) {
            size_t arr1 = i % arrays_available;
            size_t arr2 = (i + 1) % arrays_available;

            threads.emplace_back(TwoArrays, cref(splitArrays[arr1]), cref(splitArrays[arr2]),3);
        }

		for (auto& thread : threads) {
			thread.join();
		}

		return 0;
	}
	catch(const exception& e)
	{
		cerr << e.what() << '\n';
	}
}