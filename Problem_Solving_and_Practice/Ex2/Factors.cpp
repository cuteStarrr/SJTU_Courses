#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

void traverseToFactors (int num, int size) {
    int* factors;
    int up = sqrt(num);
    factors = new int(up * 2);
    factors[0] = 1;
    int pos = 1;
    int len = 1;
    
    if(num != 1) {
        factors[1] = num;
        pos = 2;
        len = 2 + to_string(num).size();
        for(int i = 2; i <= up; ++i) {
            if(!(num % i)) {
                factors[pos] = i;
                ++pos;
                len = len + 1 + to_string(i).size();
                factors[pos] = num / i;
                ++pos;
                len = len + 1 + to_string(factors[pos]).size();
            }
        }
    }


    cout << size << ':' << (len + (to_string(pos)).size() + 1) * 2 + 1 << '\n';
    cout << pos;
    for(int i = 0; i < pos; i = i + 2) {
        cout << ' ' << factors[i];
    }
    for(int i = pos - 1; i > 0; i = i - 2) {
        cout << ' ' << factors[i];
    }
    cout << endl;

    delete factors;
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
            //cout << prime_factors[pos] << endl;
            ++pos;
            flag = 1;
        }
        if(flag) continue;
        for(int i = 3; i <= k; i = i + 2) {
            if (!(k % i)) {
                k = k / i;
                prime_factors[pos] = i;
                //cout << prime_factors[pos] << endl;
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
        cout << prime_factors[size - 1] * times <<endl;
        return ;
    }
    if(size == 0) return ;

    Multiple(factors, size - 1, prime_factors, times);
    Multiple(factors, size - 1, prime_factors, times * prime_factors[size - 1]);
    factors.push_back(prime_factors[size - 1] * times);
}

void primeToFactors (int num) {
    int n_prime;
    int* prime_factors;
    prime_factors = new int(int(sqrt(num)) * 2);

    clock_t t2;
    t2 = clock();
    cout << "t2:" << t2 << endl;

    n_prime = prime(num, prime_factors);

    clock_t t3;
    t3 = clock();
    cout << "t3:" << t3 << endl;
    
    /********************/
    for(int i = 0;i < n_prime; ++i) {
        cout << prime_factors[i] << ' ';
    }
    cout << endl;
    /********************/

    vector<int> factors;
    Multiple(factors, n_prime, prime_factors, 1);
    factors.push_back(1);

    clock_t t4;
    t4 = clock();
    cout << "t4:" << t4 << endl;

    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());

    clock_t t5;
    t5 = clock();
    cout << "t5:" << t5 << endl;

    int len = factors.size();
    cout<< len;

    for(int i = 0; i < len; ++i) {
        cout << ' ' << factors[i];
    }

    clock_t t6;
    t6 = clock();
    cout <<'\n' << "t6:" << t6 << endl;

    //for(vector<int>::iterator it=factors.begin(); it!=factors.end(); it++){
    //    cout << ' ' << *it;
    //}

    delete prime_factors;
}


int main() 
{		
   bool exercise1=true;
    if(exercise1)    {
    //第一关执行代码
    //string str;          
    //getline(cin,str);

    clock_t start, finish;
    start = clock();
    cout << start << endl;
    //int num = atoi(str.c_str());

    //traverseToFactors(num, str.size());

    int num = 100;
    traverseToFactors(num, 3);

    clock_t t1;
    t1 = clock();
    cout << t1 << endl;

    primeToFactors(num);

    finish = clock();
    cout << finish << endl;
    }   else     {
    //第二关执行代码


    }
    
    
	/********** End **********/
  	return 0;
}