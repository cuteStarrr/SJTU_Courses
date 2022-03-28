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
    int max_weight, num_persons;
    vector<int> persons;
    int weight;
    int flag = 0;

    cin >> max_weight >> num_persons;
    for(int i = 0; i < num_persons; ++i) {
        cin >> weight;
        if(weight > max_weight) {
            flag = 1;
        }
        else {
            if(weight <= 0) {
                flag = 2;
            }
            else persons.push_back(weight);
        }
    }

    if(flag == 1) {
        cout << "out";
        return 0;
    }
    if(flag == 2) {
        cout << "error";
        return 0;
    }

    sort(persons.begin(), persons.end());

    int num_boats = 0;
    int loaded = 0;
    int i = 0;
    int start = 0;
    int end = persons.size() - 1;
    while(i < persons.size()) {
        loaded += persons[end];
        ++i;
        --end;
        if(loaded + persons[start] <= max_weight) {
            ++i;
            ++start;
        }
        ++num_boats;
        loaded = 0;
    }
    cout << num_boats;

    return 0;
}