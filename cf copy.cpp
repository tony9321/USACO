#include <bits/stdc++.h> // see /general/running-code-locally
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") {
	cin.tie(0)->sync_with_stdio(0); // see /general/fast-io
	if (sz(name)) {
		freopen((name + ".in").c_str(), "r", stdin); // see /general/input-output
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

/*Solution

The main observation for this problem is that we only need to keep track of the
number of games played i, the number of times switched so far j, and the
current gesture k in order to determine the largest number of previous games
won for any game i.

For every move, either Bessie can either switch or stay on her current gesture.
If she changes her gesture, then the next game i+1 will have used j+1
gestures, which corresponds to the dp state
dp[i+1][j+1][k]. We can simulate this for all 3 gestures. Then, we
just increment dp[i][j][k] if Bessie wins at game i with gesture
k.

Note that you can just compare the current gesture to H, P, S because there is
always exactly one way to win.

Time Complexity: O(NK)*/

const int mx=1e5+5; // +5 prevent overflow 
int dp[mx][22][3];	// dp[i][j][k] is the largest number of games she wins at
                    // games i with switches j with current item k
	                // 0 == H 1 == P 2 == S
int c[mx];          // storing the record of the farmer's combination

int main() 
{
	setIO("hps");  // reading IO 
    int n, K;  cin >> n >> K;

    // storing farmer's record
    for(int i=0;i<n;i++)
    {
		char tmp; cin >> tmp;
		if(tmp=='H') c[i]=0;
		else if(tmp=='P') c[i]=1;
		else c[i]=2;
    } 

    // either swith or stay
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=K;j++)
		{
			for(int k=0;k<3;k++)
			{
				if(k==c[i]) dp[i][j][k]++;
				dp[i+1][j+1][0]=max(dp[i+1][j+1][0],dp[i][j][k]); // switch to next item
				dp[i+1][j+1][1]=max(dp[i+1][j+1][1],dp[i][j][k]); // switch to next item
				dp[i+1][j+1][2]=max(dp[i+1][j+1][2],dp[i][j][k]); // switch to next item
				dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]); //stay at k(current)
			}
		}
	}
	int ans=0;
	for(int i=0;i<3;i++) {ans=max(ans, dp[n-1][K][i]);}	cout << ans << '\n';
}
