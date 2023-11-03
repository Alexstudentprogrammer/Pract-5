#include<string>
#include<iostream>
#include<fstream>
#include "Test.h"
#include "Solver.h"

using namespace std;

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
	solver.solve();

}