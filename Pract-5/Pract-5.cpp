#include <iostream>
#include "Solver.h"
#include "Test.h"
#include "my_vector.h"
#include "HashTable.h"
#include "my_vector.h"
#include <list>
int main()
{

    Test test; 
    test.run_test("Tests/stress_test_2.txt");
   /* HashTable<Triplet, int, Triplet::HashFunction> alphabet;
    Triplet t;
    alphabet.put(t, 0);*/
    
   // dependency of 2 parameters
   // test.run_test("Tests/stress_test.txt");
   // test.run_stress_test1(8); // variate n - and analyze time and steps

    /*
    test1 - 2^9 words of length 9
    60 seconds (debug mode)
    operations approximation: (2^9)^2 = 216 144
                               9^4 = 6561
                               Total, aprox. 1.72 * 10^(9)
    */

    // test - 1
    // generate binary numbers of fixed size

    // test - 2
    // generate numbers with pattern
    // a1 = b1b2b3
    // a2 = b3b4b5
    // a4 = b1b2
    // a5 = b4b5
}