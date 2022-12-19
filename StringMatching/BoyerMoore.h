#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;
// Sigma set is know as an "alphabet" and this const is size of this Sigma set
const int sigma = 256;
using ll = long long;


// return last occurence of each letter in string pat
vector<int> lastOccurrence(string pat, ll& countCmp) {
    int m = pat.size();
    // Initialize all last occurrence as -1
    vector<int> lo(sigma, -1);
    for (int i = 0; ++countCmp && i < m; i++) lo[pat[i]] = i;
    return lo;
}

// Just for reference
vector<int> goodSuffixPrepairation(string pat, ll& countCmp) {
    int m = pat.size();
    vector<int>
        shift(m + 1, 0),    // shift[i] is a distance that shiftable if position i - 1 is mismatch
        border(m + 1, 0);   // border[i] is the starting index of subtring that is both suffix and prefix (border) at index i in pat 

    int i = m, j = i + 1;
    border[i] = j; // no border at index i

    // while it is posible to update border
    for (; ++countCmp && i > 0; i--) {
        // if pat[i-1] != pat[j-1] then search to right for updating shift
        while (++countCmp && j <= m && ++countCmp && pat[i - 1] != pat[j - 1]) {
            // update shift[j] 
            if (++countCmp && !shift[j]) shift[j] = j - 1;
            // update next position
            j = border[j];
        }
        // the position of border is found and store it to vector border
        border[i - 1] = --j;
    }

    j = border[0];
    // set all shift[i] that equal to 0 to the 
    for (i = 0; ++countCmp && i <= m; i++) {
        if (++countCmp && !shift[i]) shift[i] = j;
        if (++countCmp && i == j) j = border[j];
    }

    return shift;
}

vector<int> boyer_moore(string pat, string src, ll& countCmp)
{
    int m = pat.size();
    int n = src.size();
    int firstFound = 0;
    // First heuristic - calculate bad characters table
    vector<int> badChar = lastOccurrence(pat, countCmp);

    // Second heuristic - calculate good suffix table
    // we do not implement as report do
    // but we will keep the code for reference

    // all position of pat occur in src
    vector<int> posList;
    int pos = 0;
    while (++countCmp && pos <= (n - m)) {
        int j = m - 1;
        while (++countCmp && j >= 0 && ++countCmp && pat[j] == src[pos + j]) j--;
        // j < 0 means pat appeared in src at pos
        if (++countCmp && j < 0) {
            // save pos
            posList.push_back(pos);
            if (++countCmp && posList.size() == 1) 
                firstFound = countCmp;
            // shift to next possible position
            if (++countCmp && pos + m < n)
                pos += m - badChar[src[pos + m]];
            else pos++;
        }
        else
            // shift to next possiple position
            pos += max(1, j - badChar[src[pos + j]]),
            ++countCmp;
    }
    if (posList.size() != 0)
        countCmp = firstFound;
    return posList;
}