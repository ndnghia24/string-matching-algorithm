#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;

// function lib
#include "BruteForce.h"
#include "RabinKarp.h"
#include "KmpSearching.h"
#include "BoyerMoore.h"
#include "TwoWayMatching.h"

void toFile(string filename, vector<int> startID, int n) {
    ofstream fout(filename);
    for (int i = 0; i < startID.size(); i++)
        fout << startID[i] << " " << startID[i] + n - 1 << endl;
    fout.close();
}

int main(int argc, char* argv[]) {

    vector<string> argvVector;
    cout << ">> ";
    for (int i = 0; i < argc; i++) {
        argvVector.push_back(argv[i]);
        cout << argvVector[i] << " ";
    }
    cout << "\n\n";

    if (argc != 5) {
        cout << "Invalid arrguments!" << endl;
        system("pause");
        return -1;
    }

    map<string, int> ID_algo = {
        {"-bf",1},
        {"-rk",2},
        {"-kmp",3},
        {"-bm",4},
        {"-tw",5},
    };

    map<string, int> ID_info = {
        {"-t",1},
        {"-n",2},
        {"-ind",3},
    };
  
    map<int, pair<vector<int>(*) (string, string, long long&), string>> algo = {
        {1,{brute_force, "Brute-force"}},
        {2,{rabin_karp, "Rabin-Karp"}},
        {3,{knuth_morris_pratt,"Knuth-Morris-Pratt"}},
        {4,{boyer_moore, "Boyer–Moore"}},
        {5,{two_way_matching, "Two-way algorithm"}},
    };
    // check input
    if (ID_algo[argvVector[1]] > 5 || ID_algo[argvVector[1]] < 1) {
        cout << "Wrong algorithms!";
        system("pause");
        return -1;
    }
    if (ID_info[argvVector[4]] > 3 || ID_info[argvVector[4]] < 1) {
        cout << "Wrong output status!";
        system("pause");
        return -1;
    }

    // read 2 string from input file
    ifstream fin(argvVector[2]);
    if (fin.fail()) {
        cout << "File doesn't exist\n";
        system("pause");
        return -1;
    }
    string src, pat;
    /*
    getline(fin, src);
    getline(fin, pat);
    */
    getline(fin, pat);
    getline(fin, src);
    fin.close();

    // init variable
    int i;

    // print information
    i = ID_algo[argvVector[1]];
    cout << "Algorithm : " << algo[i].second << endl << endl;
    cout << "Source  (" << src.size() << " characters): " << src.substr(0, 30) + " _"[src.size() > 30] << endl;
    cout << "Pattern (" << pat.size() << " characters): " << pat.substr(0, 30) + " _"[pat.size() > 30] << endl;
    if (pat.size() > src.size()) {
        cout << "Source string must longer than pattern string!\n";
        system("pause");
        return -1;
    }

    // string matching
    long long countCmpFirst = 0;
    i = ID_algo[argvVector[1]];
    auto startTime = chrono::steady_clock::now();
    vector<int> startID = algo[i].first(pat, src, countCmpFirst);
    auto endTime = chrono::steady_clock::now();
    double runTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() / 1000000.0;

    // output pattern's location in source string to file
    toFile(argvVector[3], startID, pat.size());

    // print runtime & number of comparisons
    cout << "_________________________\n\n";
    i = ID_info[argvVector[4]];
    if (i == 1 || i == 3)
        cout << "Running time : " << runTime  << " (ms) " << endl;
    if (i == 2 || i == 3)
        cout << "Number of comparisons of the first successful searching : " << countCmpFirst << endl << endl;

    return 0;
}