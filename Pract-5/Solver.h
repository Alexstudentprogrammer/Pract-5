#pragma once
#include "Triplet.h"
#include<set> 
#include<vector>
#include<unordered_set>
#include<unordered_map>

using namespace std;

class Solver {
private:
	char** words;
	int number_of_words;
	int* length_of_nth_word;
	unordered_set<Triplet, Triplet::HashFunction> non_trivial_decompositions;
	vector<Triplet> vec_non_trivial_decompositions;
	unordered_set<string> alphabet;
	vector<string> vec_alphabet;
	unordered_map<string, unordered_set<string>> graph;

public:
	Solver(char** words, int verticalSize, int* horizontalSize) {
		this->length_of_nth_word = horizontalSize;
		this->number_of_words = verticalSize;
		this->words = words;
	}

	void solve() {
		for (
			int current_word_number = 0;
			current_word_number < number_of_words;
			current_word_number++
			) {
			int current_word_length = length_of_nth_word[current_word_number];

			for (int window = 0; window < current_word_length; window++) {//current word length
				for (int start = 0; start < current_word_length - window + 1; start++) {//added + 1
					int end = start + window;

					if (
						(window == 0 && start == 0) ||
						(window == 0 && end == current_word_length)
					) {
						continue;
					}
					
					char* tmp_prefix = new char [start + 1];
					char* tmp_suffix = new char[current_word_length - end + 1];
					char* tmp_middle_part = new char[end - start + 1];

					for (int i = 0; i < start; i++) {
						tmp_prefix[i] = words[current_word_number][i];
					}
					tmp_prefix[start] = '\0';

					for (int i = end, j = 0; i < current_word_length; i++, j++) {
						tmp_suffix[j] = words[current_word_number][i];
					}
					tmp_suffix[current_word_length - end] = '\0';

					for (int i = start, j = 0; i < end; i++, j++) {
						tmp_middle_part[j] = words[current_word_number][i];
					}
					tmp_middle_part[end - start] = '\0';
					string wordToCheck = string(tmp_middle_part);

					if (wordToCheck == "" || canComposeUsingGivenWords(wordToCheck)) {
						Triplet decomposition_candidate(
							start,
							end,
							current_word_number,
							current_word_length,
							string(tmp_prefix),
							string(tmp_suffix),
							string(tmp_middle_part)
						);
						non_trivial_decompositions.insert(decomposition_candidate);
					}
				}
			}
		}
		vec_non_trivial_decompositions.insert(
			vec_non_trivial_decompositions.end(),
			non_trivial_decompositions.begin(),
			non_trivial_decompositions.end()
		);
		generateBAlphabet(vec_non_trivial_decompositions);
	}
public:
	bool canComposeUsingGivenWords(string wordToCheck) {
		bool *canBeComposed = new bool[wordToCheck.length()];
		for (int i = 0; i < wordToCheck.length(); i++) {
			canBeComposed[i] = false;
		}
		//base of dynamics
		for (int i = 0; i < number_of_words; i++) {
			if (compare_strs(words[i], wordToCheck, 0, length_of_nth_word[i])) {
				canBeComposed[length_of_nth_word[i] - 1] = true;
			}
		}
		//step of dynamics
		for (int i = 1; i < wordToCheck.length(); i++) {
			if (canBeComposed[i]) {
				i++;// checking from next symbol
				for (int j = 0; j < number_of_words; j++) {
					if (compare_strs(words[j], wordToCheck, i, length_of_nth_word[j])) {
						canBeComposed[i + length_of_nth_word[j] - 1] = true;
					}
				}
			}
		}
		return canBeComposed[wordToCheck.length() - 1];
	}

	bool compare_strs(
		char* word,
		string word_to_check,
		int start_symbol,
		int wordSize
	) {
		if (word_to_check.length() - start_symbol < wordSize)
			return false;

		for (int i = 0, j = start_symbol; i < wordSize; i++, j++) {
			if (word_to_check[j] != word[i])
				return false;
		}
		return true;
	}

	void generateBAlphabet(vector<Triplet> decompositions) {
		for (int i = 0; i < vec_non_trivial_decompositions.size(); i++) {
			for (int j = 0; j < vec_non_trivial_decompositions.size(); j++) {

					int prefix = vec_non_trivial_decompositions[i].start;
					int word_of_prefix = vec_non_trivial_decompositions[i].wordNumber;
					int length_of_word = vec_non_trivial_decompositions[i].length;

					int suffix = vec_non_trivial_decompositions[j].end;
					int word_of_suffix = vec_non_trivial_decompositions[j].wordNumber;
					int length_of_word2 = vec_non_trivial_decompositions[j].length;

					int lengthOfSuffix1 = length_of_word2 - suffix;
					if (
						compare(
							prefix,
							word_of_prefix,
							length_of_word,
							suffix,
							word_of_suffix,
							length_of_word2,
							lengthOfSuffix1
						)
					) {
					if (prefix == 0) {
						char* part_of_alphabet = new char[1];
						part_of_alphabet[0] = '\0';
						alphabet.insert(string(part_of_alphabet));
						continue;
					}
					char* part_of_alphabet = new char[prefix + 1];
					for (int k = 0; k < prefix; k++) {
						part_of_alphabet[k] = words[word_of_prefix][k];
					}
					part_of_alphabet[prefix] = '\0';
					alphabet.insert(string(part_of_alphabet));
			        }
		     }
	    }
	alphabet.insert("");
    buildGraph();
	doDfs();
}
	void buildGraph() {
		vec_alphabet.insert(vec_alphabet.end(), alphabet.begin(), alphabet.end());
		for (int i = 0; i < vec_alphabet.size(); i++) {
			unordered_set<string> destinations;
			graph.emplace(vec_alphabet[i], destinations);
		}
		for (int i = 0; i < vec_non_trivial_decompositions.size(); i++) {
			Triplet triplet = vec_non_trivial_decompositions[i];
			if (
				alphabet.find(triplet.prefix) != alphabet.end() &&
				alphabet.find(triplet.suffix) != alphabet.end()
				) {
				graph.at(triplet.prefix).insert(triplet.suffix);
			}
		}
	}
	void doDfs() {
		unordered_set<string> visited;
		string startVertex = "";
		dfs(visited, startVertex, graph);
	}
	void dfs(
		unordered_set<string>& visited,
		string curVertex,
		unordered_map<string, unordered_set<string>>& graph
	) {
		cout << "current vertex: " << curVertex << endl;
		if (visited.find(curVertex) != visited.end()) {
			if (curVertex == "") {
				cout << "Not Ok" << endl;
			}
			return;
		}
		visited.emplace(curVertex);

			for (const auto& elem : graph.at(curVertex)) {
				dfs(visited, elem, graph);
			}
	}
private:
	bool compare(
		int prefix,
		int word_of_prefix,
		int length_of_prefix_word,
		int suffix,
		int word_of_suffix,
		int length_of_suffix_word,
		int length_of_the_suffix
	) {
		char* prefix_word = words[word_of_prefix];
		char* suffix_word = words[word_of_suffix];

		if (prefix != length_of_the_suffix) {
			 return false;

		}
		char* tmp_suffix = new char[length_of_the_suffix];
		for (int i = suffix, j = 0; i < length_of_suffix_word; i++, j++) {
			tmp_suffix[j] = suffix_word[i];
		}

		for (int i = 0; i < prefix; i++) {

			if (prefix_word[i] != tmp_suffix[i]) {
				return false;
			}
		}
		return true;
	}
};

