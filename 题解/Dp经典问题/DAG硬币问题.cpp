# 求最少硬币数目

#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int maxn = 4e4;
ll dp[maxn];
int n,a[maxn];
int main() {
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	int v;
	while (~scanf("%d", &v) && v) {
		memset(dp, INF, sizeof(dp));
		dp[0] = 0;
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= v;j++)
				if (j >= a[i]) dp[j] = min(dp[j], dp[j - a[i]] + 1);
		printf("%lld\n", dp[v]);
	}
	return 0;
}
