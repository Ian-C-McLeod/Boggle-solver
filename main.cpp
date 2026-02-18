#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <deque>
#include "wordfinder.hpp"
#include "trie.hpp"
#include "Matrix.hpp"// from uni
using namespace std;

void fill_Dictionary(string file_name, PrefixDictionary& dicts);
void fillcin(Matrix<char>& grid);
int main(int argc,char *argv[]){
    if (argc==1){
        cout<< "not enough inline arguement(dict)";
    }
    PrefixDictionary dict;
    cout<<argv[1];
    fill_Dictionary(argv[1],dict);
    for(int i= 65;i<90;i++){
        char ch=(char)i;
        string temp;temp+=ch;
        cout<<ch<<" : "<<dict.searchPrefix(temp).size()<<endl;
    }
    int l, w;
    cin >> l;cin >> w;
    Matrix<char> board(l, w);fillcin(board);
    Matrixsolver game(board,dict);
    cout<<game.grid;
    game.squaredlesolve();
    int count=1;
            for (const auto& str : game.found) {
            cout<< count << " " << str << "\n";
            count++;
        }
}

void fillcin(Matrix<char>& grid){
    string line;
    for(int i=0;i<grid.height();i++){
        cin >>line;
        for(int j=0;j<grid.width();j++){
        grid.at(i, j) = line[j];
        //cout<<i<<","<<j<<" "<<grid.at(i, j) <<" ";
        }
    }
}

void fill_Dictionary(string file_name, PrefixDictionary& dicts){
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Could not open file:"<<file_name<<"\n";
        exit(1);
    }
    cout<<"file cleared"<<endl;
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            dicts.insert(word);
        }
    }
    cout<<"file done"<<endl;
    file.close();
}

