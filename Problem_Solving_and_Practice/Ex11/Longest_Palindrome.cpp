#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <map>
#include <string.h>

using namespace std;

int main() {
    string s;
    s = "racecar";
    //getline(cin,s);

    string palin_start = "";
    string palin_end = "";
    int dp[1000][1000];
    int path[1000][1000];
    for(int i = 0; i < s.size(); ++i) {
        dp[i][i] = 1;
    }

    for(int step = 1; step < s.size(); ++step) {
        for(int start = 0; start + step < s.size(); ++start) {
            if(s[start] == s[start + step]) {
                dp[start][start + step] = 2 + dp[start + 1][start + step - 1];
                path[start][start + step] = 1;
            }
            else {
                if(dp[start + 1][start + step] >= dp[start][start + step - 1]) {
                    dp[start][start + step] = dp[start + 1][start + step];
                    path[start][start + step] = 2;
                }
                else {
                    dp[start][start + step] = dp[start][start + step - 1];
                    path[start][start + step] = 3;
                }
            }
        }
    }

    int start = 0;
    int end = s.size() - 1;
    while(start < end) {
        if(path[start][end] == 1) {
            palin_start = palin_start + s[start];
            palin_end = s[end] + palin_end;
            ++start;
            --end;
        }
        if(path[start][end] == 2) ++start;
        if(path[start][end] == 3) --end;
    }
    if(start == end) palin_start = palin_start + s[start];

    cout << palin_start + palin_end;

    return 0;
}