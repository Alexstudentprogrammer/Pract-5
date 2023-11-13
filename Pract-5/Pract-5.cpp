#include <iostream>
#include "Solver.h"
#include "Test.h"
#include "my_vector.h"
#include "HashTable.h"
int main()
{

    Test test;
    HashTable t;
    // test.run_test("Tests/test_file_4.txt");
    test.run_stress_test1(4); // variate n - and analyze time and steps
   
    // dependency of 2 parameters

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