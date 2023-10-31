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
	int verticalSize;
	int* horizontalSize;
	unordered_set<Triplet, Triplet::HashFunction> decompositions;
	vector<Triplet> vecDecompositions;
	unordered_set<string> bAlphabet;
	vector<string> vecAlphabet;
	unordered_map<string, unordered_set<string>> graph;

public:
	Solver(char** words, int verticalSize, int* horizontalSize) {
		this->horizontalSize = horizontalSize;
		this->verticalSize = verticalSize;
		this->words = words;
	}

	void solve() {
		for (int p = 0; p < verticalSize; p++) {
			int currentWordLength = horizontalSize[p];

			for (int window = 0; window < currentWordLength; window++) {//current word length
				for (int start = 0; start < currentWordLength - window + 1; start++) {//added + 1
					int end = start + window;

					if ( // added to avoid redundant alphabet members
						(window == 0 && start == 0) ||
						(window == 0 && end == currentWordLength)
					) {
						continue;
					}
					
					char* tmpPrefix = new char [start + 1];
					char* tmpSuffix = new char[currentWordLength - end + 1];
					char* tmpWord = new char[end - start + 1];

					for (int i = 0; i < start; i++) {
						tmpPrefix[i] = words[p][i];
					}
					tmpPrefix[start] = '\0';

					for (int i = end, j = 0; i < currentWordLength; i++, j++) {
					tmpSuffix[j] = words[p][i];
					}
					tmpSuffix[currentWordLength - end] = '\0';

					for (int i = start, j = 0; i < end; i++, j++) {
						tmpWord[j] = words[p][i];
					}
					tmpWord[end - start] = '\0';
					string wordToCheck = string(tmpWord);

					if (wordToCheck == "" || canComposeUsingGivenWords(wordToCheck)) {
						Triplet triplet(
							start,
							end,
							p,
							currentWordLength,
							string(tmpPrefix),
							string(tmpSuffix),
							string(tmpWord)
						);
						decompositions.insert(triplet);
					}
				}
			}
		}
		vecDecompositions.insert(vecDecompositions.end(), decompositions.begin(), decompositions.end());
		generateBAlphabet(vecDecompositions);
	}
public:
	bool canComposeUsingGivenWords(string wordToCheck) {
		bool *canBeComposed = new bool[wordToCheck.length()];
		for (int i = 0; i < wordToCheck.length(); i++) {
			canBeComposed[i] = false;
		}
		//base of dynamics
		for (int i = 0; i < verticalSize; i++) {
			if (compare_strs(words[i], wordToCheck, 0, horizontalSize[i])) {
				canBeComposed[horizontalSize[i] - 1] = true;
			}
		}
		//step of dynamics
		for (int i = 1; i < wordToCheck.length(); i++) {
			if (canBeComposed[i]) {
				i++;// checking from next symbol
				for (int j = 0; j < verticalSize; j++) {
					if (compare_strs(words[j], wordToCheck, i, horizontalSize[j])) {
						canBeComposed[i + horizontalSize[j] - 1] = true;
					}
				}
			}
		}
		return canBeComposed[wordToCheck.length() - 1];
	}

	bool compare_strs(
		char* word,
		string wordToCheck,
		int startSymbol,
		int wordSize
	) {
		if (wordToCheck.length() - startSymbol < wordSize)
			return false;

		for (int i = 0, j = startSymbol; i < wordSize; i++, j++) {
			if (wordToCheck[j] != word[i])
				return false;
		}
		return true;
	}

	void generateBAlphabet(vector<Triplet> decompositions) {
		for (int i = 0; i < vecDecompositions.size(); i++) {
			for (int j = 0; j < vecDecompositions.size(); j++) {

					int prefix = vecDecompositions[i].start;
					int wordOfPrefix = vecDecompositions[i].wordNumber;
					int lengthOfWord = vecDecompositions[i].length;

					int suffix = vecDecompositions[j].end;
					int wordOfSuffix = vecDecompositions[j].wordNumber;
					int lengthOfWord2 = vecDecompositions[j].length;

					int lengthOfSuffix1 = lengthOfWord2 - suffix;
					if (
						compare(
							prefix,
							wordOfPrefix,
							lengthOfWord,
							suffix,
							wordOfSuffix,
							lengthOfWord2,
							lengthOfSuffix1
						)
					) {
					if (prefix == 0) {
						char* partOfAlphabet = new char[1];
						partOfAlphabet[0] = '\0';
						bAlphabet.insert(string(partOfAlphabet));
						continue;
					}
					char* partOfAlphabet = new char[prefix + 1];
					for (int k = 0; k < prefix; k++) {
			       		partOfAlphabet[k] = words[wordOfPrefix][k];
					}
					partOfAlphabet[prefix] = '\0';
					bAlphabet.insert(string(partOfAlphabet));
			        }
		     }
	    }
     bAlphabet.insert("");
	 buildGraph();
	 doDfs();
}
	void buildGraph() {
		vecAlphabet.insert(vecAlphabet.end(), bAlphabet.begin(), bAlphabet.end());
		for (int i = 0; i < vecAlphabet.size(); i++) {
			unordered_set<string> destinations;
			graph.emplace(vecAlphabet[i], destinations);
		}
		for (int i = 0; i < vecDecompositions.size(); i++) {
			Triplet triplet = vecDecompositions[i];
			if (
				bAlphabet.find(triplet.prefix) != bAlphabet.end() &&
				bAlphabet.find(triplet.suffix) != bAlphabet.end()
				) {
				graph.at(triplet.prefix).insert(triplet.suffix);
			}
		}
	}
	void doDfs() {
		unordered_set<string> visited;
		string startVertex = "";
		dfs(visited, startVertex, graph, "");
	}

	void dfs(
		unordered_set<string>& visited,
		string curVertex,
		unordered_map<string, unordered_set<string>>& graph,
		string cur
	) {
		cout << "current vertex: " << endl;
		if (visited.find(curVertex) != visited.end()) {
			if (curVertex == "") {
				cout << "Not Ok" << endl;
			}
			return;
		}
		visited.emplace(curVertex);

			for (const auto& elem : graph.at(curVertex)) {
				dfs(visited, elem, graph, cur);
			}
	}
private:
	bool compare(
		int prefix,
		int wordOfPrefix,
		int lengthOfPrefixWord,
		int suffix,
		int wordOfSuffix,
		int lengthOfSuffixWord,
		int lengthOfTheSuffix
	) {
		char* prefixWord = words[wordOfPrefix];
		char* suffixWord = words[wordOfSuffix];

		if (prefix != lengthOfTheSuffix) {
			 return false;

		}
		char* tmpSuffix = new char[lengthOfTheSuffix];
		for (int i = suffix, j = 0; i < lengthOfSuffixWord; i++, j++) {
			tmpSuffix[j] = suffixWord[i];
		}

		for (int i = 0; i < prefix; i++) {

			if (prefixWord[i] != tmpSuffix[i]) {
				return false;
			}
		}
		return true;
	}
};

