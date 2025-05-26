#include<iostream>
#include<vector>

using namespace std;

void printArr(vector <int> arr, int size) {
	for (int i = 0; i < size; i++) { cout << arr[i] << " "; }
	cout << endl;
}

void doSeries(int size, int* tmp1, int* tmp2, int* firstSeries, int* secSeries) {
	bool f = true;
	vector <int> fibonacci{ 0, 1 };
	for (int i = 0; i < fibonacci.size() && f; i++) {
		if (fibonacci[i + 1] < size) { fibonacci.push_back(fibonacci[i] + fibonacci[i + 1]); }
		else if (fibonacci[i + 1] == size) {
			*tmp1 = fibonacci[i - 1];
			*tmp2 = fibonacci[i];
			f = false;
		}
		else {
			*firstSeries = ((fibonacci[i - 1] + fibonacci[i]) - size) / 2;
			int ostatokOtDelNtmp2_empty_series = ((fibonacci[i - 1] + fibonacci[i]) - size) % 2;
			*secSeries = *firstSeries;
			if (ostatokOtDelNtmp2_empty_series > 0) { *firstSeries += 1; }
			*tmp1 = fibonacci[i - 1] - *firstSeries;
			*tmp2 = fibonacci[i] - *secSeries;
			f = false;
		}
	}
	fibonacci.clear();
}

void bubbleSort(vector <int>* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < (n - i - 1); j++) {
			if ((*arr)[j] > (*arr)[j + 1]) {
				auto temp = (*arr)[j];
				(*arr)[j] = (*arr)[j + 1];
				(*arr)[j + 1] = temp;
			}
		}
	}
}

void mergeSort(int symbolsAverage, int symbolsMaximum, vector <int>* averageFile, vector <int>* maxFile, vector <int>* minFile) {
	while (!(*averageFile).empty() && !(*maxFile).empty()) {
		for (int i = 0; i < symbolsAverage; i++) {
			minFile->push_back((*averageFile).at(0));
			averageFile->erase(averageFile->begin() + 0);
		}
		for (int i = 0; i < symbolsMaximum; i++) {
			minFile->push_back((*maxFile).at(0));
			maxFile->erase(maxFile->begin() + 0);
		}
	}
	if (averageFile->size() < maxFile->size() && (averageFile->size() != 0 || maxFile->size() != 0)) {
		bubbleSort(minFile, minFile->size());
		mergeSort(symbolsMaximum, (symbolsAverage + symbolsMaximum), maxFile, minFile, averageFile);
	}
	else if (averageFile->size() > maxFile->size() && (averageFile->size() != 0 || maxFile->size() != 0)) {
		bubbleSort(minFile, minFile->size());
		mergeSort((symbolsAverage + symbolsMaximum), symbolsMaximum, averageFile, minFile, maxFile);
	}
	else if (averageFile->size() == maxFile->size()) { bubbleSort(minFile, minFile->size()); }
}

void polyphaseSort(vector <int>* arr, int size) {
	int tmp1, tmp2, firstSeries = 0, secSeries = 0, empty = 0;
	doSeries(size, &tmp1, &tmp2, &firstSeries, &secSeries);
	empty = firstSeries + secSeries;

	vector <int> file1(tmp1 + firstSeries);
	vector <int> file2(tmp2 + secSeries);
	vector <int> file3;

	for (int i = 0; i < tmp1; i++) {
		file1[i] = (*arr)[0];
		arr->erase(arr->begin() + 0);
	}
	for (int i = 0; i < tmp2; i++) {
		file2[i] = (*arr)[0];
		arr->erase(arr->begin() + 0);
	}

	if (file1.size() < file2.size()) { mergeSort(1, 1, &file1, &file2, &file3); }
	else { mergeSort(1, 1, &file2, &file1, &file3); }

	int numberNotEmptyFile;
	if (!file1.empty()) numberNotEmptyFile = 1;
	else if (!file2.empty()) numberNotEmptyFile = 2;
	else  numberNotEmptyFile = 3;

	switch (numberNotEmptyFile) {
	case 1: file1.erase(file1.begin(), file1.begin() + empty);
		break;
	case 2:file2.erase(file2.begin(), file2.begin() + empty);;
		break;
	case 3:file3.erase(file3.begin(), file3.begin() + empty);;
		break;
	}

	arr->clear();
	while (size > 0) {
		switch (numberNotEmptyFile) {
		case 1: {
			arr->push_back(file1.at(0));
			file1.erase(file1.begin() + 0);
		}
			  break;
		case 2: {
			arr->push_back(file2.at(0));
			file2.erase(file2.begin() + 0);
		}
			  break;
		case 3: {
			arr->push_back(file3.at(0));
			file3.erase(file3.begin() + 0);
		}
			  break;
		}
		size--;
	}
}

int main() {
	setlocale(LC_CTYPE, "rus");
	int n = 25;
	vector <int> arr{ 16, 51, 8, 15, 24, 2, 1, 12, 7, 10, 3, 1, 24, 45, 43, 22, 34, 4, 3, 3, 33, 43, 4, 23, 34 };
	cout << "Массив до: " << endl;
	printArr(arr, n);

	polyphaseSort(&arr, n);

	cout << "Массив после: " << endl;;
	printArr(arr, n);

	return 0;
}