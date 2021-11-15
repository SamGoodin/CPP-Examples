#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int search(vector<int> list, int start_idx, int end_idx) {

	// Find the midpoint of the list
	int midpoint = (start_idx + end_idx) / 2;

	// If the midpoint value is greater than the value below it
	if (list[midpoint] > list[midpoint - 1]) {

		// If the midpoint value is greater than the value above it
		if (list[midpoint] > list[midpoint + 1]) {
			// Return the midpoint index
			return midpoint;
		}

		// Otherwise, continue searching from midpoint+1 to end
		return search(list, midpoint + 1, end_idx);
	}

	// If the midpoint value is less than the value below it
	if (list[midpoint] < list[midpoint - 1]) {
		// Continue searching from start to midpoint-1
		return search(list, start_idx, midpoint - 1);
	}

}

int iteration_peak(vector<int> list) {

	int peak = list[0];
	for (int num : vector<int>(list.begin() + 1, list.end())) {
		if (num > peak) {
			peak = num;
		}
	}
	return peak;
}

int main() {

	vector<int> list_of_numbers;
	fstream peak_file;

	try {
		peak_file.open("peak.txt", ios::in);
		if (peak_file.is_open()) {
			int number;
			while (peak_file >> number) {
				//cout << number << endl;
				list_of_numbers.push_back(number);
			}
		}
		peak_file.close();

		auto start = chrono::high_resolution_clock::now();
		int index = iteration_peak(list_of_numbers);
		auto stop = chrono::high_resolution_clock::now();
		cout << iteration_peak(list_of_numbers) << endl;	
		cout << "Duration of iteration peak: ";
		cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << endl;

		start = chrono::high_resolution_clock::now();
		int idx = search(list_of_numbers, 0, list_of_numbers.size() - 1);
		stop = chrono::high_resolution_clock::now();
		cout << list_of_numbers[idx] << " at index " << idx << endl;
		cout << "Duration of divide and conquer: ";
		cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << endl;


	}
	catch (exception& e) {
		cout << "Standard exception: " << e.what() << endl;
	}
	catch (...) {
		cout << "Exception occurred." << endl;
	}
		
	return 0;
}