#include <iostream>
#include <vector>
using namespace std;

int Fib(int n) {
    if (n <= 1) return n;

    //定义DP表
    vector<int> dp(n + 1, 0);

    // 2. 初始化边界
    dp[0] = 0;
    dp[1] = 1;

    // 3. 自底向上递推（状态转移方程）
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];//状态转移方程
    }

    return dp[n];
}

int main() {
    cout << Fib(10) << endl; // 输出 55
    return 0;
}