#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <fstream>
using namespace std;

vector<int> createKMPtable(string pat, long long& countCmp) {
    vector<int> next(pat.size() + 1);
    int i = 0;
    int j = next[0] = -1;
    while (++countCmp && i < pat.size()) {
        while (++countCmp && j > -1 && (pat[i] != pat[j])) {
            j = next[j];
        }
        i++;
        j++;
        next[i] = j;
    }
    return next;
}
vector<int> knuth_morris_pratt(string pat, string src, long long& countCmp) {
    vector<int> ans;
    long long countCmpFirst = 0;
    vector<int> next = createKMPtable(pat, countCmp);
    int i = 0;  // index of src 
    int j = 0;  // index of pat
    while (++countCmp && i <= src.size() - pat.size()) {
        if (++countCmp && pat[j] == src[i + j]) {
            j++;
            if (++countCmp && j == pat.size()) {
                ans.push_back(i);
                if (countCmpFirst == 0)
                    countCmpFirst = countCmp;
                i += j - next[j];
                j = next[j];
            }
        }
        else {
            i += j - next[j];
            j = 0;
        }
    }
    if (ans.size() != 0)
        countCmp = countCmpFirst;
    return ans;
}