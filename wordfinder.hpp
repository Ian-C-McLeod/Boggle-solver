#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include "trie.hpp"
#include "Matrix.hpp"
using namespace std;


class Matrixsolver {
 public:
 Matrixsolver(Matrix<char> Grid, PrefixDictionary& Dict);
 void wordsearchsolve();
 void squaredlesolve();
 void changegrid(Matrix<char> Grid);
 Matrix<char> grid;
 set<string> found;
 private:
 PrefixDictionary dict;

};





