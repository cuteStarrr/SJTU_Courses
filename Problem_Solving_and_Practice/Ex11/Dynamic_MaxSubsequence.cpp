#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dp[n];
    vector<int> seq;
    int tmp;
    while(cin >> tmp) {
        if(tmp < -1000 || tmp > 1000) {
            cout << "error";
            return 0;
        }
        seq.push_back(tmp);
    }
    if(seq.size() > 100000 || seq.size() != n) {
        cout << "error";
        return 0;
    }

    int start = 0;
    int end = 0;
    int start_pre = 0;
    int end_pre = 0;
    int pre = seq[0];
    dp[0] = seq[0];
    for(int i = 1; i < n; ++i) {
        pre = max(seq[i], seq[i] + pre);
        end_pre = i;
        if(seq[i] >= seq[i] + pre) {
            start_pre = i;
        }
        dp[i] = max(dp[i - 1], pre);
        if(pre > dp[i - 1]) {
            start = start_pre;
            end = end_pre;
        }
    }
    cout << dp[n - 1] << ' ' << start + 1 << ' ' << end + 1;

    return 0;
}