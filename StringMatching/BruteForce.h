#pragma once
#include<vector>
#include<iostream>
using namespace std;

//pat = child ; txt = source

vector<int> brute_force(string pat, string txt, long long& cmp)
{
    vector<int> ans;
    int firstCmp = 0;
    for (int i = 0; ++cmp && i < txt.size() - pat.size() + 1; i++)
    {
        int j;
        for (j = 0; ++cmp && j < pat.size(); j++)
        {
            if (++cmp && txt[i + j] != pat[j])
                break;
        }
        if (++cmp && j == pat.size()) {
            ans.push_back(i);
            if (firstCmp == 0)
                firstCmp = cmp;
        }
    }
    if (ans.size() != 0)
        cmp = firstCmp;
    return ans;
}