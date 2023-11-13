#pragma once
#include<iostream>
#include <exception>


class IndexOutOfBounds : public std::exception {
public:
	const int size;
	const int current_index;
	IndexOutOfBounds(int size, int current_index) : size(size), current_index(current_index) {}

};
