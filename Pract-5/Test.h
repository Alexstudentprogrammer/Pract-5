#pragma once
#include<string>

class Test {
	char** words;
	int number_of_words;
	int* nth_word_length;
private:
	void upload(std::string file_path);
public:
	void run_test(std::string file_path);
	void run_stress_test1(int n);
	void run_stress_test2(int n);//paste odd argument (number)
	void run_stress_test3(int n);
};