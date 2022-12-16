#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <fstream>
using namespace std;

int cmp(char a, char b, long long& countCmp)
{
	if (++countCmp && a > b)
		return 1;
	if (++countCmp && a == b)
		return 0;
	return -1;
}
// order: 1 is <=, -1 is >=
pair<int, int> maxsuf(string x, int order, long long& countCmp)
{
	int l = x.size(), p = 1, k = 1, j = 0, i = -1;
	while (++countCmp && j + k < l)
	{
		int cmpv = order * cmp(x[j + k], x[i + k], countCmp);
		if (++countCmp && cmpv < 0)
		{
			j = j + k;
			k = 1;
			p = j - i;
		}
		else if (++countCmp && cmpv == 0)
		{
			if (++countCmp && k == p)
			{
				j = j + p;
				k = 1;
			}
			else
				k++;
		}
		else
		{
			i = j;
			j++;
			p = 1;
			k = 1;
		}
	}
	return { i, p };
}

pair<int, int> crit_fact(string x, long long& countCmp)
{
	pair<int, int> maxSuf1 = maxsuf(x, 1, countCmp);
	pair<int, int> maxSuf2 = maxsuf(x, -1, countCmp);
	if (++countCmp && maxSuf1.first > maxSuf2.first)
		return maxSuf1;
	return maxSuf2;
}

vector<int> two_way_matching(string x, string t, long long& countCmp)
{
	int i, j, ell, per, memory;
	long long countCmpFirst;
	int n = t.size(), m = x.size();
	pair<int, int> maxSuf = crit_fact(x, countCmp);
	vector<int> ans;
	ell = maxSuf.first;
	per = maxSuf.second;
	if (++countCmp && x.substr(0, ell + 1) == x.substr(per, ell + 1))
	{
		j = 0;
		memory = -1;
		while (++countCmp && j <= n - m)
		{
			i = max(ell, memory) + 1;
			++countCmp;
			while (++countCmp && i < m && ++countCmp && x[i] == t[i + j])
				++i;
			if (++countCmp && i >= m)
			{
				i = ell;
				while (++countCmp && i > memory && ++countCmp && x[i] == t[i + j])
					--i;
				if (++countCmp && i <= memory)
				{
					ans.push_back(j);
					if (ans.size() == 1)
						countCmpFirst = countCmp;
				}
				j += per;
				memory = m - per - 1;
			}
			else
			{
				j += (i - ell);
				memory = -1;
			}
		}
	}
	else
	{
		per = max(ell + 1, m - ell - 1) + 1;
		++countCmp;
		j = 0;
		while (++countCmp && j <= n - m)
		{
			i = ell + 1;
			while (++countCmp && i < m && ++countCmp && x[i] == t[i + j])
				++i;
			if (++countCmp && i >= m)
			{
				i = ell;
				while (++countCmp && i >= 0 && ++countCmp && x[i] == t[i + j])
					--i;
				if (++countCmp && i < 0)
				{
					ans.push_back(j);
					if (ans.size() == 1)
						countCmpFirst = countCmp;
				}
				j += per;
			}
			else
				j += (i - ell);
		}
	}
	countCmp = countCmpFirst;
	return ans;
}