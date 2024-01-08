#include <iostream>
#include "Solver.h"
#include "Test.h"
#include "my_vector.h"
#include "HashTable.h"
#include "my_vector.h"
#include <list>
#include "Trie.h"

int main()
{
    // Graphx
    //Two way search comparison

    Test test;
   // test.run_test("Tests/stress_test_3.txt");
   // test.run_stress_test1(11, 44); // variate n - and analyze time and steps

    /*Trie trie;
    trie.add_word("111");
    trie.add_word("alex");
    trie.add_word("practicum");

    cout << trie.check_word("alex") << endl;
    cout << trie.check_word("111") << endl;
    cout << trie.check_word("practicum") << endl;
    cout << trie.check_word("some other word") << endl;*/

   while (true) {

       int option;
       cout << " 1 - Run correctness test" << endl;
       cout << " 2 - Run stress test with correct code words" << endl;
       cout << " 3 - Run stress test with incorrect code words" << endl;
       cout << " 4 - Run worse case stress test with incorrect code words" << endl;
       cin >> option;

       switch (option)
       {
       case 1: {
           test.run_test("Tests/test_file_1.txt");
           //test.run_test("Tests/test_file_2.txt");
           break;
       }
       case 2: {
           int word_len, number_of_words;
           cout << " Enter word length and number of words" << endl;
           cin >> word_len >> number_of_words;
           test.run_stress_test1(word_len, number_of_words);
           break;
       }
       case 3: {
           test.run_test("Tests/stress_test_2.txt");
           break;
        }

       case 4: {
           test.run_test("Tests/stress_test_3.txt");
           break;
       }

       default:
           cout << " Incorrect option" << endl;
           break;
       }

   }

    // test - 1
    // generate binary numbers of fixed size

    // test - 2
    // generate numbers with pattern
    // a1 = b1b2b3
    // a2 = b3b4b5
    // a4 = b1b2
    // a5 = b4b5
}