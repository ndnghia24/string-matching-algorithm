#pragma once
#include<vector>
#include<iostream>
using namespace std;

vector<int> rabin_karp(string pat, string txt, long long& cmp)
{
    vector<int> ans;
    int firstCmp = 0;
    int d = 256;
    int M = pat.size();
    int N = txt.size();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    for (i = 0; ++cmp && i < M - 1; i++)
    {
        h = (h * d) % INT_MAX;
    }
    for (i = 0; ++cmp && i < M; i++)
    {
        p = (d * p + pat[i]) % INT_MAX;
        t = (d * t + txt[i]) % INT_MAX;
    }
    for (i = 0; ++cmp && i <= N - M; i++) {
        if (++cmp && p == t)
        {
            for (j = 0; ++cmp && j < M; j++)
            {
                if (++cmp && txt[i + j] != pat[j])
                {
                    break;
                }
            }

            if (++cmp && j == M)
            {
                ans.push_back(i);
                if (firstCmp == 0)
                    firstCmp = cmp;
            }
        }
        if (++cmp && i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % INT_MAX;
            if (++cmp && t < 0)
            {
                t = (t + INT_MAX);
            }
        }
    }
    if (ans.size() != 0)
        cmp = firstCmp;
    return ans;
}