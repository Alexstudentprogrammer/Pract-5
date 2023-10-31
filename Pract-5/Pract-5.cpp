#include <iostream>
#include "Solver.h"
int main()
{

    //read from input files
    int* horizontalSise = new int[5];
    horizontalSise[0] = 2;
    horizontalSise[1] = 3;
    horizontalSise[2] = 2;
    horizontalSise[3] = 4;
    horizontalSise[4] = 5;

    char** words = new char* [5];
    words[0] = new char[2];
    words[0][0] = 'a';
    words[0][1] = 'b';
    
    words[1] = new char[3];
    words[1][0] = 'a';
    words[1][1] = 'c';
    words[1][2] = 'b';

    words[2] = new char[2];
    words[2][0] = 'b';
    words[2][1] = 'c';
    
    words[3] = new char[4];
    words[3][0] = 'a';
    words[3][1] = 'b';
    words[3][2] = 'a';
    words[3][3] = 'c';
    
    words[4] = new char[5];
    words[4][0] = 'b';
    words[4][1] = 'a';
    words[4][2] = 'b';
    words[4][3] = 'b';
    words[4][4] = 'c';

    Solver s(words, 5, horizontalSise);
    s.solve();
}