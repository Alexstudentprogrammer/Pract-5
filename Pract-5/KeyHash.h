#pragma once
#include<string>
#pragma warning(disable:4267)
struct KeyHash {
	int operator()(string& key)
	{
		size_t hash = 0;
		const char* temp = key.c_str();
		int keySize = key.length();
		for (int i = 0; i < keySize; ++i) {
			hash *= 85021;
			hash = hash + temp[i];
			hash %= 130253;
		}
		return hash % 100;
	}
};
