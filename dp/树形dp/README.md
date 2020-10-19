        #include <bits/stdc++.h>
        using namespace std;
        typedef long long ll;

        const int maxn = 6005;
        int h[maxn];
        int v[maxn];
        vector<int> son[maxn];
        int f[maxn][2];    //f[x][0]代表以x为根的子树，x不参加的最大权值；f[x][1]代表以x为根的子树，x参加的最大权值

        void dp(int x){
            f[x][0] = 0;
            f[x][1] = h[x];
            for(int i=0;i<son[x].size();i++){
                int y = son[x][i];
                dp(y);
                f[x][0] += max(f[y][0],f[y][1]);
                f[x][1] += f[y][0];
            }
        }

        int main(){
            int n;
            scanf("%d",&n);
            //输入每个点的权值
            for(int i=1;i<=n;i++){
                scanf("%d",&h[i]);
            }
            //建树，在这里y是x的父亲
            for(int i=1;i<=n-1;i++){
                int x,y;
                scanf("%d %d",&x,&y);
                son[y].push_back(x);
                //v[i]记录i是否为根节点
                v[x] = 1;
            }
            //找出根节点
            int root;
            for(int i=1;i<=n;i++){
                if(v[i]==0){
                    root = i;
                    break;
                }
            }
            dp(root);
            printf("%d\n",max(f[root][0],f[root][1]));
            return 0;
        }
        
    //金明的预算方案
        #include<bits/stdc++.h>
        using namespace std;
        const int maxn =4e4+10;
        const int N =70;
        vector<int>g[maxn];
        struct node{
                int cost;
                int val;
        }s[N];
        int dp[N][maxn];

        void dfs(int rt,int m){
                if(m==0){
                        return;
                }
                for(int i=0;i<g[rt].size();i++){
                        int u=g[rt][i];
                        for(int j=0;j<=m;j++){
                                dp[u][j]=dp[rt][j];
                        }
                        dfs(u,m-s[rt].cost);
                        for(int j=m;j>=s[u].cost;j--){
                                dp[rt][j]=max(dp[rt][j],dp[u][j-s[u].cost]+s[u].cost*s[u].val);
                        }
                }
        }
        int main(){
                int m,n;
                while(scanf("%d%d",&m,&n)!=EOF){
                        for(int i=0;i<=n;i++){
                                g[i].clear();
                        }
                        int r,c,x;
                        for(int i=1;i<=n;i++){
                                scanf("%d%d%d",&s[i].cost,&s[i].val,&x);
                                g[x].push_back(i);
                        }
                        memset(dp,0,sizeof(dp));
                        dfs(0,m);
                        printf("%d\n",dp[0][m]);
                }
                return 0;
        }
