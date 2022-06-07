#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define yes cout << "YES\n";
#define no cout << "NO\n";
const int maxn = 1e9 + 7;
const double mod = 1e9 + 7;


void solution()
{
	int n, k;
	cin >> n >> k;
	vi dp(k + 1, 1e9);
	
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		if (num > k) continue;
		dp[num] = 1;
		for (int j = 2; j * num <= k; j++)
		{
			dp[j * num] = dp[(j - 1) * num] + 1;
		}
	}

	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j < i; j++)
		{
			dp[i] = min(dp[i], dp[i - j] + dp[j]);
		}
	}

	if (dp[k] == 1e9) cout << -1;
	else cout << dp[k];
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}