#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;


void traverseToFactors (int num, int size) {
    vector<int> factors_t;
    int up = sqrt(num);
    factors_t.push_back(1);
    int len = 1;
    
    if(num != 1) {
        factors_t.push_back(num);
        len = 2 + to_string(num).size();
        for(int i = 2; i <= up; ++i) {
            if(!(num % i)) {
                factors_t.push_back(i);
                len = len + 1 + to_string(i).size();
                if(i < num / i) {
                    factors_t.push_back(num / i);
                    len = len + 1 + to_string(num / i).size();
                }
            }
        }
    }

    sort(factors_t.begin(), factors_t.end());
    factors_t.erase(unique(factors_t.begin(), factors_t.end()), factors_t.end());

    cout << size << ':' << (len + (to_string(factors_t.size())).size() + 1) * 2 + 1 << '\n';
    cout << factors_t.size();
    for(int i = 0; i < factors_t.size(); ++i) {
        cout << ' ' << factors_t[i];
    }
    cout << endl;

}


int prime (int num, int* prime_factors) {
    int k = num;
    int pos = 0;

    int flag;
    while(k != 1) {
        flag = 0;
        if (!(k % 2)) {
            k = k / 2;
            prime_factors[pos] = 2;
            ++pos;
            flag = 1;
        }
        if(flag) continue;
        for(int i = 2; i <= k; ++i) {
            if (!(k % i)) {
                k = k / i;
                prime_factors[pos] = i;
                ++pos;
                flag = 1;
            }
            if (flag) break;
        }
    }

    return pos;

}


void Multiple (vector<int>& factors, int size, int* prime_factors, int times) {
    if(size == 1) {
        factors.push_back(prime_factors[size - 1] * times);
        return ;
    }
    if(size == 0) return ;

    Multiple(factors, size - 1, prime_factors, times);
    Multiple(factors, size - 1, prime_factors, times * prime_factors[size - 1]);
    factors.push_back(prime_factors[size - 1] * times);
}

void primeToFactors (int num) {
    int n_prime;
    int * prime_factors;
    prime_factors = new int(int(sqrt(num)) * 2);

    n_prime = prime(num, prime_factors);

    vector<int> factors;
    Multiple(factors, n_prime, prime_factors, 1);
    factors.push_back(1);

    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());

    cout<< factors.size();
    for(vector<int>::iterator it=factors.begin(); it!=factors.end(); it++){
        cout << ' ' << *it;
    }

    delete prime_factors;

}

//¶¨Òåmainº¯Êý
int main() 
{		
   bool exercise1=true;
    if(exercise1)    {
    //第一关执行代码
    string str;          
    getline(cin,str);    

    int num = atoi(str.c_str());

    traverseToFactors(num, str.size());

    primeToFactors(num);
    }   else     {
    //第二关执行代码


    }
    
    
	/********** End **********/
  	return 0;
}