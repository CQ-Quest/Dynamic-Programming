# 背包问题
# 01背包：拿与不拿问题  
题目    

有N件物品和一个容量为V的背包。第i件物品的费用是w[i]，价值是v[i],   
求将哪些物品装入背包可使价值总和最大。

 基本思路    
 
 打表


	        重量		价值		   dp					    容量					
              wi	         ci  	       <0	1	2	3	4	5	6	7	8	9	10>
     i=0	  0		  0	       <0	0	0	0	0	0	0	0	0	0	0>
      1	  2		  1		   <0 	0	1	1	1	1	1	1	1	1	1>
      2	  3		  3		   <0 	0	1	3	3	4	4	4	4	4	4>
      3	  4		  5		   <0 	0	1	3	5	5	6	8	8	9	9>
      4	  7	          9	      <0	0	1	3	5	5	6	9	9	10      12> 
      
      
      dp[i][j]表示商品价值，i为物品数，j表示容量，dp[2][u]~dp[n][u];  
      
        当j<w[i],不足以放下，不拿   dp[i][j]=dp[i-1][j];
          j>=w[i]时：(1)不拿： 上一物品价值 dp[i-1][j]
                     (2)拿：dp[i-1][j-w[i]]+c[i];      (dp[1][0]+3 , 0+3)=>max(dp[i-1][j],dp[i-1][j-w[i]]+c[i]);
                     
            ***判定：  
            if(j<w[i])  dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+c[i]);
            
 反无效原则：当前状态只与上一个有关
  
     一维,空间复杂度O(n)
     for(j=m;j>=1;j--)   //从后往前推
     if(j>=w[i])  dp[j]=max(dp[j],dp[j-w[i]]+c[i]);     
     
	   Code:  
		const int maxn=4000;
		int dp[maxn][maxn];
		int w[maxn],c[maxn];
		int main() {
			int N,V;
		    cin>>N>>V;
		    for(int i=1;i<=N;i++){
			cin>>w[i]>>c[i];
		    }
		    for(int i = 1;i<=N;i++)
				for(int j = 0;j<=V;j++){ 
					if(j>=w[i]){
				dp[i][j] = max(dp[i-1][j],dp[i-1][j-w[i]]+c[i]);
			    }
					else
						dp[i][j] = dp[i-1][j];
			} 
		    cout<<dp[N][V]<<endl;
		    return 0;
		}
		
         一维优化：
	const int maxn=3000;
	int dp[maxn],w[maxn],c[200];
	int main(){
		int N,V;
		cin>>N>>V;
		for(int i=1;i<=N;i++)
		cin>>w[i]>>c[i];
		for(int i=1;i<=N;i++)
		for(int j=V;j>=w[i];j--)  //滚动数组
		dp[j]=max(dp[j],dp[j-w[i]]+c[i]);
		cout<<dp[N]<<endl;
		return 0; 
	}
        
                     
# 完全背包  
    一个背包载重量M,从n种物品中选取若干件（同一物品可多次选取，即数量无限），使其重量和小于等于M  =>  最大价值  
    
               上限             下限
     朴素        0  1  2  3  ...  n     for(int j=w[i];j<=m;j++)    //记w[i]为重量
     完全         直到装满，当前背包容量j/w[i]
     
        01背包写法     
                    for(int i=1;i<=n;i++)
                      for(int j=m;j>=1;j--)  //反向
                      for(int k=0;k<=j/w[i];k++)
                      dp[j]=max(dp[j],dp[j-k*w[i]+k*c[i]);
                      
                      
           优化**  dp[i][j]=max(dp[i-1][j],dp[i][j-w[i]]+c[i])
                     一维 dp[j]=max(dp[j],dp[j-w[i]]+c[i]);
		     
        // dp[i][j]表示只看前i个物品，总体积是j的情况下，总价值最大是多少
		  Code:
		#include <iostream>
		#include <algorithm>
		using namespace std;

		const int N = 1010;
		int v[N], w[N], dp[N];

		int main() {
		    int n, m;
		    cin >> n >> m;
		    for (int i = 1; i <= n; i++) 
		     cin >> w[i] >> v[i];

		    for (int i = 1; i <= n; i++) {
			for (int j = v[i]; j <= m; j++) {    // 正序
			    f[j] = max(dp[j], dp[j - w[i]] + v[i]);
			    // 朴素：dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i]] + v[i]) 
			    // dp[i][j - w[i]] + v[i] = max(x, x, x, ...)
			}
		    }

		    cout << dp[m] << endl;
		}

                     
 # 多重背包    
	有N种物品和一个容量是V的背包。
	第i种物品最多有s件，每件体积是V,价值是Wi。
	求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。输出最大价值。

	输入格式
	第一行两个整数，N，V,用空格隔开，分别表示物品种数和背包容积。
	接下来有N行，每行三个整数v;, wi;Sj,用空格隔开，分别表示第i种物品的体积、价值和数量。

	输出格式
	输出一个整数，表示最大价值。

	  Code: 
		#include <iostream>
		#include <algorithm>
		using namespace std;

		const int N = 110;
		int v[N], w[N], s[N];
		int f[N][N];

		int main() {
		    int n, m;
		    cin >> n >> m;

	    for (int i = 1; i <= n; i++) {
		cin >> v[i] >> w[i] >> s[i]; 
	    }

	    // 三重循环
	    for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
		    for (int k = 0; k <= s[i] && k * v[i] <= j; k++) {
			f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
		    }
		}
	    }

	    cout << f[n][m] << endl;

	    return 0;
	}
	
    多重背包二进制思想优化：
	#include <iostream>
	#include <algorithm>
	using namespace std;

	const int N = 25000;
	int v[N], w[N],f[N];

	int main() {
	    int n, m;
	    cin >> n >> m;

	    // 核心是划分s[i],然后对所有划分出来的数用01背包思想
	    // 20: 1 2 4 8  5
	    int cnt = 0;
	    for (int i = 1; i <= n; i ++) {
		int a, b, s;
		cin >> a >> b >> s;

		int k = 1;
		while(k <= s) {
		    cnt ++;
		    v[cnt] = a * k;
		    w[cnt] = b * k;
		    s -= k;
		    k *= 2;
		}
		if (s > 0) {
		    cnt ++;
		    v[cnt] = a * s;
		    w[cnt] = b * s;
		}
	    }
	    n = cnt;

	    // 01背包模板
	    for (int i = 1; i <= n; i ++) {
		for (int j = m; j >= v[i]; j --) {
		    f[j] = max(f[j], f[j - v[i]] + w[i]);
		}
	    }

	    cout << f[m] << endl;

	    return 0;
	}
	
# 混合三种背包问题
# 二维费用背包
# 分组背包问题
	题目
	有N件物品，告诉你这N件物品的重量以及价值，将这些物品划分为K组，每组中的物品互相冲突，
	最多选一件，求解将哪些物品装入背包可使这些物品的费用综合不超过背包的容量，且价值总和最大。
	
	输入格式
	第一行有两个整数N，V,用空格隔开，分别表示物品组数和背包容量。接下来有N组数据:
	每组数据第一行有一个整数n，表示第1个物品组的物品数量;
	每组数据接下来有n行，每行有两个整数wi, vi,用空格隔开，分别表示第1个物品组的第j个物品的体积和价值;

	输出格式
	输出一个整数，表示最大价值。

	Code:
	#include <iostream>
	#include <algorithm>
	using namespace std;

	const int N = 110;
	int v[N][N], w[N][N];
	int f[N];
	int s[N];
	int n, m;

	int main() {
	    cin >> n >>m ;
	    for (int i = 1; i <= n; i++) {
		cin >> s[i];
		for (int j = 1; j <= s[i]; j++) {
		    cin >> w[i][j] >> v[i][j];
		}
	    }
    
    // 01背包+每组选一种
    /* 
       j逆序是因为      f[j] = max(f[j], f[j - w[i][k]] + v[i][k])
       等价变形是    f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i][k]] + v[i][k])
    */
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= s[i]; k++) {
                if (j >= w[i][k])
                    f[j] = max(f[j], f[j - w[i][k]] + v[i][k]);
            }
        }
    }
    cout << f[m] << endl;
    return 0;
    }

# 有依赖的背包问题
# 泛化物品
# 背包问题问法的变化
