 # 二维费用背包
     顾名思义，即背包中的每种物品有两种费用。   
    设f[i][v][u]表示前i件物品付出两种代价分别为v和u时可获得的最大价值，那么我们很容易给出状态转移方程，
    加一维状态即可,实际二维费用背包是前几种背包的综合体现。f[i][v][u]=max{f[i-1][v][u],f[i-1][v-a[i]][u-b[i]]+w[i]}

    在这里，如果每种物品只可以取一次采用类似于01背包滚动数组的循环方式，即逆序循环
    如果每种物品可以取无数次采用完全背包滚动数组的循环方式，顺序循环
    如果有多重背包的方式进行二进制优化，拆分物品
