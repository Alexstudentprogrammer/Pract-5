#pragma once

using namespace std;
class Triplet {
public:
	int length;
	int wordNumber;
	int start;
	int end;
	string prefix;
	string suffix;
	string word;


	Triplet(
		int start,
		int end,
		int wordNumber,
		int length,
		string prefix,
		string suffix,
		string word
	) {
		this->start = start;
		this->end = end;
		this->wordNumber = wordNumber;
		this->length = length;
		this->prefix = prefix;
		this->suffix = suffix;
		this->word = word;
	}

	Triplet() {

	}

	bool operator ==(const Triplet& triplet) const
	{
		if (
			(this->start == triplet.start) &&
		        (this->end == triplet.end) &&
			(this->wordNumber == triplet.wordNumber) &&
			(this->length == triplet.length)
			) {
			return true;
		}
		return false;
	}
public:
	struct HashFunction
	{
		size_t operator()(const Triplet& triplet) const
		{
			size_t startHash = std::hash<int>()(triplet.start);
			size_t endHash = std::hash<int>()(triplet.end) << 1;
			size_t wordNumberHash = std::hash<int>()(triplet.wordNumber) << 2;
			size_t lengthHash = std::hash<int>()(triplet.length) << 3;
			return (startHash ^ endHash ^ wordNumberHash ^ lengthHash) % 100;
		}
	};
};

