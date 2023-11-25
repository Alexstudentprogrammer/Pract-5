#include <string>
#include <iostream>
#include <fstream>
#include "Test.h"
#include "Solver.h"
#include <chrono>
#include <ctime>

using namespace std;

void printTheArray(int arr[], int n, fstream& in)
{
	for (int i = 0; i < n; i++) {
		in << arr[i];
	}
	in << endl;
}

// Function to generate all binary strings
void generateAllBinaryStrings(int n, int arr[], int i, fstream& in, int &printed, int &want)
{
	if (i == n && printed < want) {
		printed++;
		printTheArray(arr, n, in);
		return;
	}
	else if (i == n) {
		return;
	}

	// First assign "0" at ith position
	// and try for all other permutations
	// for remaining positions
	arr[i] = 0;
	generateAllBinaryStrings(n, arr, i + 1, in, printed, want);

	// And then assign "1" at ith position
	// and try for all other permutations
	// for remaining positions
	arr[i] = 1;
	generateAllBinaryStrings(n, arr, i + 1, in, printed, want);
}

void Test::upload(string file_path) {
	fstream io(file_path);
	io >> number_of_words;
	nth_word_length = new int[number_of_words];

	for (int i = 0; i < number_of_words; i++) {
		io >> nth_word_length[i];
		
	}
	io.get(); // to move on next line
	words = new char* [number_of_words];
	for (int i = 0; i < number_of_words; i++) {
		words[i] = new char[nth_word_length[i]];
		io.getline(words[i], (std::streamsize)nth_word_length);
	}
	
}

void Test::run_test(string file_path) {
	upload(file_path);
	Solver solver(words, number_of_words, nth_word_length);

	clock_t start_clock = clock();
	solver.solve();
	clock_t duration = clock() - start_clock;
	cout << "Time, for test: " << (double)duration / CLOCKS_PER_SEC << endl;

}

void Test::run_stress_test1(int n, int count) {
	fstream io("Tests/stress_test.txt");
	io << (count);
	io << endl;
	for (int i = 0; i < count; i++) {
		io << n;
		if (i != (count - 1))
			io << " ";
	}
	io << endl;
	int *arr = new int[n];

	int printed = 0, want = count;
	generateAllBinaryStrings(n, arr, 0, io, printed, count);

	upload("Tests/stress_test.txt");
	Solver solver(words, number_of_words, nth_word_length);

	clock_t start_clock = clock();
	solver.solve();
	clock_t duration = clock() - start_clock;
	cout << (double)duration / CLOCKS_PER_SEC << endl;
}

void Test::run_stress_test2(int n) {
	// only odd n 
	fstream io("Tests/stress_test_2.txt");
	io << (pow(2, n) + 2);
	io << endl;
	for (int i = 0; i < pow(2, n); i++) {
		io << n;
		io << " ";
	}
	io << 3;
	io << " ";
	io << 3;

	io << endl;
	int* arr = new int[n + 2];
	int printed = 0, wanted = n;
	generateAllBinaryStrings(n, arr, 0, io, printed, wanted);
	io << 101;
	io << endl;
	io << 111;


	upload("Tests/stress_test_2.txt");
	Solver solver(words, number_of_words, nth_word_length);

	clock_t start_clock = clock();
	solver.solve();

	clock_t duration = clock() - start_clock;
	cout << "Removing elements : " << (double)duration / CLOCKS_PER_SEC << endl;
}