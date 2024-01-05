// http://www.usaco.org/index.php?page=viewproblem2&cpid=574
// https://usaco.guide/gold/knapsack?lang=cpp
// 11/14/23
// Yun Tung Chen
// dp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

//const ll l=5e6+6;

bool dp[2][5000001];
int main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);
	int t=0, a=0, b=0;
	cin >> t >> a >> b;
	dp[0][0]=1;
	// we maintain two arrays, the first one[0][5e6+5] if when we haven't drunk water yet
	//we use this array to build[1][5e6+6] the array after we drink the water 
	for(int i=0;i<t+1;i++)
	{
		if(i-a>=0) dp[0][i]|=dp[0][i-a];
		if(i-b>=0) dp[0][i]|=dp[0][i-b];
		dp[1][i/2]=dp[0][i];
	}
	for(int i=0;i<t+1;i++)
	{
		if(i-a>=0) dp[1][i]|=dp[1][i-a];
		if(i-b>=0) dp[1][i]|=dp[1][i-b];
	}
	// then from the rear of the dp[1][] array, we try to find the biggest index that is 
	 //true as the highest possible fullness we can obtain
	for(int i=t;i>=0;i--)
	{
		if(dp[1][i])
		{
			cout << i << '\n';
			break;
		}
	}
}
