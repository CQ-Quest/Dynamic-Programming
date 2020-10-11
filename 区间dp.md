# 区间dp
      Key code:
      
          for(int len=1;len<=m;len++){
          for(int i=1;i+len-1<=m;i++){
              int j=i+len-1;
              for(int k=i;k<=j;k++){
                  f[i][j] = min(f[i][j],f[i][k-1]+f[k+1][j]+something);
              }
          }
      }
      
      
 Code:
 
          #include <bits/stdc++.h>
          using namespace std;
          typedef long long ll;

          int n,m;
          int a[1001];
          int f[1001][1001]; 

          int main(){
              scanf("%d %d",&n,&m);
              for(int i=1;i<=m;i++){
                  scanf("%d",&a[i]);
              }
              sort(a+1,a+m+1);
              a[0] = 0;
              a[m+1] = n+1;
              for(int len=1;len<=m;len++){
                  for(int i=1;i+len-1<=m;i++){
                      int j=i+len-1;
                      f[i][j] = 1000000000;
                      for(int k=i;k<=j;k++){
                          f[i][j] = min(f[i][j],f[i][k-1]+f[k+1][j]+a[j+1]-a[i-1]-1-1);
                      }
                  }
              }
              printf("%d\n",f[1][m]);
              return 0;
          }
