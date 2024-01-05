//https://cses.fi/problemset/task/1638
//https://usaco.guide/gold/paths-grids?lang=cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll dp[1003][1003];
bool s[1003][1003];
int main() 
{
	int n; cin >> n;
	//int dp[n+1][n+1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			char tmp;
			cin >> tmp;
			if(tmp=='.') 
			{
				s[i][j]=1;
				//dp[i][j]=1;
			}
			else 
			{
				s[i][j]=0;
				//dp[i][j]=0;
			}
		}
	}
	dp[0][0]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]==0) dp[i][j]=0;
			else
			{
				if(i>0)
				{
					dp[i][j]+=dp[i-1][j];
				}
				if(j>0)
				{
					dp[i][j]+=dp[i][j-1];
				}
				dp[i][j]%=1000000007;
			}
			
		}
	}
	cout << dp[n-1][n-1] << '\n';
}