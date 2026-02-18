#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <utility>
#include <deque>
#include <set>
#include "Matrix.hpp"
#include "wordfinder.hpp"
using namespace std;

pair<int, int> operator+(const pair<int, int>& a, const pair<int, int>& b) {
    return {a.first + b.first, a.second + b.second};
}

struct path_state{
    Matrix<bool> vtable;
    string proto;
    pair<int, int> last;
    path_state(Matrix<bool> vt,string prot, pair<int, int> lst){
        vtable= vt;
        proto=prot;
        last=lst;
    }

};

void Matrixsolver::changegrid(Matrix<char> Grid){
    grid=Grid;
    set<string> the;
    found= the;
}

Matrixsolver::Matrixsolver(Matrix<char> Grid, PrefixDictionary& Dict){
    grid=Grid;
    dict=move(Dict);
}

void Matrixsolver::wordsearchsolve(){
    for(size_t i=0; i<grid.height()-1;i++){
        for(size_t j=0; j<grid.width()-1;j++){
        vector<pair<int, int>> directions = {
        {0, 1},{1, 0},{0, -1},{-1, 0}, //cardinal
        {-1,-1},{-1,1},{1,-1},{1,1}// diagonal
        };
        for(auto direction :directions){
            string proto_word = "";
            proto_word += grid.at(i,j);
            pair<int , int> start={i,j}; 
            while(dict.isprefix(proto_word)){
                if(dict.isword(proto_word)){
                    cout<<proto_word<<endl;
                    //record
                }
                start=start+direction;
                if((start.first<0 || start.first > grid.height()-1) || (start.second< 0 || start.second > grid.width()-1)){
                    break;
                }
                proto_word+=grid.at(start.first,start.second);
            }


        }
    }


}
}

void join_all(std::vector<thread>& threads) {
    for (auto& t : threads) {
        if (t.joinable()) {  
            t.join(); 
        }
    }
}



void Matrixsolver::squaredlesolve(){
    int test=0;
    mutex found_mutex;
    auto frompoint = [&](pair<int, int> start) {
        vector<pair<int, int>> directions = {
            {0, 1},{1, 0},{0, -1},{-1, 0}, //cardinal
            {-1,-1},{-1,1},{1, -1},{1, 1}// diagonal
        };
            string proto_word = "";
            proto_word += grid.at(start.first,start.second);
        Matrix<bool> visittable(grid.height(),grid.width());
        for(int i=0;i<visittable.height();i++){
            for(int j=0;j<visittable.width();j++){
            visittable.at(i,j) = true;
            }
        }
        set<string> temp;
        visittable.at(start.first,start.second)=false;
        path_state state(visittable,proto_word,start);
        queue<path_state> backtracking;
        if(dict.isprefix(proto_word))
            backtracking.push(state);
        while(!backtracking.empty()){
            //cout<<test<<endl;
            for (auto direction : directions){
                test++;
                path_state poss_st = backtracking.front();
                poss_st.last=poss_st.last+direction;
                if((poss_st.last.first<0 || poss_st.last.first > grid.height()-1) || (poss_st.last.second< 0 || poss_st.last.second > grid.width()-1)){
                    continue;
                }
                poss_st.proto +=grid.at(poss_st.last.first,poss_st.last.second);
                if(!poss_st.vtable.at(poss_st.last.first,poss_st.last.second)){
                    continue;
                }
                else{
                    poss_st.vtable.at(poss_st.last.first,poss_st.last.second)=false;
                }
                
                if(dict.isword(poss_st.proto)&&poss_st.proto.length()>=4){
                    temp.insert(poss_st.proto);
                }
                if(!dict.isprefix(poss_st.proto)){
                    continue;
                }
                backtracking.push(poss_st);

            }
            backtracking.pop();
        }
        lock_guard<mutex> lock(found_mutex);
        found.insert(temp.begin(),temp.end());


    };
    vector<thread> threads;
    for(size_t i=0; i<grid.height();i++){
        for(size_t j=0; j<grid.width();j++){
            pair<int, int> start = {i,j};
            thread Thread(frompoint,start);
            threads.push_back(move(Thread));

        }
    }
    join_all(threads);
}


