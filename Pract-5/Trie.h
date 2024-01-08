#pragma once
#include <string>

using namespace std;

typedef struct LetterNode LetterNode;
struct LetterNode {
	LetterNode **childs;
	bool is_word_end;
};

class Trie {
	LetterNode* root;
	
public:
	Trie() {
		root = new LetterNode;
		root->childs = new LetterNode*[256];
		for (int i = 0; i < 256; i++) {
			root->childs[i] = NULL;
		}
	}

	void add_word(std::string word) {
		LetterNode* tmp = root;

		for (int i = 0; i < word.size(); i++) {
			char current_char = word.at(i);
			if (tmp->childs[current_char - '0'] != NULL) {
				tmp = tmp->childs[current_char - '0'];
			}
			else {
				tmp->childs[current_char - '0'] = new LetterNode;
				tmp->childs[current_char - '0']->childs = new LetterNode * [256];

				for (int j = 0; j < 256; j++) {
					tmp->childs[current_char - '0']->childs[j] = NULL;
				}
				tmp = tmp->childs[current_char - '0'];
			}
		}
		tmp->is_word_end = true;
	}
	// Paying constant for asyptotic
	bool check_word(string word, long double &steps) {
		LetterNode* tmp = root;

		for (int i = 0; i < word.size(); i++) {
			steps++;
			int current_char = word.at(i);// fix types confusion
			if (tmp->childs[current_char - 'A'] != NULL) {// add assertion or validation
				tmp = tmp->childs[current_char - 'A'];
			}
			else {
				return false;
			}
		}
		if (tmp != NULL && tmp->is_word_end) {
			return true;
		}
		return false;
	}
};
