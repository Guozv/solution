# CF1515E

发现最后一定是手动点亮一些连续段，中间隔一个被动亮的

直接 dp[i][j] 表示前i 个灯有 j 个连续段的方案数 然后 对于段内方案数是 $\sum_{i=1}^{n-1}\binom{n}{i} =2^{n-1}$

然后这段新的电脑的排列顺序又可以跟前面的段内交换方案数 $\binom{i-j+1}{n}$ 

# P3643

简单暴力的思路

对暴力 dp[i][j] 表示前 i 个学校 j 为最大值的方案数。

$$dp[i][j]=dp[i-1][j]+[a_i\le j \le b_i]\sum_{k=1}^{j-1}dp[i-1][k]$$

容易想到多项式维护这个式子，后面区间中的求和可以使用离散微积分做到快速求表达式。

最后式子是分段函数的形式，注意细节，维护一下常数项即可


# AGC30 - D - Inversion Sum

喵喵题。

直接计数是困难的，这里可以转化为期望。

对于每次操作有二分之一概率执行。

我们定义 F[i][j] 表示 $a_i>a_j$ 的概率，每次对于 $x,y$ 可以发现 $F[i][x],F[i][y]$ 可能会交换， $F[x][i],F[y][i]$ 可能会交换 $F[x][y],F[y][x]$ 同理，然后维护这个数组就行了，复杂度 $O(n^2+nq)$ 。

# AT_codefestival_2016_final_f_Road_of_the_King

明显的dp，考虑如何设计状态。

要求图强联通，则每个点与 1 都要相互可到达，我们设计状态表示走了 i 步，路过了 j 个点 k 个点 与 1 强联通

只要我们重新走回到与 1 强联通的点，路过的所有点都会变成强联通。

以此可以很快写出转移方程。

# P9823 [ICPC 2020 Shanghai R] The Journey of Geor Autumn

考虑 1 的位置

设 1 在位置 $x,x\ le k$ 

则有前 x 个数的位置是可以随便放的。

然后 $[x+1,x+k]$ 区间里的数也是可以随便放的

所以这里相当于一个子问题，我们还是需要吧最小值放到前 k 个位置。

所以有 

$$
f_n=\sum_{x=1}^{\min(n,k)}(x-1)!\binom{n-1}{x-1}f_{n-x}\\
=\sum_{x=1}^{\min(n,k)}\frac{(n-1)!}{(n-x)!}f_{n-x}
$$

# AT_arc178_d [ARC178D] Delete Range Mex

考虑反过来加数。

我们从小到大加数，一个数只能被加到所有小于等于他的数的两边。

对于给出的 $n$ 个数，有 $n+1$ 个插入位置。

然后对于一个数 $x$，如果已经出现过

$F[x-1][l][r]\to F[x][\min(l,pos_x)][\max(pos_x+1,r)]$

否则枚举出现位置，前缀和优化一下就行。

# P6944 [ICPC 2018 WF] Gem Island

设结束后每个人有 $a_i$ 个宝石，想要达成这种分配方式的方案数其实就是隔板法，是确定可算的，算出来没种分配方式都是等概率的。

所以我们计算所有分配方式前 $r$ 大数的和即可以及分配方式总数即可。

这里的分配本质就是 $d$ 分配到 $n$ 个数上。

使用拆分数 dp $F[i][j]$ 表示和为 $i$ 有 $j$ 个最大值的方案数。

每次只增加最大值，直到分配 完 d 个数。


当然，这道题二项式反演是更直观的做法。

设在所有的合法的 $a$ 中，有 $F[i][j]$ 表示有 $i$ 个数大于等于 $j$。

可以发现答案就是 $\sum_{i,j}\min(i,k)F[i][j]$

设 $g$ 为钦定有 i 个数大于等于 j

$$
g[i][j]=\binom{n}{i}\binom{d-ij+n-1}{n-1}
$$

对 f 进行二项式反演：
$$
 F[k][j]=\sum_{i\ge k}(-1)^{i-k}\binom{i}{k}g[i][j]=\\
 \sum_{i\ge k}(-1)^{i-k}\binom{i}{k}\binom{n}{i}\binom{d-ij+n-1}{n-1}
$$

这个式子已经能通过了。

可以枚举 $j$ 进行计算

这个式子还能进一步优化：

$$
\sum_k\min(k,r)\sum_{i\ge k}(-1)^{i-k}\binom{i}{k}\binom{n}{i}\sum_{j}\binom{d-ij+n-1}{n-1}
$$

稍微交换一下求和顺序：

$$
\sum_{i}\binom{n}{i}(\sum_{j}\binom{d-ij+n-1}{n-1})(\sum_k (-1)^{i-k}\binom{i}{k}\min(k,r))
$$

j k 的求和明显可以分开来算。

对 $j$ 的设：
$$
g(i)=\sum_{j}\binom{d-ij+n-1}{n-1}
\\
z(k)=\binom{d-k+n-1}{n-1}
\\ 有\\
g(i)=\sum_{i|k}z(k)
$$

可以 $\text{dirichlet}$ 后缀和求出所有 $g(i)$

对于 $k$ 的部分：
$$
\sum_k (-1)^{i-k}\binom{i}{k}\min(k,r)=\\
\sum_{k=1}^{\min(d,r)}k(-1)^k\binom{i}{k}+r\sum_{k=r+1}^d(-1)^k\binom{i}{k}\\=
\sum_{k=1}^{\min(d,r)}i(-1)^k\binom{i-1}{k-1}+r\sum_{k=r+1}^d(-1)^k\binom{i}{k}\\
=\sum_{k=0}^{\min(d,r)-1}i(-1)^{k-1}\binom{i-1}{k}+r\sum_{k=r+1}^d(-1)^k\binom{i}{k}
$$

有组合恒等式：

$$
    \sum_{k=0}^m(-1)^k\binom{n}{k}=(-1)^m\binom{n-1}{m}
$$

则能化简为

$$
i(-1)^{\min(d,r)}\binom{i-2}{\min(d,r)-1}+r((-1)^d\binom{i-1}d-(-1)^r\binom{i-1}r)
$$

做到 $O(n)$ 的复杂度。
