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
        while (++countCmp && j > -1 && pat[i] != pat[j]) {
            j = next[j];
        }
        i++;
        j++;
        if (++countCmp && pat[i] == pat[j]) {
            next[i] = next[j];
        }
        else {
            next[i] = j;
        }
    }
    return next;
}
vector<int> knuth_morris_pratt(string pat, string src, long long& countCmp) {
    vector<int> ans;
    long long countCmpFirst = 0;
    vector<int> next = createKMPtable(pat, countCmp);
    int start = 0;  // index of src 
    int i = 0;      // index of pat
    while (++countCmp && start <= src.size() - pat.size()) {
        if (++countCmp && pat[i] == src[start + i]) {
            i++;
            if (++countCmp && i == pat.size()) {
                ans.push_back(start);
                if (countCmpFirst == 0)
                    countCmpFirst = countCmp;
                start += i - next[i];
                i = next[i];
            }
        }
        else {
            start += i - next[i];
            i = 0;
        }
    }
    countCmp = countCmpFirst;
    return ans;
}